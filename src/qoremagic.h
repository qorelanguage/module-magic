/* -*- mode: c++; indent-tabs-mode: nil -*- */

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
//        DLLLOCAL AbstractQoreNode* descriptor(const File *f, ExceptionSink *xsink);
        DLLLOCAL AbstractQoreNode* buffer(const AbstractQoreNode *data, ExceptionSink *xsink);

    private:
        magic_t m_magic;   

        void setup(int flags, ExceptionSink *xsink);
        bool checkException(ExceptionSink *xsink);
};

#endif

