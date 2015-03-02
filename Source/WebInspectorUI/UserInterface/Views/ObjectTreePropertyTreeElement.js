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

WebInspector.ObjectTreePropertyTreeElement = function(property, propertyPath, mode, prototypeName)
{
    console.assert(property instanceof WebInspector.PropertyDescriptor);
    console.assert(propertyPath instanceof WebInspector.PropertyPath);

    this._property = property;
    this._mode = mode || WebInspector.ObjectTreeView.Mode.Properties;
    this._propertyPath = propertyPath;
    this._prototypeName = prototypeName;

    var classNames = ["object-tree-property"];

    if (this._property.hasValue()) {
        classNames.push(this._property.value.type);
        if (this._property.value.subtype)
            classNames.push(this._property.value.subtype);
    } else
        classNames.push("accessor");

    if (this._property.wasThrown)
        classNames.push("had-error");

    if (this._property.name === "__proto__")
        classNames.push("prototype-property");

    WebInspector.GeneralTreeElement.call(this, classNames, this._titleFragment(), null, this._property, false);
    this._updateTooltips();
    this._updateHasChildren();

    this.small = true;
    this.toggleOnClick = true;
    this.selectable = false;
    this.tooltipHandledSeparately = true;
};

WebInspector.ObjectTreePropertyTreeElement.prototype = {
    constructor: WebInspector.ObjectTreePropertyTreeElement,
    __proto__: WebInspector.GeneralTreeElement.prototype,

    // Public

    get property()
    {
        return this._property;
    },

    // Protected

    onpopulate: function()
    {
        this._updateChildren();
    },

    onexpand: function()
    {
        if (this._previewView)
            this._previewView.showTitle();
    },

    oncollapse: function()
    {
        if (this._previewView)
            this._previewView.showPreview();
    },

    oncontextmenu: function(event)
    {
        this._contextMenuHandler(event);
    },

    // Private

    _resolvedValue: function()
    {
        if (this._getterValue)
            return this._getterValue;
        if (this._property.hasValue())
            return this._property.value;
        return null;
    },

    _propertyPathType: function()
    {
        if (this._getterValue || this._property.hasValue())
            return WebInspector.PropertyPath.Type.Value;
        if (this._property.hasGetter())
            return WebInspector.PropertyPath.Type.Getter;
        if (this._property.hasSetter())
            return WebInspector.PropertyPath.Type.Setter;
        return WebInspector.PropertyPath.Type.Value;
    },

    _resolvedValuePropertyPath: function()
    {
        if (this._getterValue)
            return this._propertyPath.appendPropertyDescriptor(this._getterValue, this._property, WebInspector.PropertyPath.Type.Value);
        if (this._property.hasValue())
            return this._propertyPath.appendPropertyDescriptor(this._property.value, this._property, WebInspector.PropertyPath.Type.Value);
        return null;
    },

    _thisPropertyPath: function()
    {
        return this._propertyPath.appendPropertyDescriptor(null, this._property, this._propertyPathType());
    },

    _updateHasChildren: function()
    {
        var resolvedValue = this._resolvedValue();
        var valueHasChildren = (resolvedValue && resolvedValue.hasChildren);
        var wasThrown = this._property.wasThrown || this._getterHadError;

        if (this._mode === WebInspector.ObjectTreeView.Mode.Properties)
            this.hasChildren = !wasThrown && valueHasChildren;
        else
            this.hasChildren = !wasThrown && valueHasChildren && (this._property.name === "__proto__" || this._alwaysDisplayAsProperty());
    },

    _updateTooltips: function()
    {
        var attributes = [];

        if (this._property.configurable)
            attributes.push("configurable");
        if (this._property.enumerable)
            attributes.push("enumerable");
        if (this._property.writable)
            attributes.push("writable");

        this.iconElement.title = attributes.join(" ");
    },

    _updateTitleAndIcon: function()
    {
        this.mainTitle = this._titleFragment();

        if (this._getterValue) {
            this.addClassName(this._getterValue.type);
            if (this._getterValue.subtype)
                this.addClassName(this._getterValue.subtype);
            if (this._getterHadError)
                this.addClassName("had-error");
            this.removeClassName("accessor");
        }

        this._updateHasChildren();
    },

    _titleFragment: function()
    {
        if (this._property.name === "__proto__")
            return this._createTitlePrototype();

        if (this._mode === WebInspector.ObjectTreeView.Mode.Properties)
            return this._createTitlePropertyStyle();
        else
            return this._createTitleAPIStyle();
    },

    _createTitlePrototype: function()
    {
        console.assert(this._property.hasValue());
        console.assert(this._property.name === "__proto__");

        var nameElement = document.createElement("span");
        nameElement.className = "prototype-name";
        nameElement.textContent = WebInspector.UIString("%s Prototype").format(this._sanitizedPrototypeString(this._property.value));
        nameElement.title = this._propertyPathString(this._thisPropertyPath());
        return nameElement;
    },

    _createTitlePropertyStyle: function()
    {
        var container = document.createDocumentFragment();

        // Property name.
        var nameElement = document.createElement("span");
        nameElement.className = "property-name";
        nameElement.textContent = this._property.name + ": ";
        nameElement.title = this._propertyPathString(this._thisPropertyPath());

        // Property attributes.
        if (this._mode === WebInspector.ObjectTreeView.Mode.Properties) {
            if (!this._property.enumerable)
                nameElement.classList.add("not-enumerable");
        }

        // Value / Getter Value / Getter.
        var valueOrGetterElement;
        var resolvedValue = this._resolvedValue();
        if (resolvedValue) {
            if (resolvedValue.preview) {
                this._previewView = new WebInspector.ObjectPreviewView(resolvedValue.preview);
                valueOrGetterElement = this._previewView.element;
            } else {
                valueOrGetterElement = WebInspector.FormattedValue.createElementForRemoteObject(resolvedValue, this._property.wasThrown || this._getterHadError);

                // Special case a function property string.
                if (resolvedValue.type === "function")
                    valueOrGetterElement.textContent = this._functionPropertyString();
            }

            // FIXME: Option+Click for Value.
        } else {
            valueOrGetterElement = document.createElement("span");
            if (this._property.hasGetter())
                valueOrGetterElement.appendChild(this._createInteractiveGetterElement());
            if (!this._property.hasSetter())
                valueOrGetterElement.appendChild(this._createReadOnlyIconElement());
            // FIXME: What if just a setter?
        }

        valueOrGetterElement.classList.add("value");
        if (this._property.wasThrown || this._getterHadError)
            valueOrGetterElement.classList.add("error");

        container.appendChild(nameElement);
        container.appendChild(valueOrGetterElement);
        return container;
    },

    _createTitleAPIStyle: function()
    {
        // Fixed values and special properties display like a property.
        if (this._alwaysDisplayAsProperty())
            return this._createTitlePropertyStyle();

        // Fetched getter values should already have been shown as properties.
        console.assert(!this._getterValue);

        // No API to display.
        var isFunction = this._property.hasValue() && this._property.value.type === "function";
        if (!isFunction && !this._property.hasGetter() && !this._property.hasSetter())
            return null;

        var container = document.createDocumentFragment();

        // Function / Getter / Setter.
        var nameElement = document.createElement("span");
        nameElement.className = "property-name";
        nameElement.textContent = this._property.name;
        nameElement.title = this._propertyPathString(this._thisPropertyPath());
        container.appendChild(nameElement);

        if (isFunction) {
            var paramElement = document.createElement("span");
            paramElement.className = "function-parameters";
            paramElement.textContent = this._functionParameterString();
            container.appendChild(paramElement);
        } else {
            if (this._property.hasGetter())
                container.appendChild(this._createInteractiveGetterElement());
            if (!this._property.hasSetter())
                container.appendChild(this._createReadOnlyIconElement());
            // FIXME: What if just a setter?
        }

        return container;
    },

    _createInteractiveGetterElement: function()
    {
        var getterElement = document.createElement("img");
        getterElement.className = "getter";
        getterElement.title = WebInspector.UIString("Invoke getter");

        getterElement.addEventListener("click", function(event) {
            event.stopPropagation();
            var lastNonPrototypeObject = this._propertyPath.lastNonPrototypeObject;
            var getterObject = this._property.get;
            lastNonPrototypeObject.invokeGetter(getterObject, function(error, result, wasThrown) {
                this._getterHadError = !!(error || wasThrown);
                this._getterValue = result;
                this._updateTitleAndIcon();
            }.bind(this));
        }.bind(this));

        return getterElement;
    },

    _createReadOnlyIconElement: function()
    {
        var readOnlyElement = document.createElement("img");
        readOnlyElement.className = "read-only";
        readOnlyElement.title = WebInspector.UIString("Read only");
        return readOnlyElement;
    },

    _alwaysDisplayAsProperty: function()
    {
        // Constructor, though a function, is often better treated as an expandable object.
        if (this._property.name === "constructor")
            return true;

        // Non-function objects are often better treated as properties.
        if (this._property.hasValue() && this._property.value.type !== "function")
            return true;

        // Fetched getter value.
        if (this._getterValue)
            return true;

        return false;
    },

    _functionPropertyString: function()
    {
        return "function" + this._functionParameterString();
    },

    _functionParameterString: function()
    {
        var resolvedValue = this._resolvedValue();
        console.assert(resolvedValue.type === "function");

        // For Native methods, the toString is poor. We try to provide good function parameter strings.
        if (isFunctionStringNativeCode(resolvedValue.description)) {
            // Native function on a prototype, likely "Foo.prototype.method".
            if (this._prototypeName) {
                if (WebInspector.NativePrototypeFunctionParameters[this._prototypeName]) {
                    var params = WebInspector.NativePrototypeFunctionParameters[this._prototypeName][this._property.name];
                    return params ? "(" + params + ")" : "()";
                }
            }

            // Native function property on a native function is likely a "Foo.method".
            if (isFunctionStringNativeCode(this._propertyPath.object.description)) {
                var match = this._propertyPath.object.description.match(/^function\s+([^)]+?)\(/);
                if (match) {
                    var name = match[1];
                    if (WebInspector.NativeConstructorFunctionParameters[name]) {
                        var params = WebInspector.NativeConstructorFunctionParameters[name][this._property.name];
                        return params ? "(" + params + ")" : "()";
                    }
                }
            }
        }        

        var match = resolvedValue.description.match(/^function.*?(\([^)]+?\))/);
        return match ? match[1] : "()";
    },

    _sanitizedPrototypeString: function(value)
    {
        // FIXME: <https://webkit.org/b/141610> For many X, X.prototype is an X when it must be a plain object
        if (value.type === "function")
            return "Function";
        if (value.subtype === "date")
            return "Date";
        if (value.subtype === "regexp")
            return "RegExp";

        return value.description.replace(/\[\d+\]$/, "").replace(/Prototype$/, "");
    },

    _propertyPathString: function(propertyPath)
    {
        if (propertyPath.isFullPathImpossible())
            return WebInspector.UIString("Unable to determine path to property from root");

        return propertyPath.displayPath(this._propertyPathType());
    },

    _updateChildren: function()
    {
        if (this.children.length && !this.shouldRefreshChildren)
            return;

        var resolvedValue = this._resolvedValue();
        if (resolvedValue.isCollectionType() && this._mode === WebInspector.ObjectTreeView.Mode.Properties)
            resolvedValue.getCollectionEntries(0, 100, this._updateChildrenInternal.bind(this, this._updateEntries, this._mode));
        else if (this._property.name === "__proto__")
            resolvedValue.getOwnPropertyDescriptors(this._updateChildrenInternal.bind(this, this._updateProperties, WebInspector.ObjectTreeView.Mode.API));
        else
            resolvedValue.getDisplayablePropertyDescriptors(this._updateChildrenInternal.bind(this, this._updateProperties, this._mode));
    },

    _updateChildrenInternal: function(handler, mode, list)
    {
        this.removeChildren();

        if (!list) {
            var errorMessageElement = WebInspector.ObjectTreeView.emptyMessageElement(WebInspector.UIString("Could not fetch properties. Object may no longer exist."));
            this.appendChild(new TreeElement(errorMessageElement, null, false));
            return;
        }

        handler.call(this, list, this._resolvedValuePropertyPath(), mode);
    },

    _updateEntries: function(entries, propertyPath, mode)
    {
        for (var entry of entries) {
            if (entry.key) {
                this.appendChild(new WebInspector.ObjectTreeMapKeyTreeElement(entry.key, propertyPath));
                this.appendChild(new WebInspector.ObjectTreeMapValueTreeElement(entry.value, propertyPath, entry.key));
            } else
                this.appendChild(new WebInspector.ObjectTreeSetIndexTreeElement(entry.value, propertyPath));
        }

        if (!this.children.length) {
            var emptyMessageElement = WebInspector.ObjectTreeView.emptyMessageElement(WebInspector.UIString("No Entries."));
            this.appendChild(new TreeElement(emptyMessageElement, null, false));
        }

        // Show the prototype so users can see the API.
        var resolvedValue = this._resolvedValue();
        resolvedValue.getOwnPropertyDescriptor("__proto__", function(propertyDescriptor) {
            if (propertyDescriptor)
                this.appendChild(new WebInspector.ObjectTreePropertyTreeElement(propertyDescriptor, propertyPath, mode));
        }.bind(this));
    },

    _updateProperties: function(properties, propertyPath, mode)
    {
        properties.sort(WebInspector.ObjectTreeView.ComparePropertyDescriptors);

        var resolvedValue = this._resolvedValue();
        var isArray = resolvedValue.isArray();
        var isPropertyMode = mode === WebInspector.ObjectTreeView.Mode.Properties || this._getterValue;
        var isAPI = mode === WebInspector.ObjectTreeView.Mode.API;

        var prototypeName = undefined;
        if (this._property.name === "__proto__") {
            if (resolvedValue.description)
                prototypeName = this._sanitizedPrototypeString(resolvedValue);
        }

        for (var propertyDescriptor of properties) {
            // FIXME: If this is a pure API ObjectTree, we should show the native getters.
            // For now, just skip native binding getters in API mode, since we likely
            // already showed them in the Properties section.
            if (isAPI && propertyDescriptor.nativeGetter)
                continue;
            
            if (isArray && isPropertyMode) {
                if (propertyDescriptor.isIndexProperty())
                    this.appendChild(new WebInspector.ObjectTreeArrayIndexTreeElement(propertyDescriptor, propertyPath));
                else if (propertyDescriptor.name === "__proto__")
                    this.appendChild(new WebInspector.ObjectTreePropertyTreeElement(propertyDescriptor, propertyPath, mode, prototypeName));
            } else
                this.appendChild(new WebInspector.ObjectTreePropertyTreeElement(propertyDescriptor, propertyPath, mode, prototypeName));
        }

        if (!this.children.length) {
            var emptyMessageElement = WebInspector.ObjectTreeView.emptyMessageElement(WebInspector.UIString("No Properties."));
            this.appendChild(new TreeElement(emptyMessageElement, null, false));
        }
    },

    _contextMenuHandler: function(event)
    {
        var resolvedValue = this._resolvedValue();
        if (!resolvedValue)
            return;

        var contextMenu = new WebInspector.ContextMenu(event);

        var propertyPath = this._resolvedValuePropertyPath();
        if (propertyPath && !propertyPath.isFullPathImpossible()) {
            contextMenu.appendItem(WebInspector.UIString("Copy Path to Property"), function() {
                InspectorFrontendHost.copyText(propertyPath.displayPath(WebInspector.PropertyPath.Type.Value));
            }.bind(this));
        }

        contextMenu.appendSeparator();

        this._appendMenusItemsForObject(contextMenu, resolvedValue);

        if (!contextMenu.isEmpty())
            contextMenu.show();
    },

    _appendMenusItemsForObject: function(contextMenu, resolvedValue)
    {
        if (resolvedValue.type === "function") {
            // FIXME: We should better handle bound functions.
            if (!isFunctionStringNativeCode(resolvedValue.description)) {
                contextMenu.appendItem(WebInspector.UIString("Jump to Definition"), function() {
                    DebuggerAgent.getFunctionDetails(resolvedValue.objectId, function(error, response) {
                        if (error)
                            return;

                        var location = response.location;
                        var sourceCode = WebInspector.debuggerManager.scriptForIdentifier(location.scriptId);
                        if (!sourceCode)
                            return;

                        var sourceCodeLocation = sourceCode.createSourceCodeLocation(location.lineNumber, location.columnNumber || 0);
                        WebInspector.resourceSidebarPanel.showSourceCodeLocation(sourceCodeLocation);
                    });
                });
            }
            return;
        }

        if (resolvedValue.subtype === "node") {
            contextMenu.appendItem(WebInspector.UIString("Reveal in DOM Tree"), function() {
                resolvedValue.pushNodeToFrontend(function(nodeId) {
                    WebInspector.domTreeManager.inspectElement(nodeId);
                });
            });
            return;
        }
    }
};
