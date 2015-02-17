/*
 *  Copyright (C) 2010, 2015 Igalia S.L.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "config.h"
#include "DOMObjectCache.h"

#include "Document.h"
#include "FrameDestructionObserver.h"
#include "Node.h"
#include <glib-object.h>
#include <wtf/HashMap.h>
#include <wtf/NeverDestroyed.h>
#include <wtf/Vector.h>
#include <wtf/gobject/GRefPtr.h>

namespace WebKit {

struct DOMObjectCacheData {
    DOMObjectCacheData(GObject* wrapper)
        : object(wrapper)
        , cacheReferences(1)
    {
    }

    void clearObject()
    {
        ASSERT(object);
        ASSERT(cacheReferences >= 1);

        GRefPtr<GObject> protect(object);
        do {
            g_object_unref(object);
        } while (--cacheReferences);
        object = nullptr;
    }

    void* refObject()
    {
        ASSERT(object);

        cacheReferences++;
        return g_object_ref(object);
    }

    GObject* object;
    unsigned cacheReferences;
};

class DOMObjectCacheFrameObserver;
typedef HashMap<WebCore::Frame*, std::unique_ptr<DOMObjectCacheFrameObserver>> DOMObjectCacheFrameObserverMap;

static DOMObjectCacheFrameObserverMap& domObjectCacheFrameObservers()
{
    static NeverDestroyed<DOMObjectCacheFrameObserverMap> map;
    return map;
}

static DOMObjectCacheFrameObserver& getOrCreateDOMObjectCacheFrameObserver(WebCore::Frame& frame)
{
    auto observerPtr = domObjectCacheFrameObservers().get(&frame);
    if (observerPtr)
        return *observerPtr;

    std::unique_ptr<DOMObjectCacheFrameObserver> observer = std::make_unique<DOMObjectCacheFrameObserver>(frame);
    observerPtr = observer.get();
    domObjectCacheFrameObservers().set(&frame, WTF::move(observer));
    return *observerPtr;
}

class DOMObjectCacheFrameObserver final: public WebCore::FrameDestructionObserver {
public:
    DOMObjectCacheFrameObserver(WebCore::Frame& frame)
        : FrameDestructionObserver(&frame)
    {
    }

    ~DOMObjectCacheFrameObserver()
    {
        ASSERT(m_objects.isEmpty());
    }

    void addObjectCacheData(DOMObjectCacheData& data)
    {
        ASSERT(!m_objects.contains(&data));

        m_objects.append(&data);
        g_object_weak_ref(data.object, DOMObjectCacheFrameObserver::objectFinalizedCallback, this);
    }

private:
    static void objectFinalizedCallback(gpointer userData, GObject* finalizedObject)
    {
        DOMObjectCacheFrameObserver* observer = static_cast<DOMObjectCacheFrameObserver*>(userData);
        observer->m_objects.removeFirstMatching([finalizedObject](DOMObjectCacheData* data) {
            return data->object == finalizedObject;
        });
    }

    void clear()
    {
        if (m_objects.isEmpty())
            return;

        auto objects = WTF::move(m_objects);
        for (auto* data : objects) {
            g_object_weak_unref(data->object, DOMObjectCacheFrameObserver::objectFinalizedCallback, this);
            data->clearObject();
        }
    }

    virtual void willDetachPage() override
    {
        clear();
    }

    virtual void frameDestroyed() override
    {
        clear();
        WebCore::Frame* frame = m_frame;
        FrameDestructionObserver::frameDestroyed();
        domObjectCacheFrameObservers().remove(frame);
    }

    Vector<DOMObjectCacheData*, 8> m_objects;
};

typedef HashMap<void*, std::unique_ptr<DOMObjectCacheData>> DOMObjectMap;

static DOMObjectMap& domObjects()
{
    static NeverDestroyed<DOMObjectMap> staticDOMObjects;
    return staticDOMObjects;
}

void DOMObjectCache::forget(void* objectHandle)
{
    ASSERT(domObjects().contains(objectHandle));
    domObjects().remove(objectHandle);
}

void* DOMObjectCache::get(void* objectHandle)
{
    DOMObjectCacheData* data = domObjects().get(objectHandle);
    return data ? data->refObject() : nullptr;
}

void DOMObjectCache::put(void* objectHandle, void* wrapper)
{
    if (domObjects().contains(objectHandle))
        return;
    domObjects().set(objectHandle, std::make_unique<DOMObjectCacheData>(G_OBJECT(wrapper)));
}

void DOMObjectCache::put(WebCore::Node* objectHandle, void* wrapper)
{
    if (domObjects().contains(objectHandle))
        return;

    std::unique_ptr<DOMObjectCacheData> data = std::make_unique<DOMObjectCacheData>(G_OBJECT(wrapper));
    auto dataPtr = data.get();
    domObjects().set(objectHandle, WTF::move(data));

    if (WebCore::Frame* frame = objectHandle->document().frame())
        getOrCreateDOMObjectCacheFrameObserver(*frame).addObjectCacheData(*dataPtr);
}

}
