/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "JSTestTypedefs.h"

#include "DOMStringList.h"
#include "ExceptionCode.h"
#include "JSDOMBinding.h"
#include "JSDOMStringList.h"
#include "JSSVGPoint.h"
#include "JSSerializedScriptValue.h"
#include "JSTestCallback.h"
#include "JSTestEventTarget.h"
#include "JSTestSubObj.h"
#include "SVGPoint.h"
#include "ScriptExecutionContext.h"
#include "SerializedScriptValue.h"
#include "TestTypedefs.h"
#include "URL.h"
#include <runtime/Error.h>
#include <runtime/JSArray.h>
#include <runtime/JSString.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

// Functions

JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionFunc(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionSetShadow(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionMethodWithSequenceArg(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionNullableArrayArg(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionFuncWithClamp(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionImmutablePointFunction(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionStringArrayFunction(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionStringArrayFunction2(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionCallWithSequenceThatRequiresInclude(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionMethodWithException(JSC::ExecState*);

// Attributes

JSC::EncodedJSValue jsTestTypedefsUnsignedLongLongAttr(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
void setJSTestTypedefsUnsignedLongLongAttr(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
JSC::EncodedJSValue jsTestTypedefsImmutableSerializedScriptValue(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
void setJSTestTypedefsImmutableSerializedScriptValue(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
JSC::EncodedJSValue jsTestTypedefsConstructorTestSubObj(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
JSC::EncodedJSValue jsTestTypedefsAttrWithGetterException(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
void setJSTestTypedefsAttrWithGetterException(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
JSC::EncodedJSValue jsTestTypedefsAttrWithSetterException(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
void setJSTestTypedefsAttrWithSetterException(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
JSC::EncodedJSValue jsTestTypedefsStringAttrWithGetterException(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
void setJSTestTypedefsStringAttrWithGetterException(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
JSC::EncodedJSValue jsTestTypedefsStringAttrWithSetterException(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
void setJSTestTypedefsStringAttrWithSetterException(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
JSC::EncodedJSValue jsTestTypedefsConstructor(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);

class JSTestTypedefsPrototype : public JSC::JSNonFinalObject {
public:
    typedef JSC::JSNonFinalObject Base;
    static JSTestTypedefsPrototype* create(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestTypedefsPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestTypedefsPrototype>(vm.heap)) JSTestTypedefsPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestTypedefsPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};

class JSTestTypedefsConstructor : public DOMConstructorObject {
private:
    JSTestTypedefsConstructor(JSC::Structure*, JSDOMGlobalObject*);
    void finishCreation(JSC::VM&, JSDOMGlobalObject*);

public:
    typedef DOMConstructorObject Base;
    static JSTestTypedefsConstructor* create(JSC::VM& vm, JSC::Structure* structure, JSDOMGlobalObject* globalObject)
    {
        JSTestTypedefsConstructor* ptr = new (NotNull, JSC::allocateCell<JSTestTypedefsConstructor>(vm.heap)) JSTestTypedefsConstructor(structure, globalObject);
        ptr->finishCreation(vm, globalObject);
        return ptr;
    }

    DECLARE_INFO;
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }
protected:
    static JSC::EncodedJSValue JSC_HOST_CALL constructJSTestTypedefs(JSC::ExecState*);
    static JSC::ConstructType getConstructData(JSC::JSCell*, JSC::ConstructData&);
};

/* Hash table */

static const struct CompactHashIndex JSTestTypedefsTableIndex[2] = {
    { -1, -1 },
    { -1, -1 },
};


static const HashTableValue JSTestTypedefsTableValues[] =
{
    { 0, 0, NoIntrinsic, 0, 0 }
};

static const HashTable JSTestTypedefsTable = { 0, 1, false, JSTestTypedefsTableValues, 0, JSTestTypedefsTableIndex };
/* Hash table for constructor */

static const HashTableValue JSTestTypedefsConstructorTableValues[] =
{
    { "TestSubObj", DontDelete | ReadOnly, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestTypedefsConstructorTestSubObj), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) },
};

EncodedJSValue JSC_HOST_CALL JSTestTypedefsConstructor::constructJSTestTypedefs(ExecState* exec)
{
    JSTestTypedefsConstructor* castedThis = jsCast<JSTestTypedefsConstructor*>(exec->callee());
    if (UNLIKELY(exec->argumentCount() < 2))
        return throwVMError(exec, createNotEnoughArgumentsError(exec));
    const String& hello(exec->argument(0).isEmpty() ? String() : exec->argument(0).toString(exec)->value(exec));
    if (UNLIKELY(exec->hadException()))
        return JSValue::encode(jsUndefined());
    if (!exec->argument(1).isFunction())
        return throwArgumentMustBeFunctionError(*exec, 1, "testCallback", "TestTypedefs", nullptr);
    RefPtr<TestCallback> testCallback = JSTestCallback::create(asObject(exec->uncheckedArgument(1)), castedThis->globalObject());
    RefPtr<TestTypedefs> object = TestTypedefs::create(hello, testCallback);
    return JSValue::encode(asObject(toJS(exec, castedThis->globalObject(), object.get())));
}

const ClassInfo JSTestTypedefsConstructor::s_info = { "TestTypedefsConstructor", &Base::s_info, 0, CREATE_METHOD_TABLE(JSTestTypedefsConstructor) };

JSTestTypedefsConstructor::JSTestTypedefsConstructor(Structure* structure, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(structure, globalObject)
{
}

void JSTestTypedefsConstructor::finishCreation(VM& vm, JSDOMGlobalObject* globalObject)
{
    Base::finishCreation(vm);
    ASSERT(inherits(info()));
    putDirect(vm, vm.propertyNames->prototype, JSTestTypedefs::getPrototype(vm, globalObject), DontDelete | ReadOnly);
    putDirect(vm, vm.propertyNames->length, jsNumber(2), ReadOnly | DontDelete | DontEnum);
    reifyStaticProperties(vm, JSTestTypedefsConstructorTableValues, *this);
}

ConstructType JSTestTypedefsConstructor::getConstructData(JSCell*, ConstructData& constructData)
{
    constructData.native.function = constructJSTestTypedefs;
    return ConstructTypeHost;
}

/* Hash table for prototype */

static const HashTableValue JSTestTypedefsPrototypeTableValues[] =
{
    { "constructor", DontEnum | ReadOnly, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestTypedefsConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) },
    { "unsignedLongLongAttr", DontDelete | CustomAccessor, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestTypedefsUnsignedLongLongAttr), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestTypedefsUnsignedLongLongAttr) },
    { "immutableSerializedScriptValue", DontDelete | CustomAccessor, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestTypedefsImmutableSerializedScriptValue), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestTypedefsImmutableSerializedScriptValue) },
    { "attrWithGetterException", DontDelete | CustomAccessor, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestTypedefsAttrWithGetterException), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestTypedefsAttrWithGetterException) },
    { "attrWithSetterException", DontDelete | CustomAccessor, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestTypedefsAttrWithSetterException), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestTypedefsAttrWithSetterException) },
    { "stringAttrWithGetterException", DontDelete | CustomAccessor, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestTypedefsStringAttrWithGetterException), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestTypedefsStringAttrWithGetterException) },
    { "stringAttrWithSetterException", DontDelete | CustomAccessor, NoIntrinsic, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestTypedefsStringAttrWithSetterException), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestTypedefsStringAttrWithSetterException) },
    { "func", JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestTypedefsPrototypeFunctionFunc), (intptr_t) (0) },
    { "setShadow", JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestTypedefsPrototypeFunctionSetShadow), (intptr_t) (3) },
    { "methodWithSequenceArg", JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestTypedefsPrototypeFunctionMethodWithSequenceArg), (intptr_t) (1) },
    { "nullableArrayArg", JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestTypedefsPrototypeFunctionNullableArrayArg), (intptr_t) (1) },
    { "funcWithClamp", JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestTypedefsPrototypeFunctionFuncWithClamp), (intptr_t) (1) },
    { "immutablePointFunction", JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestTypedefsPrototypeFunctionImmutablePointFunction), (intptr_t) (0) },
    { "stringArrayFunction", JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestTypedefsPrototypeFunctionStringArrayFunction), (intptr_t) (1) },
    { "stringArrayFunction2", JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestTypedefsPrototypeFunctionStringArrayFunction2), (intptr_t) (1) },
    { "callWithSequenceThatRequiresInclude", JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestTypedefsPrototypeFunctionCallWithSequenceThatRequiresInclude), (intptr_t) (1) },
    { "methodWithException", JSC::Function, NoIntrinsic, (intptr_t)static_cast<NativeFunction>(jsTestTypedefsPrototypeFunctionMethodWithException), (intptr_t) (0) },
};

WEBCORE_EXPORT const ClassInfo JSTestTypedefsPrototype::s_info = { "TestTypedefsPrototype", &Base::s_info, 0, CREATE_METHOD_TABLE(JSTestTypedefsPrototype) };

void JSTestTypedefsPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestTypedefsPrototypeTableValues, *this);
}

WEBCORE_EXPORT const ClassInfo JSTestTypedefs::s_info = { "TestTypedefs", &Base::s_info, &JSTestTypedefsTable, CREATE_METHOD_TABLE(JSTestTypedefs) };

JSTestTypedefs::JSTestTypedefs(Structure* structure, JSDOMGlobalObject* globalObject, PassRefPtr<TestTypedefs> impl)
    : JSDOMWrapper(structure, globalObject)
    , m_impl(impl.leakRef())
{
}

JSObject* JSTestTypedefs::createPrototype(VM& vm, JSGlobalObject* globalObject)
{
    return JSTestTypedefsPrototype::create(vm, globalObject, JSTestTypedefsPrototype::createStructure(vm, globalObject, globalObject->objectPrototype()));
}

JSObject* JSTestTypedefs::getPrototype(VM& vm, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSTestTypedefs>(vm, globalObject);
}

void JSTestTypedefs::destroy(JSC::JSCell* cell)
{
    JSTestTypedefs* thisObject = static_cast<JSTestTypedefs*>(cell);
    thisObject->JSTestTypedefs::~JSTestTypedefs();
}

JSTestTypedefs::~JSTestTypedefs()
{
    releaseImplIfNotNull();
}

bool JSTestTypedefs::getOwnPropertySlot(JSObject* object, ExecState* exec, PropertyName propertyName, PropertySlot& slot)
{
    JSTestTypedefs* thisObject = jsCast<JSTestTypedefs*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    return getStaticValueSlot<JSTestTypedefs, Base>(exec, JSTestTypedefsTable, thisObject, propertyName, slot);
}

EncodedJSValue jsTestTypedefsUnsignedLongLongAttr(ExecState* exec, JSObject* slotBase, EncodedJSValue thisValue, PropertyName)
{
    UNUSED_PARAM(exec);
    UNUSED_PARAM(slotBase);
    UNUSED_PARAM(thisValue);
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(JSValue::decode(thisValue));
    if (UNLIKELY(!castedThis)) {
        if (jsDynamicCast<JSTestTypedefsPrototype*>(slotBase))
            return reportDeprecatedGetterError(*exec, "TestTypedefs", "unsignedLongLongAttr");
        return throwGetterTypeError(*exec, "TestTypedefs", "unsignedLongLongAttr");
    }
    TestTypedefs& impl = castedThis->impl();
    JSValue result = jsNumber(impl.unsignedLongLongAttr());
    return JSValue::encode(result);
}


EncodedJSValue jsTestTypedefsImmutableSerializedScriptValue(ExecState* exec, JSObject* slotBase, EncodedJSValue thisValue, PropertyName)
{
    UNUSED_PARAM(exec);
    UNUSED_PARAM(slotBase);
    UNUSED_PARAM(thisValue);
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(JSValue::decode(thisValue));
    if (UNLIKELY(!castedThis)) {
        if (jsDynamicCast<JSTestTypedefsPrototype*>(slotBase))
            return reportDeprecatedGetterError(*exec, "TestTypedefs", "immutableSerializedScriptValue");
        return throwGetterTypeError(*exec, "TestTypedefs", "immutableSerializedScriptValue");
    }
    TestTypedefs& impl = castedThis->impl();
    JSValue result = impl.immutableSerializedScriptValue() ? impl.immutableSerializedScriptValue()->deserialize(exec, castedThis->globalObject(), 0) : jsNull();
    return JSValue::encode(result);
}


EncodedJSValue jsTestTypedefsConstructorTestSubObj(ExecState* exec, JSObject* slotBase, EncodedJSValue thisValue, PropertyName)
{
    UNUSED_PARAM(exec);
    UNUSED_PARAM(slotBase);
    UNUSED_PARAM(thisValue);
    JSTestTypedefs* castedThis = jsCast<JSTestTypedefs*>(slotBase);
    return JSValue::encode(JSTestSubObj::getConstructor(exec->vm(), castedThis->globalObject()));
}


EncodedJSValue jsTestTypedefsAttrWithGetterException(ExecState* exec, JSObject* slotBase, EncodedJSValue thisValue, PropertyName)
{
    UNUSED_PARAM(exec);
    UNUSED_PARAM(slotBase);
    UNUSED_PARAM(thisValue);
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(JSValue::decode(thisValue));
    if (UNLIKELY(!castedThis)) {
        if (jsDynamicCast<JSTestTypedefsPrototype*>(slotBase))
            return reportDeprecatedGetterError(*exec, "TestTypedefs", "attrWithGetterException");
        return throwGetterTypeError(*exec, "TestTypedefs", "attrWithGetterException");
    }
    ExceptionCode ec = 0;
    TestTypedefs& impl = castedThis->impl();
    JSValue result = jsNumber(impl.attrWithGetterException(ec));
    setDOMException(exec, ec);
    return JSValue::encode(result);
}


EncodedJSValue jsTestTypedefsAttrWithSetterException(ExecState* exec, JSObject* slotBase, EncodedJSValue thisValue, PropertyName)
{
    UNUSED_PARAM(exec);
    UNUSED_PARAM(slotBase);
    UNUSED_PARAM(thisValue);
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(JSValue::decode(thisValue));
    if (UNLIKELY(!castedThis)) {
        if (jsDynamicCast<JSTestTypedefsPrototype*>(slotBase))
            return reportDeprecatedGetterError(*exec, "TestTypedefs", "attrWithSetterException");
        return throwGetterTypeError(*exec, "TestTypedefs", "attrWithSetterException");
    }
    TestTypedefs& impl = castedThis->impl();
    JSValue result = jsNumber(impl.attrWithSetterException());
    return JSValue::encode(result);
}


EncodedJSValue jsTestTypedefsStringAttrWithGetterException(ExecState* exec, JSObject* slotBase, EncodedJSValue thisValue, PropertyName)
{
    UNUSED_PARAM(exec);
    UNUSED_PARAM(slotBase);
    UNUSED_PARAM(thisValue);
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(JSValue::decode(thisValue));
    if (UNLIKELY(!castedThis)) {
        if (jsDynamicCast<JSTestTypedefsPrototype*>(slotBase))
            return reportDeprecatedGetterError(*exec, "TestTypedefs", "stringAttrWithGetterException");
        return throwGetterTypeError(*exec, "TestTypedefs", "stringAttrWithGetterException");
    }
    ExceptionCode ec = 0;
    TestTypedefs& impl = castedThis->impl();
    JSValue result = jsStringWithCache(exec, impl.stringAttrWithGetterException(ec));
    setDOMException(exec, ec);
    return JSValue::encode(result);
}


EncodedJSValue jsTestTypedefsStringAttrWithSetterException(ExecState* exec, JSObject* slotBase, EncodedJSValue thisValue, PropertyName)
{
    UNUSED_PARAM(exec);
    UNUSED_PARAM(slotBase);
    UNUSED_PARAM(thisValue);
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(JSValue::decode(thisValue));
    if (UNLIKELY(!castedThis)) {
        if (jsDynamicCast<JSTestTypedefsPrototype*>(slotBase))
            return reportDeprecatedGetterError(*exec, "TestTypedefs", "stringAttrWithSetterException");
        return throwGetterTypeError(*exec, "TestTypedefs", "stringAttrWithSetterException");
    }
    TestTypedefs& impl = castedThis->impl();
    JSValue result = jsStringWithCache(exec, impl.stringAttrWithSetterException());
    return JSValue::encode(result);
}


EncodedJSValue jsTestTypedefsConstructor(ExecState* exec, JSObject* baseValue, EncodedJSValue, PropertyName)
{
    JSTestTypedefsPrototype* domObject = jsDynamicCast<JSTestTypedefsPrototype*>(baseValue);
    if (!domObject)
        return throwVMTypeError(exec);
    return JSValue::encode(JSTestTypedefs::getConstructor(exec->vm(), domObject->globalObject()));
}

void setJSTestTypedefsUnsignedLongLongAttr(ExecState* exec, JSObject* baseObject, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    JSValue value = JSValue::decode(encodedValue);
    UNUSED_PARAM(baseObject);
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(JSValue::decode(thisValue));
    if (UNLIKELY(!castedThis)) {
        if (jsDynamicCast<JSTestTypedefsPrototype*>(JSValue::decode(thisValue)))
            reportDeprecatedSetterError(*exec, "TestTypedefs", "unsignedLongLongAttr");
        else
            throwSetterTypeError(*exec, "TestTypedefs", "unsignedLongLongAttr");
        return;
    }
    TestTypedefs& impl = castedThis->impl();
    unsigned long long nativeValue(toUInt64(exec, value, NormalConversion));
    if (UNLIKELY(exec->hadException()))
        return;
    impl.setUnsignedLongLongAttr(nativeValue);
}


void setJSTestTypedefsImmutableSerializedScriptValue(ExecState* exec, JSObject* baseObject, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    JSValue value = JSValue::decode(encodedValue);
    UNUSED_PARAM(baseObject);
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(JSValue::decode(thisValue));
    if (UNLIKELY(!castedThis)) {
        if (jsDynamicCast<JSTestTypedefsPrototype*>(JSValue::decode(thisValue)))
            reportDeprecatedSetterError(*exec, "TestTypedefs", "immutableSerializedScriptValue");
        else
            throwSetterTypeError(*exec, "TestTypedefs", "immutableSerializedScriptValue");
        return;
    }
    TestTypedefs& impl = castedThis->impl();
    RefPtr<SerializedScriptValue> nativeValue(SerializedScriptValue::create(exec, value, 0, 0));
    if (UNLIKELY(exec->hadException()))
        return;
    impl.setImmutableSerializedScriptValue(nativeValue);
}


void setJSTestTypedefsAttrWithGetterException(ExecState* exec, JSObject* baseObject, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    JSValue value = JSValue::decode(encodedValue);
    UNUSED_PARAM(baseObject);
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(JSValue::decode(thisValue));
    if (UNLIKELY(!castedThis)) {
        if (jsDynamicCast<JSTestTypedefsPrototype*>(JSValue::decode(thisValue)))
            reportDeprecatedSetterError(*exec, "TestTypedefs", "attrWithGetterException");
        else
            throwSetterTypeError(*exec, "TestTypedefs", "attrWithGetterException");
        return;
    }
    TestTypedefs& impl = castedThis->impl();
    int nativeValue(toInt32(exec, value, NormalConversion));
    if (UNLIKELY(exec->hadException()))
        return;
    impl.setAttrWithGetterException(nativeValue);
}


void setJSTestTypedefsAttrWithSetterException(ExecState* exec, JSObject* baseObject, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    JSValue value = JSValue::decode(encodedValue);
    UNUSED_PARAM(baseObject);
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(JSValue::decode(thisValue));
    if (UNLIKELY(!castedThis)) {
        if (jsDynamicCast<JSTestTypedefsPrototype*>(JSValue::decode(thisValue)))
            reportDeprecatedSetterError(*exec, "TestTypedefs", "attrWithSetterException");
        else
            throwSetterTypeError(*exec, "TestTypedefs", "attrWithSetterException");
        return;
    }
    TestTypedefs& impl = castedThis->impl();
    ExceptionCode ec = 0;
    int nativeValue(toInt32(exec, value, NormalConversion));
    if (UNLIKELY(exec->hadException()))
        return;
    impl.setAttrWithSetterException(nativeValue, ec);
    setDOMException(exec, ec);
}


void setJSTestTypedefsStringAttrWithGetterException(ExecState* exec, JSObject* baseObject, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    JSValue value = JSValue::decode(encodedValue);
    UNUSED_PARAM(baseObject);
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(JSValue::decode(thisValue));
    if (UNLIKELY(!castedThis)) {
        if (jsDynamicCast<JSTestTypedefsPrototype*>(JSValue::decode(thisValue)))
            reportDeprecatedSetterError(*exec, "TestTypedefs", "stringAttrWithGetterException");
        else
            throwSetterTypeError(*exec, "TestTypedefs", "stringAttrWithGetterException");
        return;
    }
    TestTypedefs& impl = castedThis->impl();
    const String& nativeValue(value.isEmpty() ? String() : value.toString(exec)->value(exec));
    if (UNLIKELY(exec->hadException()))
        return;
    impl.setStringAttrWithGetterException(nativeValue);
}


void setJSTestTypedefsStringAttrWithSetterException(ExecState* exec, JSObject* baseObject, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    JSValue value = JSValue::decode(encodedValue);
    UNUSED_PARAM(baseObject);
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(JSValue::decode(thisValue));
    if (UNLIKELY(!castedThis)) {
        if (jsDynamicCast<JSTestTypedefsPrototype*>(JSValue::decode(thisValue)))
            reportDeprecatedSetterError(*exec, "TestTypedefs", "stringAttrWithSetterException");
        else
            throwSetterTypeError(*exec, "TestTypedefs", "stringAttrWithSetterException");
        return;
    }
    TestTypedefs& impl = castedThis->impl();
    ExceptionCode ec = 0;
    const String& nativeValue(value.isEmpty() ? String() : value.toString(exec)->value(exec));
    if (UNLIKELY(exec->hadException()))
        return;
    impl.setStringAttrWithSetterException(nativeValue, ec);
    setDOMException(exec, ec);
}


JSValue JSTestTypedefs::getConstructor(VM& vm, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestTypedefsConstructor>(vm, jsCast<JSDOMGlobalObject*>(globalObject));
}

EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionFunc(ExecState* exec)
{
    JSValue thisValue = exec->thisValue();
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(thisValue);
    if (UNLIKELY(!castedThis))
        return throwThisTypeError(*exec, "TestTypedefs", "func");
    ASSERT_GC_OBJECT_INHERITS(castedThis, JSTestTypedefs::info());
    TestTypedefs& impl = castedThis->impl();

    size_t argsCount = exec->argumentCount();
    if (argsCount <= 0) {
        impl.func();
        return JSValue::encode(jsUndefined());
    }

    Vector<int> x(toNativeArray<int>(exec, exec->argument(0)));
    if (UNLIKELY(exec->hadException()))
        return JSValue::encode(jsUndefined());
    impl.func(x);
    return JSValue::encode(jsUndefined());
}

EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionSetShadow(ExecState* exec)
{
    JSValue thisValue = exec->thisValue();
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(thisValue);
    if (UNLIKELY(!castedThis))
        return throwThisTypeError(*exec, "TestTypedefs", "setShadow");
    ASSERT_GC_OBJECT_INHERITS(castedThis, JSTestTypedefs::info());
    TestTypedefs& impl = castedThis->impl();
    if (UNLIKELY(exec->argumentCount() < 3))
        return throwVMError(exec, createNotEnoughArgumentsError(exec));
    float width(exec->argument(0).toFloat(exec));
    if (UNLIKELY(exec->hadException()))
        return JSValue::encode(jsUndefined());
    float height(exec->argument(1).toFloat(exec));
    if (UNLIKELY(exec->hadException()))
        return JSValue::encode(jsUndefined());
    float blur(exec->argument(2).toFloat(exec));
    if (UNLIKELY(exec->hadException()))
        return JSValue::encode(jsUndefined());

    size_t argsCount = exec->argumentCount();
    if (argsCount <= 3) {
        impl.setShadow(width, height, blur);
        return JSValue::encode(jsUndefined());
    }

    const String& color(exec->argument(3).isEmpty() ? String() : exec->argument(3).toString(exec)->value(exec));
    if (UNLIKELY(exec->hadException()))
        return JSValue::encode(jsUndefined());
    if (argsCount <= 4) {
        impl.setShadow(width, height, blur, color);
        return JSValue::encode(jsUndefined());
    }

    float alpha(exec->argument(4).toFloat(exec));
    if (UNLIKELY(exec->hadException()))
        return JSValue::encode(jsUndefined());
    impl.setShadow(width, height, blur, color, alpha);
    return JSValue::encode(jsUndefined());
}

EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionMethodWithSequenceArg(ExecState* exec)
{
    JSValue thisValue = exec->thisValue();
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(thisValue);
    if (UNLIKELY(!castedThis))
        return throwThisTypeError(*exec, "TestTypedefs", "methodWithSequenceArg");
    ASSERT_GC_OBJECT_INHERITS(castedThis, JSTestTypedefs::info());
    TestTypedefs& impl = castedThis->impl();
    if (UNLIKELY(exec->argumentCount() < 1))
        return throwVMError(exec, createNotEnoughArgumentsError(exec));
    Vector<RefPtr<SerializedScriptValue>> sequenceArg((toRefPtrNativeArray<SerializedScriptValue, JSSerializedScriptValue>(exec, exec->argument(0), &JSSerializedScriptValue::toWrapped)));
    if (UNLIKELY(exec->hadException()))
        return JSValue::encode(jsUndefined());
    JSValue result = jsNumber(impl.methodWithSequenceArg(sequenceArg));
    return JSValue::encode(result);
}

EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionNullableArrayArg(ExecState* exec)
{
    JSValue thisValue = exec->thisValue();
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(thisValue);
    if (UNLIKELY(!castedThis))
        return throwThisTypeError(*exec, "TestTypedefs", "nullableArrayArg");
    ASSERT_GC_OBJECT_INHERITS(castedThis, JSTestTypedefs::info());
    TestTypedefs& impl = castedThis->impl();
    if (UNLIKELY(exec->argumentCount() < 1))
        return throwVMError(exec, createNotEnoughArgumentsError(exec));
    Vector<String> arrayArg(toNativeArray<String>(exec, exec->argument(0)));
    if (UNLIKELY(exec->hadException()))
        return JSValue::encode(jsUndefined());
    impl.nullableArrayArg(arrayArg);
    return JSValue::encode(jsUndefined());
}

EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionFuncWithClamp(ExecState* exec)
{
    JSValue thisValue = exec->thisValue();
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(thisValue);
    if (UNLIKELY(!castedThis))
        return throwThisTypeError(*exec, "TestTypedefs", "funcWithClamp");
    ASSERT_GC_OBJECT_INHERITS(castedThis, JSTestTypedefs::info());
    TestTypedefs& impl = castedThis->impl();
    if (UNLIKELY(exec->argumentCount() < 1))
        return throwVMError(exec, createNotEnoughArgumentsError(exec));
    unsigned long long arg1 = 0;
    double arg1NativeValue = exec->argument(0).toNumber(exec);
    if (UNLIKELY(exec->hadException()))
        return JSValue::encode(jsUndefined());

    if (!std::isnan(arg1NativeValue))
        arg1 = clampTo<unsigned long long>(arg1NativeValue);


    size_t argsCount = exec->argumentCount();
    if (argsCount <= 1) {
        impl.funcWithClamp(arg1);
        return JSValue::encode(jsUndefined());
    }

    unsigned long long arg2 = 0;
    double arg2NativeValue = exec->argument(1).toNumber(exec);
    if (UNLIKELY(exec->hadException()))
        return JSValue::encode(jsUndefined());

    if (!std::isnan(arg2NativeValue))
        arg2 = clampTo<unsigned long long>(arg2NativeValue);

    impl.funcWithClamp(arg1, arg2);
    return JSValue::encode(jsUndefined());
}

EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionImmutablePointFunction(ExecState* exec)
{
    JSValue thisValue = exec->thisValue();
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(thisValue);
    if (UNLIKELY(!castedThis))
        return throwThisTypeError(*exec, "TestTypedefs", "immutablePointFunction");
    ASSERT_GC_OBJECT_INHERITS(castedThis, JSTestTypedefs::info());
    TestTypedefs& impl = castedThis->impl();
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(SVGPropertyTearOff<SVGPoint>::create(impl.immutablePointFunction())));
    return JSValue::encode(result);
}

EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionStringArrayFunction(ExecState* exec)
{
    JSValue thisValue = exec->thisValue();
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(thisValue);
    if (UNLIKELY(!castedThis))
        return throwThisTypeError(*exec, "TestTypedefs", "stringArrayFunction");
    ASSERT_GC_OBJECT_INHERITS(castedThis, JSTestTypedefs::info());
    TestTypedefs& impl = castedThis->impl();
    if (UNLIKELY(exec->argumentCount() < 1))
        return throwVMError(exec, createNotEnoughArgumentsError(exec));
    ExceptionCode ec = 0;
    Vector<String> values(toNativeArray<String>(exec, exec->argument(0)));
    if (UNLIKELY(exec->hadException()))
        return JSValue::encode(jsUndefined());
    JSValue result = jsArray(exec, castedThis->globalObject(), impl.stringArrayFunction(values, ec));

    setDOMException(exec, ec);
    return JSValue::encode(result);
}

EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionStringArrayFunction2(ExecState* exec)
{
    JSValue thisValue = exec->thisValue();
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(thisValue);
    if (UNLIKELY(!castedThis))
        return throwThisTypeError(*exec, "TestTypedefs", "stringArrayFunction2");
    ASSERT_GC_OBJECT_INHERITS(castedThis, JSTestTypedefs::info());
    TestTypedefs& impl = castedThis->impl();
    if (UNLIKELY(exec->argumentCount() < 1))
        return throwVMError(exec, createNotEnoughArgumentsError(exec));
    ExceptionCode ec = 0;
    Vector<String> values(toNativeArray<String>(exec, exec->argument(0)));
    if (UNLIKELY(exec->hadException()))
        return JSValue::encode(jsUndefined());
    JSValue result = jsArray(exec, castedThis->globalObject(), impl.stringArrayFunction2(values, ec));

    setDOMException(exec, ec);
    return JSValue::encode(result);
}

EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionCallWithSequenceThatRequiresInclude(ExecState* exec)
{
    JSValue thisValue = exec->thisValue();
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(thisValue);
    if (UNLIKELY(!castedThis))
        return throwThisTypeError(*exec, "TestTypedefs", "callWithSequenceThatRequiresInclude");
    ASSERT_GC_OBJECT_INHERITS(castedThis, JSTestTypedefs::info());
    TestTypedefs& impl = castedThis->impl();
    if (UNLIKELY(exec->argumentCount() < 1))
        return throwVMError(exec, createNotEnoughArgumentsError(exec));
    Vector<RefPtr<TestEventTarget>> sequenceArg((toRefPtrNativeArray<TestEventTarget, JSTestEventTarget>(exec, exec->argument(0), &JSTestEventTarget::toWrapped)));
    if (UNLIKELY(exec->hadException()))
        return JSValue::encode(jsUndefined());
    JSValue result = jsBoolean(impl.callWithSequenceThatRequiresInclude(sequenceArg));
    return JSValue::encode(result);
}

EncodedJSValue JSC_HOST_CALL jsTestTypedefsPrototypeFunctionMethodWithException(ExecState* exec)
{
    JSValue thisValue = exec->thisValue();
    JSTestTypedefs* castedThis = jsDynamicCast<JSTestTypedefs*>(thisValue);
    if (UNLIKELY(!castedThis))
        return throwThisTypeError(*exec, "TestTypedefs", "methodWithException");
    ASSERT_GC_OBJECT_INHERITS(castedThis, JSTestTypedefs::info());
    TestTypedefs& impl = castedThis->impl();
    ExceptionCode ec = 0;
    impl.methodWithException(ec);
    setDOMException(exec, ec);
    return JSValue::encode(jsUndefined());
}

bool JSTestTypedefsOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    return false;
}

void JSTestTypedefsOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    JSTestTypedefs* jsTestTypedefs = jsCast<JSTestTypedefs*>(handle.slot()->asCell());
    DOMWrapperWorld& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsTestTypedefs->impl(), jsTestTypedefs);
    jsTestTypedefs->releaseImpl();
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestTypedefs@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore12TestTypedefsE[]; }
#endif
#endif
JSC::JSValue toJS(JSC::ExecState*, JSDOMGlobalObject* globalObject, TestTypedefs* impl)
{
    if (!impl)
        return jsNull();
    if (JSValue result = getExistingWrapper<JSTestTypedefs>(globalObject, impl))
        return result;

#if ENABLE(BINDING_INTEGRITY)
    void* actualVTablePointer = *(reinterpret_cast<void**>(impl));
#if PLATFORM(WIN)
    void* expectedVTablePointer = reinterpret_cast<void*>(__identifier("??_7TestTypedefs@WebCore@@6B@"));
#else
    void* expectedVTablePointer = &_ZTVN7WebCore12TestTypedefsE[2];
#if COMPILER(CLANG)
    // If this fails TestTypedefs does not have a vtable, so you need to add the
    // ImplementationLacksVTable attribute to the interface definition
    COMPILE_ASSERT(__is_polymorphic(TestTypedefs), TestTypedefs_is_not_polymorphic);
#endif
#endif
    // If you hit this assertion you either have a use after free bug, or
    // TestTypedefs has subclasses. If TestTypedefs has subclasses that get passed
    // to toJS() we currently require TestTypedefs you to opt out of binding hardening
    // by adding the SkipVTableValidation attribute to the interface IDL definition
    RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    return createNewWrapper<JSTestTypedefs>(globalObject, impl);
}

TestTypedefs* JSTestTypedefs::toWrapped(JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestTypedefs*>(value))
        return &wrapper->impl();
    return nullptr;
}

}
