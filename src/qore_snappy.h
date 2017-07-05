#ifndef _QORE_SNAPPY_H_
#define _QORE_SNAPPY_H_

#include <config.h>
#include <qore/Qore.h>

DLLLOCAL BinaryNode* qore_snappy_function(const void* ptr, size_t len, ExceptionSink* xsink, bool compress);

#endif
