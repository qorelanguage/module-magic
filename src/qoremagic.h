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


#ifndef QOREMAGIC_H
#define QOREMAGIC_H

#include <magic.h>


DLLEXPORT extern qore_classid_t CID_MAGIC;
DLLLOCAL extern QoreClass* QC_MAGIC;
DLLLOCAL QoreClass *initMagicClass(QoreNamespace& ns);


class QoreMagic : public AbstractPrivateData {
    protected:
        DLLLOCAL virtual ~QoreMagic();

    public:
        DLLLOCAL QoreMagic(ExceptionSink *xsink);
        DLLLOCAL QoreMagic(int flags, ExceptionSink *xsink);

        DLLLOCAL void setFlags(int flags, ExceptionSink *xsink);

        DLLLOCAL AbstractQoreNode* file(const QoreStringNode *fileName, ExceptionSink *xsink);
        DLLLOCAL AbstractQoreNode* file(const QoreStringNode *fileName, int flags, ExceptionSink *xsink);
        DLLLOCAL AbstractQoreNode* buffer(const AbstractQoreNode *data, ExceptionSink *xsink);
        DLLLOCAL AbstractQoreNode* buffer(const AbstractQoreNode *data, int flags, ExceptionSink *xsink);

    private:
        int m_flags;
        QoreThreadLock m_lock;
};

#endif

