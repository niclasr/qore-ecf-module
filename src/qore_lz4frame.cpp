/* The MIT License (MIT)
 *
 * Copyright (c) 2015 Niclas Rosenvik
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
#include <lz4frame.h>
#include <qore/Qore.h>

BinaryNode*
qore_lz4frame_compress(const void* ptr, size_t len, int level, ExceptionSink* xsink)
{
  void * lz4_compressed_buf;
  void * lz4_compressed_buf_realloc;
  size_t lz4_error_or_compressed_size;
  size_t lz4_frame_size;
  LZ4F_preferences_t preferences;
  
  memset(&preferences ,0 ,sizeof(preferences));
  preferences.compressionLevel = level;
  preferences.frameInfo.contentSize = len;

  lz4_frame_size = LZ4F_compressFrameBound(len, &preferences);
  lz4_compressed_buf = malloc(lz4_frame_size);
  if (lz4_compressed_buf == NULL) {
    xsink->outOfMemory();
    return 0;
  }

  lz4_error_or_compressed_size = LZ4F_compressFrame(lz4_compressed_buf, lz4_frame_size, ptr, len, &preferences);

  if (LZ4F_isError(lz4_error_or_compressed_size)) {
    xsink->raiseException("LZ4Frame-COMPRESS-ERROR", "LZ4Frame: %s", LZ4F_getErrorName(lz4_error_or_compressed_size));
    free(lz4_compressed_buf);
    return 0;
  }

  lz4_compressed_buf_realloc = realloc(lz4_compressed_buf, lz4_error_or_compressed_size);

  if (lz4_compressed_buf_realloc == NULL) {
    free(lz4_compressed_buf);
    xsink->outOfMemory();
    return 0;
  }
  
  return new BinaryNode(lz4_compressed_buf_realloc, lz4_error_or_compressed_size);
}

BinaryNode*
qore_lz4frame_decompress(const void* ptr, size_t len, ExceptionSink* xsink)
{
  LZ4F_decompressionContext_t lz4_dctx;
  LZ4F_frameInfo_t lz4_frameinfo;
  LZ4F_errorCode_t error;
  LZ4F_decompressOptions_t lz4_options;
  size_t lz4_hint;
  void* lz4_decompressed_buf;
  size_t lz4_decompressed_size;
  size_t lz4_compressed_start_offset;
  size_t lz4_compressed_size;
  const size_t lz4_decompressed_buf_len = 128000;

  
  SimpleRefHolder<BinaryNode> b(new BinaryNode);
  error = LZ4F_createDecompressionContext(&lz4_dctx, LZ4F_VERSION);

  if (LZ4F_isError(error)) {
    xsink->outOfMemory();
    return 0;
  }

  lz4_compressed_size = len;
  lz4_hint = LZ4F_getFrameInfo(lz4_dctx, &lz4_frameinfo, ptr, &lz4_compressed_size);
    
  if (LZ4F_isError(lz4_hint)) {
    xsink->raiseException("LZ4Frame-DECOMPRESS-ERROR", "LZ4F_getFrameInfo failed: %s", LZ4F_getErrorName(lz4_hint));
    LZ4F_freeDecompressionContext(lz4_dctx);
    return 0;
  }

  memset(&lz4_options, 0, sizeof(lz4_options));
  
  lz4_decompressed_buf = malloc(lz4_decompressed_buf_len);
  if (lz4_decompressed_buf == NULL) {
    xsink->outOfMemory();
    LZ4F_freeDecompressionContext(lz4_dctx);
    return 0;
  }
  
  lz4_decompressed_size = lz4_decompressed_buf_len;
  lz4_compressed_start_offset = lz4_compressed_size;
  lz4_compressed_size = len - lz4_compressed_start_offset;
  do {
    lz4_hint = LZ4F_decompress(lz4_dctx, lz4_decompressed_buf, &lz4_decompressed_size, ptr + lz4_compressed_start_offset, &lz4_compressed_size , &lz4_options);
    
    if (LZ4F_isError(lz4_hint)) {
      xsink->raiseException("LZ4Frame-DECOMPRESS-ERROR", "LZ4F_decompress failed: %s", LZ4F_getErrorName(lz4_hint));
      free(lz4_decompressed_buf);
      LZ4F_freeDecompressionContext(lz4_dctx);
      return 0;
    }
    
    b->append(lz4_decompressed_buf, lz4_decompressed_size);
    lz4_decompressed_size = lz4_decompressed_buf_len;
    lz4_compressed_start_offset += lz4_compressed_size;
    lz4_compressed_size = len - lz4_compressed_start_offset;
  } while (lz4_hint);

  free(lz4_decompressed_buf);
  LZ4F_freeDecompressionContext(lz4_dctx);
  return b.release();
}
