/*
 * Copyright (C) 2014, 2015 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "Heap.h"
#include "LargeChunk.h"
#include "LargeObject.h"
#include "Line.h"
#include "MediumChunk.h"
#include "Page.h"
#include "PerProcess.h"
#include "SmallChunk.h"
#include <thread>

namespace bmalloc {

static inline void sleep(std::unique_lock<StaticMutex>& lock, std::chrono::milliseconds duration)
{
    if (duration == std::chrono::milliseconds(0))
        return;
    
    lock.unlock();
    std::this_thread::sleep_for(duration);
    lock.lock();
}

Heap::Heap(std::lock_guard<StaticMutex>&)
    : m_largeObjects(Owner::Heap)
    , m_isAllocatingPages(false)
    , m_scavenger(*this, &Heap::concurrentScavenge)
{
    initializeLineMetadata();
}

void Heap::initializeLineMetadata()
{
    for (unsigned short size = alignment; size <= smallMax; size += alignment) {
        unsigned short startOffset = 0;
        for (size_t lineNumber = 0; lineNumber < SmallPage::lineCount - 1; ++lineNumber) {
            unsigned short objectCount;
            unsigned short remainder;
            divideRoundingUp(static_cast<unsigned short>(SmallPage::lineSize - startOffset), size, objectCount, remainder);
            BASSERT(objectCount);
            m_smallLineMetadata[sizeClass(size)][lineNumber] = { startOffset, objectCount };
            startOffset = remainder ? size - remainder : 0;
        }

        // The last line in the page rounds down instead of up because it's not allowed to overlap into its neighbor.
        unsigned short objectCount = static_cast<unsigned short>((SmallPage::lineSize - startOffset) / size);
        m_smallLineMetadata[sizeClass(size)][SmallPage::lineCount - 1] = { startOffset, objectCount };
    }

    for (unsigned short size = smallMax + alignment; size <= mediumMax; size += alignment) {
        unsigned short startOffset = 0;
        for (size_t lineNumber = 0; lineNumber < MediumPage::lineCount - 1; ++lineNumber) {
            unsigned short objectCount;
            unsigned short remainder;
            divideRoundingUp(static_cast<unsigned short>(MediumPage::lineSize - startOffset), size, objectCount, remainder);
            BASSERT(objectCount);
            m_mediumLineMetadata[sizeClass(size)][lineNumber] = { startOffset, objectCount };
            startOffset = remainder ? size - remainder : 0;
        }

        // The last line in the page rounds down instead of up because it's not allowed to overlap into its neighbor.
        unsigned short objectCount = static_cast<unsigned short>((MediumPage::lineSize - startOffset) / size);
        m_mediumLineMetadata[sizeClass(size)][MediumPage::lineCount - 1] = { startOffset, objectCount };
    }
}

void Heap::concurrentScavenge()
{
    std::unique_lock<StaticMutex> lock(PerProcess<Heap>::mutex());
    scavenge(lock, scavengeSleepDuration);
}
    
void Heap::scavenge(std::unique_lock<StaticMutex>& lock, std::chrono::milliseconds sleepDuration)
{
    scavengeSmallPages(lock, sleepDuration);
    scavengeMediumPages(lock, sleepDuration);
    scavengeLargeRanges(lock, sleepDuration);

    sleep(lock, sleepDuration);
}

void Heap::scavengeSmallPages(std::unique_lock<StaticMutex>& lock, std::chrono::milliseconds sleepDuration)
{
    while (1) {
        if (m_isAllocatingPages) {
            m_isAllocatingPages = false;

            sleep(lock, sleepDuration);
            continue;
        }

        if (!m_smallPages.size())
            return;
        m_vmHeap.deallocateSmallPage(lock, m_smallPages.pop());
    }
}

void Heap::scavengeMediumPages(std::unique_lock<StaticMutex>& lock, std::chrono::milliseconds sleepDuration)
{
    while (1) {
        if (m_isAllocatingPages) {
            m_isAllocatingPages = false;

            sleep(lock, sleepDuration);
            continue;
        }

        if (!m_mediumPages.size())
            return;
        m_vmHeap.deallocateMediumPage(lock, m_mediumPages.pop());
    }
}

void Heap::scavengeLargeRanges(std::unique_lock<StaticMutex>& lock, std::chrono::milliseconds sleepDuration)
{
    while (1) {
        if (m_isAllocatingPages) {
            m_isAllocatingPages = false;

            sleep(lock, sleepDuration);
            continue;
        }

        LargeObject largeObject = m_largeObjects.takeGreedy();
        if (!largeObject)
            return;
        m_vmHeap.deallocateLargeObject(lock, largeObject);
    }
}

void Heap::refillSmallBumpRangeCache(std::lock_guard<StaticMutex>& lock, size_t sizeClass, BumpRangeCache& rangeCache)
{
    BASSERT(!rangeCache.size());
    SmallPage* page = allocateSmallPage(lock, sizeClass);
    SmallLine* lines = page->begin();

    // Due to overlap from the previous line, the last line in the page may not be able to fit any objects.
    size_t end = SmallPage::lineCount;
    if (!m_smallLineMetadata[sizeClass][SmallPage::lineCount - 1].objectCount)
        --end;

    // Find a free line.
    for (size_t lineNumber = 0; lineNumber < end; ++lineNumber) {
        if (lines[lineNumber].refCount(lock))
            continue;

        LineMetadata& lineMetadata = m_smallLineMetadata[sizeClass][lineNumber];
        char* begin = lines[lineNumber].begin() + lineMetadata.startOffset;
        unsigned short objectCount = lineMetadata.objectCount;
        lines[lineNumber].ref(lock, lineMetadata.objectCount);
        page->ref(lock);

        // Merge with subsequent free lines.
        while (++lineNumber < end) {
            if (lines[lineNumber].refCount(lock))
                break;

            LineMetadata& lineMetadata = m_smallLineMetadata[sizeClass][lineNumber];
            objectCount += lineMetadata.objectCount;
            lines[lineNumber].ref(lock, lineMetadata.objectCount);
            page->ref(lock);
        }

        rangeCache.push({ begin, objectCount });
    }
}

void Heap::refillMediumBumpRangeCache(std::lock_guard<StaticMutex>& lock, size_t sizeClass, BumpRangeCache& rangeCache)
{
    MediumPage* page = allocateMediumPage(lock, sizeClass);
    BASSERT(!rangeCache.size());
    MediumLine* lines = page->begin();

    // Due to overlap from the previous line, the last line in the page may not be able to fit any objects.
    size_t end = MediumPage::lineCount;
    if (!m_mediumLineMetadata[sizeClass][MediumPage::lineCount - 1].objectCount)
        --end;

    // Find a free line.
    for (size_t lineNumber = 0; lineNumber < end; ++lineNumber) {
        if (lines[lineNumber].refCount(lock))
            continue;

        LineMetadata& lineMetadata = m_mediumLineMetadata[sizeClass][lineNumber];
        char* begin = lines[lineNumber].begin() + lineMetadata.startOffset;
        unsigned short objectCount = lineMetadata.objectCount;
        lines[lineNumber].ref(lock, lineMetadata.objectCount);
        page->ref(lock);
        
        // Merge with subsequent free lines.
        while (++lineNumber < end) {
            if (lines[lineNumber].refCount(lock))
                break;

            LineMetadata& lineMetadata = m_mediumLineMetadata[sizeClass][lineNumber];
            objectCount += lineMetadata.objectCount;
            lines[lineNumber].ref(lock, lineMetadata.objectCount);
            page->ref(lock);
        }

        rangeCache.push({ begin, objectCount });
    }
}

SmallPage* Heap::allocateSmallPage(std::lock_guard<StaticMutex>& lock, size_t sizeClass)
{
    Vector<SmallPage*>& smallPagesWithFreeLines = m_smallPagesWithFreeLines[sizeClass];
    while (smallPagesWithFreeLines.size()) {
        SmallPage* page = smallPagesWithFreeLines.pop();
        if (!page->refCount(lock) || page->sizeClass() != sizeClass) // Page was promoted to the pages list.
            continue;
        return page;
    }
    
    m_isAllocatingPages = true;

    SmallPage* page = [this, sizeClass]() {
        if (m_smallPages.size())
            return m_smallPages.pop();
        return m_vmHeap.allocateSmallPage();
    }();

    page->setSizeClass(sizeClass);
    return page;
}

MediumPage* Heap::allocateMediumPage(std::lock_guard<StaticMutex>& lock, size_t sizeClass)
{
    Vector<MediumPage*>& mediumPagesWithFreeLines = m_mediumPagesWithFreeLines[sizeClass];
    while (mediumPagesWithFreeLines.size()) {
        MediumPage* page = mediumPagesWithFreeLines.pop();
        if (!page->refCount(lock) || page->sizeClass() != sizeClass) // Page was promoted to the pages list.
            continue;
        return page;
    }
    
    m_isAllocatingPages = true;

    MediumPage* page = [this, sizeClass]() {
        if (m_mediumPages.size())
            return m_mediumPages.pop();
        return m_vmHeap.allocateMediumPage();
    }();

    page->setSizeClass(sizeClass);
    return page;
}

void Heap::deallocateSmallLine(std::lock_guard<StaticMutex>& lock, SmallLine* line)
{
    BASSERT(!line->refCount(lock));
    SmallPage* page = SmallPage::get(line);
    size_t refCount = page->refCount(lock);
    page->deref(lock);

    switch (refCount) {
    case SmallPage::lineCount: {
        // First free line in the page.
        m_smallPagesWithFreeLines[page->sizeClass()].push(page);
        break;
    }
    case 1: {
        // Last free line in the page.
        m_smallPages.push(page);
        m_scavenger.run();
        break;
    }
    }
}

void Heap::deallocateMediumLine(std::lock_guard<StaticMutex>& lock, MediumLine* line)
{
    BASSERT(!line->refCount(lock));
    MediumPage* page = MediumPage::get(line);
    size_t refCount = page->refCount(lock);
    page->deref(lock);

    switch (refCount) {
    case MediumPage::lineCount: {
        // First free line in the page.
        m_mediumPagesWithFreeLines[page->sizeClass()].push(page);
        break;
    }
    case 1: {
        // Last free line in the page.
        m_mediumPages.push(page);
        m_scavenger.run();
        break;
    }
    }
}

void* Heap::allocateXLarge(std::lock_guard<StaticMutex>&, size_t alignment, size_t size)
{
    BASSERT(isPowerOfTwo(alignment));
    BASSERT(alignment >= xLargeAlignment);
    BASSERT(size == roundUpToMultipleOf<xLargeAlignment>(size));

    m_isAllocatingPages = true;

    void* result = vmAllocate(alignment, size);
    m_xLargeObjects.push(Range(result, size));
    return result;
}

void* Heap::allocateXLarge(std::lock_guard<StaticMutex>& lock, size_t size)
{
    return allocateXLarge(lock, superChunkSize, size);
}

Range Heap::findXLarge(std::lock_guard<StaticMutex>&, void* object)
{
    for (auto& range : m_xLargeObjects) {
        if (range.begin() != object)
            continue;
        return range;
    }

    return Range();
}

void Heap::deallocateXLarge(std::unique_lock<StaticMutex>& lock, void* object)
{
    for (auto& range : m_xLargeObjects) {
        if (range.begin() != object)
            continue;

        Range toDeallocate = m_xLargeObjects.pop(&range);

        lock.unlock();
        vmDeallocate(toDeallocate.begin(), toDeallocate.size());
        lock.lock();
        
        break;
    }
}

void* Heap::allocateLarge(std::lock_guard<StaticMutex>&, LargeObject& largeObject, size_t size)
{
    BASSERT(largeObject.isFree());

    if (largeObject.size() - size > largeMin) {
        std::pair<LargeObject, LargeObject> split = largeObject.split(size);
        largeObject = split.first;
        m_largeObjects.insert(split.second);
    }

    largeObject.setFree(false);
    return largeObject.begin();
}

void* Heap::allocateLarge(std::lock_guard<StaticMutex>& lock, size_t size)
{
    BASSERT(size <= largeMax);
    BASSERT(size >= largeMin);
    BASSERT(size == roundUpToMultipleOf<largeAlignment>(size));
    
    m_isAllocatingPages = true;

    LargeObject largeObject = m_largeObjects.take(size);
    if (!largeObject)
        largeObject = m_vmHeap.allocateLargeObject(size);

    return allocateLarge(lock, largeObject, size);
}

void* Heap::allocateLarge(std::lock_guard<StaticMutex>& lock, size_t alignment, size_t size, size_t unalignedSize)
{
    BASSERT(size <= largeMax);
    BASSERT(size >= largeMin);
    BASSERT(size == roundUpToMultipleOf<largeAlignment>(size));
    BASSERT(unalignedSize <= largeMax);
    BASSERT(unalignedSize >= largeMin);
    BASSERT(unalignedSize == roundUpToMultipleOf<largeAlignment>(unalignedSize));
    BASSERT(alignment <= largeChunkSize / 2);
    BASSERT(alignment >= largeAlignment);
    BASSERT(isPowerOfTwo(alignment));

    m_isAllocatingPages = true;

    LargeObject largeObject = m_largeObjects.take(alignment, size, unalignedSize);
    if (!largeObject)
        largeObject = m_vmHeap.allocateLargeObject(alignment, size, unalignedSize);

    size_t alignmentMask = alignment - 1;
    if (test(largeObject.begin(), alignmentMask)) {
        size_t prefixSize = roundUpToMultipleOf(alignment, largeObject.begin() + largeMin) - largeObject.begin();
        std::pair<LargeObject, LargeObject> pair = largeObject.split(prefixSize);
        m_largeObjects.insert(pair.first);
        largeObject = pair.second;
    }

    return allocateLarge(lock, largeObject, size);
}

void Heap::deallocateLarge(std::lock_guard<StaticMutex>&, const LargeObject& largeObject)
{
    BASSERT(!largeObject.isFree());
    largeObject.setFree(true);
    
    LargeObject merged = largeObject.merge();
    m_largeObjects.insert(merged);
    m_scavenger.run();
}

void Heap::deallocateLarge(std::lock_guard<StaticMutex>& lock, void* object)
{
    LargeObject largeObject(object);
    deallocateLarge(lock, largeObject);
}

} // namespace bmalloc
