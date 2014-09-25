/*
 * Copyright (C) 2012 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
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

#ifndef LabelableElement_h
#define LabelableElement_h

#include "HTMLElement.h"

namespace WebCore {

// LabelableElement represents "labelable element" defined in the HTML specification.
class LabelableElement : public HTMLElement {
public:
    virtual ~LabelableElement();

    PassRefPtr<NodeList> labels();
    virtual bool supportLabels() const { return false; }

protected:
    LabelableElement(const QualifiedName& tagName, Document&);

private:
    virtual bool isLabelable() const override final { return true; }
};

void isLabelableElement(const LabelableElement&); // Catch unnecessary runtime check of type known at compile time.
inline bool isLabelableElement(const HTMLElement& element) { return element.isLabelable(); }
inline bool isLabelableElement(const Node& node) { return node.isHTMLElement() && toHTMLElement(node).isLabelable(); }

template <typename ArgType>
struct NodeTypeCastTraits<const LabelableElement, ArgType> {
    static bool isType(ArgType& node) { return isLabelableElement(node); }
};

NODE_TYPE_CASTS(LabelableElement)

} // namespace WebCore

#endif
