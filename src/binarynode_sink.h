#ifndef _BINARYNODE_SINK_H_
#define _BINARYNODE_SINK_H_

#include <qore/Qore.h>
#include <snappy-sinksource.h>

class binarynode_sink : public snappy::Sink {
 public:
  binarynode_sink(BinaryNode* abn) : pbn(abn) {} 
  ~binarynode_sink();
  void Append(const char* bytes, size_t n);
 private:
  BinaryNode* pbn;
};

#endif
