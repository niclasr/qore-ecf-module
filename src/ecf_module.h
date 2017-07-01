#ifndef _ECF_MODULE_H_
#define _ECF_MODULE_H_

#include <config.h>
#include <qore/Qore.h>

QoreStringNode * ecf_module_init();
void ecf_module_ns_init(QoreNamespace *rns, QoreNamespace *qns);
void ecf_module_delete();

#endif
