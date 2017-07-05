/* The MIT License (MIT)
 *
 * Copyright (c) 2017 Niclas Rosenvik <youremailsarecrap@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <config.h>
#include <qore/Qore.h>
#include <snappy.h>
#include <snappy-sinksource.h>

#include "binarynode_sink.h"

BinaryNode*
qore_snappy_function(const void* ptr, size_t len, ExceptionSink* xsink, bool compress)
{
  const char* cptr = (char*)ptr;
  snappy::ByteArraySource local_source(cptr, len); 
  ReferenceHolder<BinaryNode> rbn(new BinaryNode(), xsink);
  binarynode_sink local_sink(rbn.getRef());
 
  size_t snappy_bytes;
  bool snappy_success;
  if (compress) {
    snappy_bytes = snappy::Compress(&local_source, &local_sink);
  }
  else {
    if (!snappy::Uncompress(&local_source, &local_sink)) {
      xsink->raiseException("SNAPPY-UNCOMPRESS-ERROR", "");
      return 0;
    }
  }
  
  return rbn.release();
}
