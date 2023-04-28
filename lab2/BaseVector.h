#ifndef BaseVector_h
#define BaseVector_h
#include "Iterator.h"

template <VectorType Type>
class Iterator;

class BaseVector
{
public:
  BaseVector();
  BaseVector(const BaseVector &);
  virtual ~BaseVector() = 0;


  virtual int size() const = 0;

protected:
  int num_elem_ = 0;
};

#endif /* BaseVector_h */
