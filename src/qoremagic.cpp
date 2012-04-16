/* -*- mode: c++; indent-tabs-mode: nil -*- */

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
    if (magic_setflags(m_magic, flags))
        checkException(xsink);
}

AbstractQoreNode* QoreMagic::file(const QoreStringNode *fileName, ExceptionSink *xsink)
{
    const char *ret = magic_file(m_magic, fileName->getBuffer());
    if (checkException(xsink))
        return 0;
    return new QoreStringNode(ret);
}

