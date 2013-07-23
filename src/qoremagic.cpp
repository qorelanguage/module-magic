/* -*- mode: c++; indent-tabs-mode: nil -*- */
/*
  libmagic Qore wrapper

  Qore Programming Language

  Copyright 2012 - 2013 Qore Technologies

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



bool QoreMagic::checkException(ExceptionSink *xsink)
{
    const char *errmsg = magic_error(m_magic);
    if (errmsg) {
        int err = magic_errno(m_magic);
        xsink->raiseException("MAGIC-ERROR", "ERR-%d: %s", err, errmsg);
        return true;
    }
    return false;
}

QoreMagic::QoreMagic(ExceptionSink *xsink)
{
    setup(MAGIC_NONE, xsink);
}

QoreMagic::QoreMagic(int flags, ExceptionSink *xsink)
{
    setup(flags, xsink);
}

void QoreMagic::setup(int flags, ExceptionSink *xsink)
{
    AutoLocker al(m_lock);

    m_magic = magic_open(flags);
    checkException(xsink);
    if (magic_load(m_magic, 0))
        checkException(xsink);
}

QoreMagic::~QoreMagic()
{
    magic_close(m_magic);
}

void QoreMagic::setFlags(int flags, ExceptionSink *xsink)
{
    AutoLocker al(m_lock);

    if (magic_setflags(m_magic, flags))
        checkException(xsink);
}

AbstractQoreNode* QoreMagic::file(const QoreStringNode *fileName, ExceptionSink *xsink)
{
    AutoLocker al(m_lock);

    const char *ret = magic_file(m_magic, fileName->getBuffer());
    if (checkException(xsink))
        return 0;
    return new QoreStringNode(ret);
}

//AbstractQoreNode* QoreMagic::descriptor(const File *f, ExceptionSink *xsink)
//{
//    ReferenceHolder<File> rh(f, xsink);
//    int fd = rh->getFD();
//    printf("FD: %d\n", fd);
//    const char *ret = magic_descriptor(m_magic, fd);
//
//    if (checkException(xsink))
//        return 0;
//    return new QoreStringNode(ret);
//}

AbstractQoreNode* QoreMagic::buffer(const AbstractQoreNode *data, ExceptionSink *xsink)
{
    AutoLocker al(m_lock);

    qore_type_t qt = data->getType();
    const char *ret;
    if (qt == NT_BINARY) {
        const BinaryNode *s = reinterpret_cast<const BinaryNode*>(data);
        ret = magic_buffer(m_magic, s->getPtr(), s->size());
    }
    else if (qt == NT_STRING) {
        const QoreStringNode *s = reinterpret_cast<const QoreStringNode*>(data);
        ret = magic_buffer(m_magic, s->getBuffer(), s->size());
    }
    else {
        xsink->raiseException("MAGIC-ERROR", "Magic::buffer requires 'data' argument: string or binary. Got: %s", data->getTypeName());
        return 0;
    }
    
    if (checkException(xsink))
        return 0;
    return new QoreStringNode(ret);
}

