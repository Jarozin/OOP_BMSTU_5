#ifndef BaseVector_h
#define BaseVector_h

template <typename Type>
class Iterator;

class BaseVector
{
public:
  BaseVector();
  BaseVector(const BaseVector &);
  virtual ~BaseVector(){};

  bool is_empty() const;
  int get_size() const;
  virtual int size() const = 0;

protected:
  int num_elem_ = 0;
};

#endif /* BaseVector_h */
