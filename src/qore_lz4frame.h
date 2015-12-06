#ifndef _QORE_LZ4FRAME_H_
#define _QORE_LZ4FRAME_H_

#include <config.h>
#include <qore/Qore.h>

DLLLOCAL BinaryNode* qore_lz4frame_compress(const void* ptr, size_t len, int level, ExceptionSink* xsink);
DLLLOCAL BinaryNode* qore_lz4frame_decompress(const void* ptr, size_t len, ExceptionSink* xsink);

#endif
