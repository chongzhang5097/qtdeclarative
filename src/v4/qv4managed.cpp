/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the V4VM module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qv4managed.h"
#include "qv4mm.h"
#include "qv4errorobject.h"

using namespace QQmlJS::VM;

const ManagedVTable Managed::static_vtbl =
{
    call,
    construct,
    0 /*markObjects*/,
    destroy,
    hasInstance,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    "Managed",
};


void *Managed::operator new(size_t size, MemoryManager *mm)
{
    assert(mm);

    return mm->allocManaged(size);
}

void Managed::operator delete(void *ptr)
{
    if (!ptr)
        return;

    Managed *m = static_cast<Managed *>(ptr);
    m->vtbl = 0;
    m->_data = 0;
    m->~Managed();
}

void Managed::operator delete(void *ptr, MemoryManager *mm)
{
    Q_UNUSED(mm);

    operator delete(ptr);
}

QString Managed::className() const
{
    const char *s = 0;
    switch (Type(type)) {
    case Type_Invalid:
    case Type_String:
        return QString();
    case Type_Object:
        s = "Object";
        break;
    case Type_ArrayObject:
        s = "Array";
        break;
    case Type_FunctionObject:
        s = "Function";
        break;
    case Type_BooleanObject:
        s = "Boolean";
        break;
    case Type_NumberObject:
        s = "Number";
        break;
    case Type_StringObject:
        s = "String";
        break;
    case Type_DateObject:
        s = "Date";
        break;
    case Type_RegExpObject:
        s = "RegExp";
        break;
    case Type_ErrorObject:
        switch (ErrorObject::ErrorType(subtype)) {
        case ErrorObject::Error:
            s = "Error";
            break;
        case ErrorObject::EvalError:
            s = "EvalError";
            break;
        case ErrorObject::RangeError:
            s = "RangeError";
            break;
        case ErrorObject::ReferenceError:
            s = "ReferenceError";
            break;
        case ErrorObject::SyntaxError:
            s = "SyntaxError";
            break;
        case ErrorObject::TypeError:
            s = "TypeError";
            break;
        case ErrorObject::URIError:
            s = "URIError";
            break;
        }
        break;
    case Type_ArgumentsObject:
        s = "Arguments";
        break;
    case Type_JSONObject:
        s = "JSON";
        break;
    case Type_MathObject:
        s = "Math";
        break;
    case Type_ForeachIteratorObject:
        s = "__ForeachIterator";
        break;
    }
    return QString::fromLatin1(s);
}

bool Managed::hasInstance(Managed *, ExecutionContext *ctx, const Value &)
{
    ctx->throwTypeError();
}

Value Managed::construct(Managed *, ExecutionContext *context, Value *, int)
{
    context->throwTypeError();
}

Value Managed::call(Managed *, ExecutionContext *context, const Value &, Value *, int)
{
    context->throwTypeError();
}

Value Managed::get(ExecutionContext *ctx, String *name, bool *hasProperty)
{
    return vtbl->get(this, ctx, name, hasProperty);
}

Value Managed::getIndexed(ExecutionContext *ctx, uint index, bool *hasProperty)
{
    return vtbl->getIndexed(this, ctx, index, hasProperty);
}
