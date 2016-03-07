/*
 * Copyright (C) 2009 Alex Milowski (alex@milowski.com). All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef RenderMathMLRoot_h
#define RenderMathMLRoot_h

#if ENABLE(MATHML)

#include "RenderMathMLBlock.h"
#include "RenderMathMLRow.h"

namespace WebCore {

class RenderMathMLRadicalOperator;
class RenderMathMLRootWrapper;
    
// Render base^(1/index), or sqrt(base) via the derived class RenderMathMLSquareRoot, using radical notation.
class RenderMathMLRoot : public RenderMathMLBlock {

friend class RenderMathMLRootWrapper;

public:
    RenderMathMLRoot(Element&, PassRef<RenderStyle>);
    RenderMathMLRoot(Document&, PassRef<RenderStyle>);

    virtual void addChild(RenderObject* newChild, RenderObject* beforeChild = 0) override;
    virtual void styleDidChange(StyleDifference, const RenderStyle* oldStyle) override;
    virtual void updateFromElement() override;
    
protected:
    virtual void layout() override;
    
    virtual void paint(PaintInfo&, const LayoutPoint&) override;

private:
    virtual bool isRenderMathMLRoot() const override final { return true; }
    virtual const char* renderName() const override { return "RenderMathMLRoot"; }
    virtual int firstLineBaseline() const override;
    void updateStyle();
    void restructureWrappers();

    RenderMathMLRootWrapper* baseWrapper() const;
    RenderMathMLBlock* radicalWrapper() const;
    RenderMathMLRootWrapper* indexWrapper() const;
    RenderMathMLRadicalOperator* radicalOperator() const;

    LayoutUnit m_verticalGap;
    LayoutUnit m_ruleThickness;
    LayoutUnit m_extraAscender;
    float m_degreeBottomRaisePercent;
};

// These are specific wrappers for the index and base, that ask the parent to restructure the renderers after child removal.
class RenderMathMLRootWrapper final : public RenderMathMLRow {

friend class RenderMathMLRoot;

public:
    RenderMathMLRootWrapper(Document& document, PassRef<RenderStyle> style)
        : RenderMathMLRow(document, WTF::move(style)) { }

private:
    RenderObject* removeChildWithoutRestructuring(RenderObject&);
    virtual RenderObject* removeChild(RenderObject&) override;
    static RenderPtr<RenderMathMLRootWrapper> createAnonymousWrapper(RenderMathMLRoot* renderObject);
    virtual bool isRenderMathMLRootWrapper() const override { return true; }
    virtual const char* renderName() const override { return "RenderMathMLRootWrapper"; }
};

} // namespace WebCore

SPECIALIZE_TYPE_TRAITS_RENDER_OBJECT(RenderMathMLRoot, isRenderMathMLRoot())
SPECIALIZE_TYPE_TRAITS_RENDER_OBJECT(RenderMathMLRootWrapper, isRenderMathMLRootWrapper())

#endif // ENABLE(MATHML)

#endif // RenderMathMLRoot_h
