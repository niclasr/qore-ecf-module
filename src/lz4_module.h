#ifndef _LZ4_MODULE_H_
#define _LZ4_MODULE_H_

#include <config.h>
#include <qore/Qore.h>

QoreStringNode * lz4_module_init();
void lz4_module_ns_init(QoreNamespace *rns, QoreNamespace *qns);
void lz4_module_delete();

#endif
