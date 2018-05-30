/* -*- mode: c++; indent-tabs-mode: nil -*- */
/*
    libmagic Qore wrapper

    Qore Programming Language

    Copyright 2012 - 2018 Qore Technologies, s.r.o.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <qore/Qore.h>
#include "qoremagic.h"


class MagicHelper
{
    magic_t m_magic;

public:
    MagicHelper(int flags, ExceptionSink *xsink) {
        m_magic = magic_open(flags);
        if (m_magic == NULL)
            checkException(xsink);
	if (magic_load(m_magic, 0) == -1)
            checkException(xsink);
    }

    ~MagicHelper() {
        magic_close(m_magic);
    }

    magic_t* magic() {
        return &m_magic;
    }

    const char* file(const char *fname) {
        return magic_file(m_magic, fname);
    }

    const char* buffer(const void *data, size_t len) {
        return magic_buffer(m_magic, data, len);
    }

    bool checkException(ExceptionSink *xsink)
    {
        const char *errmsg = magic_error(m_magic);
        if (errmsg) {
            int err = magic_errno(m_magic);
            xsink->raiseException("MAGIC-ERROR", "ERR-%d: %s", err, errmsg);
            return true;
        }
        return false;
    }
};


QoreMagic::QoreMagic(ExceptionSink *xsink)
{
    m_flags = MAGIC_NONE;
}

QoreMagic::QoreMagic(int flags, ExceptionSink *xsink)
{
    m_flags = flags;
}

QoreMagic::~QoreMagic()
{
}

void QoreMagic::setFlags(int flags, ExceptionSink *xsink)
{
    AutoLocker al(m_lock);
    m_flags = flags;
}

AbstractQoreNode* QoreMagic::file(const QoreStringNode *fileName, ExceptionSink *xsink)
{
    return file(fileName, m_flags, xsink);
}

AbstractQoreNode* QoreMagic::file(const QoreStringNode *fileName, int flags, ExceptionSink *xsink)
{
    AutoLocker al(m_lock);

    MagicHelper magic(flags, xsink);

    if (*xsink)
        return 0;

    const char *ret = magic.file(fileName->getBuffer());

    if (magic.checkException(xsink))
        return 0;

    return new QoreStringNode(ret);
}

AbstractQoreNode* QoreMagic::buffer(QoreValue data, ExceptionSink *xsink)
{
    return buffer(data, m_flags, xsink);
}

AbstractQoreNode* QoreMagic::buffer(QoreValue data, int flags, ExceptionSink *xsink)
{
    AutoLocker al(m_lock);

    MagicHelper magic(flags, xsink);

    if (*xsink)
        return 0;

    qore_type_t qt = data.getType();
    const char *ret;
    if (qt == NT_BINARY) {
        const BinaryNode* s = data.get<const BinaryNode>();
        ret = magic.buffer(s->getPtr(), s->size());
    }
    else if (qt == NT_STRING) {
        const QoreStringNode* s = data.get<const QoreStringNode>();
        ret = magic.buffer(s->c_str(), s->size());
    }
    else {
        xsink->raiseException("MAGIC-ERROR", "Magic::buffer requires 'data' argument: string or binary. Got: %s", data.getTypeName());
        return 0;
    }

    if (magic.checkException(xsink))
        return 0;

    return new QoreStringNode(ret);
}

