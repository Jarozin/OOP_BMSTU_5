#ifndef class_Iter_h
#define class_Iter_h

#include "BaseIter.h"
#include <memory>
#include <concepts>
#include "my_errors.h"
#include <type_traits>

template <typename Type>
concept VectorType = !
std::is_pointer<Type>::value &&std::copyable<Type> &&std::destructible<Type>;

// random access iterator
template <VectorType Type>
class Vector;

template <VectorType Type>
class Iterator : public BaseIter
{
public:
  using iterator = Iterator;
  using iterator_category = std::random_access_iterator_tag;
  using difference_type = typename Vector<Type>::difference_type;
  using value_type = typename Vector<Type>::value_type;
  using reference = value_type &;
  using pointer = value_type *;
  Iterator(const Iterator<Type> &iter);
  Iterator(Iterator<Type> &&iter);
  Iterator(const Vector<Type> &vec);
  ~Iterator() = default;

  Type &operator*();
  const Type &operator*() const;
  Type *operator->();
  const Type *operator->() const;
  explicit operator bool() const override;

  Iterator<Type> &operator=(const Iterator<Type> &iter);
  Iterator<Type> &operator=(Iterator<Type> &&iter);

  Iterator<Type> &operator+=(int n);
  Iterator<Type> operator+(int n) const;
  Iterator<Type> &operator++();
  Iterator<Type> operator++(int);

  Iterator<Type> &operator-=(int n);
  Iterator<Type> operator-(int n) const;
  Iterator<Type> &operator--();
  Iterator<Type> operator--(int);

  difference_type operator-(const Iterator<Type> &iter);

  Type &operator[](int index) const;

  bool operator<=(const Iterator<Type> &b) const;
  bool operator<(const Iterator<Type> &b) const;
  bool operator>=(const Iterator<Type> &b) const;
  bool operator>(const Iterator<Type> &b) const;
  bool operator==(const Iterator<Type> &b) const;
  bool operator!=(const Iterator<Type> &b) const;

  bool check(int line) const;

private:
  std::weak_ptr<Type[]> ptr_;

protected:
  Type *get_cur_ptr() const;
};

template <VectorType Type>
Iterator<Type> operator+(const int& n, const Iterator<Type> &it)
{
  return it + n;
}

template <VectorType Type>
Type *Iterator<Type>::get_cur_ptr() const
{
  std::shared_ptr<Type[]> copy_ptr = ptr_.lock();
  return copy_ptr.get() + index_;
}

template <VectorType Type>
Iterator<Type>::Iterator(const Vector<Type> &vec)
{
  index_ = 0;
  num_elem_ = vec.num_elem_;
  ptr_ = vec.data_list_;
}

template <VectorType Type>
Iterator<Type>::Iterator(const Iterator<Type> &iter)
{
  ptr_ = iter.ptr_;
  index_ = iter.index_;
  num_elem_ = iter.num_elem_;
}

template <VectorType Type>
Iterator<Type>::Iterator(Iterator<Type> &&iter)
{
  ptr_ = std::move(iter.ptr_);
  index_ = iter.index_;
  num_elem_ = iter.num_elem_;
}

template <VectorType Type>
Type &Iterator<Type>::operator*()
{
  time_t t_time = time(NULL);
  check(__LINE__);
  if (index_ < 0 || index_ >= num_elem_)
    throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  return *get_cur_ptr();
}

template <VectorType Type>
const Type &Iterator<Type>::operator*() const
{
  time_t t_time = time(NULL);
  check(__LINE__);
  if (index_ < 0 || index_ >= num_elem_)
    throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  return *get_cur_ptr();
}

template <VectorType Type>
Type *Iterator<Type>::operator->()
{
  time_t t_time = time(NULL);
  check(__LINE__);
  if (index_ < 0 || index_ >= num_elem_)
    throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  return get_cur_ptr();
}

template <VectorType Type>
const Type *Iterator<Type>::operator->() const
{
  time_t t_time = time(NULL);
  check(__LINE__);
  if (index_ < 0 || index_ >= num_elem_)
    throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  return get_cur_ptr();
}

template <VectorType Type>
Iterator<Type> &Iterator<Type>::operator=(const Iterator<Type> &iter)
{
  check(__LINE__);

  ptr_ = iter.ptr_;
  num_elem_ = iter.num_elem_;
  index_ = iter.index_;
  return *this;
}

template <VectorType Type>
Iterator<Type> &Iterator<Type>::operator=(Iterator<Type> &&iter)
{
  check(__LINE__);

  ptr_ = std::move(iter.ptr_);
  num_elem_ = iter.num_elem_;
  index_ = iter.index_;
  return *this;
}

template <VectorType Type>
Iterator<Type> &Iterator<Type>::operator+=(int n)
{
  check(__LINE__);
  index_ += n;

  return *this;
}

template <VectorType Type>
Iterator<Type> Iterator<Type>::operator+(int n) const
{
  check(__LINE__);
  Iterator<Type> iter(*this);
  iter += n;

  return iter;
}

template <VectorType Type>
Iterator<Type> Iterator<Type>::operator++(int)
{
  check(__LINE__);
  Iterator<Type> new_iter(*this);
  ++(*this);
  return new_iter;
}

template <VectorType Type>
Iterator<Type> &Iterator<Type>::operator++()
{
  check(__LINE__);
  ++index_;

  return *this;
}

template <VectorType Type>
Iterator<Type> &Iterator<Type>::operator-=(int n)
{
  check(__LINE__);
  index_ -= n;

  return *this;
}

template <VectorType Type>
Iterator<Type> Iterator<Type>::operator-(int n) const
{
  check(__LINE__);

  Iterator<Type> iter(*this);
  iter -= n;

  return iter;
}

template <VectorType Type>
Iterator<Type> Iterator<Type>::operator--(int)
{
  check(__LINE__);

  Iterator<Type> new_iter(*this);
  --(*this);

  return new_iter;
}

template <VectorType Type>
Iterator<Type> &Iterator<Type>::operator--()
{
  check(__LINE__);
  --index_;
  return *this;
}

template <VectorType Type>
bool Iterator<Type>::operator<=(const Iterator<Type> &b) const
{
  check(__LINE__);

  return !(*this > b);
}

template <VectorType Type>
bool Iterator<Type>::operator<(const Iterator<Type> &b) const
{
  check(__LINE__);

  return this->get_cur_ptr() + index_ < b.get_cur_ptr() + b.index_;
}

template <VectorType Type>
bool Iterator<Type>::operator>=(const Iterator<Type> &b) const
{
  check(__LINE__);

  return !(*this < b);
}

template <VectorType Type>
bool Iterator<Type>::operator>(const Iterator<Type> &b) const
{
  check(__LINE__);

  return !(*this < b) && !(*this == b);
}

template <VectorType Type>
bool Iterator<Type>::operator==(const Iterator<Type> &b) const
{
  check(__LINE__);

  return this->get_cur_ptr() + index_ == b.get_cur_ptr() + b.index_;
}

template <VectorType Type>
bool Iterator<Type>::operator!=(const Iterator<Type> &b) const
{
  check(__LINE__);

  return !(*this == b);
}

template <VectorType Type>
Type &Iterator<Type>::operator[](int index) const
{
  time_t t_time = time(NULL);
  if (index + this->index_ < 0 || index + this->index_ >= num_elem_)
    throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  return *(*this + index);
}

template <VectorType Type>
Iterator<Type>::operator bool() const
{
  check(__LINE__);

  if (index_ >= num_elem_ || index_ < 0 || (num_elem_ == 0))
    return false;
  return true;
}

template <VectorType Type>
bool Iterator<Type>::check(int line) const
{
  if (!ptr_.expired())
    return true;

  time_t t_time = time(NULL);
  throw deletedObj(__FILE__, typeid(*this).name(), line, ctime(&t_time));
  return false;
}

template <VectorType Type>
typename Iterator<Type>::difference_type Iterator<Type>::operator-(const Iterator<Type> &iter)
{
  if (this->ptr_.lock() != iter.ptr_.lock())
  {
    time_t t_time = time(NULL);
    throw iteratorPtrError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  }
  return index_ - iter.index_;
}

#endif /* class_Iter_h */
