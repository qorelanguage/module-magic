#include <qore/Qore.h>
#include "qoremagic.h"


QoreStringNode *magic_module_init();                                                                                
void magic_module_ns_init(QoreNamespace *rns, QoreNamespace *qns);                                                  
void magic_module_delete();                                                                                         

// qore module symbols                                                                                              
DLLEXPORT char qore_module_name[] = "magic";                                                                        
DLLEXPORT char qore_module_version[] = PACKAGE_VERSION;                                                             
DLLEXPORT char qore_module_description[] = "libmagic wrapper";                                                          
DLLEXPORT char qore_module_author[] = "Petr Vanek";                                                                 
DLLEXPORT char qore_module_url[] = "http://qore.org";                                                               
DLLEXPORT int qore_module_api_major = QORE_MODULE_API_MAJOR;                                                        
DLLEXPORT int qore_module_api_minor = QORE_MODULE_API_MINOR;                                                        
DLLEXPORT qore_module_init_t qore_module_init = magic_module_init;                                                  
DLLEXPORT qore_module_ns_init_t qore_module_ns_init = magic_module_ns_init;                                         
DLLEXPORT qore_module_delete_t qore_module_delete = magic_module_delete;                                            
DLLEXPORT qore_license_t qore_module_license = QL_LGPL;


 static QoreNamespace MNS("Magic");


QoreStringNode * magic_module_init() {
    MNS.addSystemClass(initMagicClass(MNS));
    return 0;
}

void magic_module_ns_init(QoreNamespace *rns, QoreNamespace *qns) {
    qns->addInitialNamespace(MNS.copy());
}

void magic_module_delete() {
    // nothing to do here in this case
}

