/*
 * Copyright (C) 2015 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

WebInspector.ObjectTreeSetIndexTreeElement = function(object, propertyPath)
{
    console.assert(object instanceof WebInspector.RemoteObject);

    this._object = object;

    // Treat the same as an array-index just with different strings and widths.
    WebInspector.ObjectTreeBaseTreeElement.call(this, this._object, propertyPath);

    this.mainTitle = this._titleFragment();
    this.addClassName("object-tree-array-index");
};

WebInspector.ObjectTreeSetIndexTreeElement.prototype = {
    constructor: WebInspector.ObjectTreeSetIndexTreeElement,
    __proto__: WebInspector.ObjectTreeBaseTreeElement.prototype,

    // Public

    get object()
    {
        return this._object;
    },

    // Protected

    resolvedValue()
    {
        return this._object;
    },

    resolvedValuePropertyPath()
    {
        return this.propertyPath.appendSetIndex(this._object);
    },

    // Private

    _titleFragment()
    {
        var container = document.createDocumentFragment();

        var propertyPath = this.resolvedValuePropertyPath();

        // Set bullet.
        var nameElement = container.appendChild(document.createElement("span"));
        nameElement.className = "index-name";
        nameElement.textContent = "\u2022";
        nameElement.title = WebInspector.UIString("Unable to determine path to property from root");

        // Value.
        var valueElement = container.appendChild(document.createElement("span"));
        valueElement.className = "index-value";
        valueElement.appendChild(WebInspector.FormattedValue.createObjectTreeOrFormattedValueForRemoteObject(this._object, propertyPath));

        return container;
    }
};
