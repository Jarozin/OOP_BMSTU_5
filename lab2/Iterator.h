#ifndef class_Iter_h
#define class_Iter_h

#include "BaseIter.h"
#include <memory>
#include "my_errors.h"

template <typename Type>
class Vector;

template <typename Type>
class Iterator : public BaseIter
{
public:
  Iterator(const Iterator<Type> &iter);
  Iterator(Iterator<Type> &&iter);
  Iterator(const Vector<Type> &vec);
  ~Iterator() = default;

  Type &operator*();
  const Type &operator*() const;
  Type *operator->();
  const Type *operator->() const;
  operator bool() const override;

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

template <class Type>
Type *Iterator<Type>::get_cur_ptr() const
{
  std::shared_ptr<Type[]> copy_ptr = ptr_.lock();
  return copy_ptr.get() + index_;
}

template <class Type>
Iterator<Type>::Iterator(const Vector<Type> &vec)
{
  index_ = 0;
  num_elem_ = vec.num_elem_;
  ptr_ = vec.data_list_;
}

template <class Type>
Iterator<Type>::Iterator(const Iterator<Type> &iter)
{
  ptr_ = iter.ptr_;
  index_ = iter.index_;
  num_elem_ = iter.num_elem_;
}

template <class Type>
Iterator<Type>::Iterator(Iterator<Type> &&iter)
{
  ptr_ = std::move(iter.ptr_);
  index_ = iter.index_;
  num_elem_ = iter.num_elem_;
}


template <class Type>
Type &Iterator<Type>::operator*()
{
  time_t t_time = time(NULL);
  check(__LINE__);
  if (index_ < 0 || index_ >= num_elem_)
    throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  return *get_cur_ptr();
}

template <class Type>
const Type &Iterator<Type>::operator*() const
{
  time_t t_time = time(NULL);
  check(__LINE__);
  if (index_ < 0 || index_ >= num_elem_)
    throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  return *get_cur_ptr();
}

template <class Type>
Type *Iterator<Type>::operator->()
{
  time_t t_time = time(NULL);
  check(__LINE__);
  if (index_ < 0 || index_ >= num_elem_)
    throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  return get_cur_ptr();
}

template <class Type>
const Type *Iterator<Type>::operator->() const
{
  time_t t_time = time(NULL);
  check(__LINE__);
  if (index_ < 0 || index_ >= num_elem_)
    throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  return get_cur_ptr();
}

template <class Type>
Iterator<Type> &Iterator<Type>::operator=(const Iterator<Type> &iter)
{
  check(__LINE__);

  ptr_ = iter.ptr_;
  num_elem_ = iter.num_elem_;
  index_ = iter.index_;
  return *this;
}

template <class Type>
Iterator<Type> &Iterator<Type>::operator=(Iterator<Type> &&iter)
{
  check(__LINE__);

  ptr_ = std::move(iter.ptr_);
  num_elem_ = iter.num_elem_;
  index_ = iter.index_;
  return *this;
}


template <class Type>
Iterator<Type> &Iterator<Type>::operator+=(int n)
{
  check(__LINE__);
  index_ += n;

  return *this;
}

template <class Type>
Iterator<Type> Iterator<Type>::operator+(int n) const
{
  check(__LINE__);
  Iterator<Type> iter(*this);
  iter += n;

  return iter;
}

template <class Type>
Iterator<Type> Iterator<Type>::operator++(int)
{
  check(__LINE__);
  Iterator<Type> new_iter(*this);
  ++(*this);
  return new_iter;
}

template <class Type>
Iterator<Type> &Iterator<Type>::operator++()
{
  check(__LINE__);
  ++index_;

  return *this;
}

template <class Type>
Iterator<Type> &Iterator<Type>::operator-=(int n)
{
  check(__LINE__);
  index_ -= n;

  return *this;
}

template <class Type>
Iterator<Type> Iterator<Type>::operator-(int n) const
{
  check(__LINE__);

  Iterator<Type> iter(*this);
  iter -= n;

  return iter;
}

template <class Type>
Iterator<Type> Iterator<Type>::operator--(int)
{
  check(__LINE__);

  Iterator<Type> new_iter(*this);
  --(*this);

  return new_iter;
}

template <class Type>
Iterator<Type> &Iterator<Type>::operator--()
{
  check(__LINE__);
  --index_;
  return *this;
}

template <class Type>
bool Iterator<Type>::operator<=(const Iterator<Type> &b) const
{
  check(__LINE__);

  return this->get_cur_ptr() <= b.get_cur_ptr();
}

template <class Type>
bool Iterator<Type>::operator<(const Iterator<Type> &b) const
{
  check(__LINE__);

  return this->get_cur_ptr() < b.get_cur_ptr();
}

template <class Type>
bool Iterator<Type>::operator>=(const Iterator<Type> &b) const
{
  check(__LINE__);

  return this->get_cur_ptr() >= b.get_cur_ptr();
}

template <class Type>
bool Iterator<Type>::operator>(const Iterator<Type> &b) const
{
  check(__LINE__);

  return this->get_cur_ptr() > b.get_cur_ptr();
}

template <class Type>
bool Iterator<Type>::operator==(const Iterator<Type> &b) const
{
  check(__LINE__);

  return this->get_cur_ptr() == b.get_cur_ptr();
}

template <class Type>
bool Iterator<Type>::operator!=(const Iterator<Type> &b) const
{
  check(__LINE__);

  return this->get_cur_ptr() != b.get_cur_ptr();
}

template <typename Type>
Type &Iterator<Type>::operator[](int index) const
{
  time_t t_time = time(NULL);
  if (index + this->index_ < 0 || index + this->index_ >= num_elem_)
    throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  return *(*this + index);
}

template <class Type>
Iterator<Type>::operator bool() const
{
  check(__LINE__);

  if (index_ >= num_elem_ || index_ < 0 || (num_elem_ == 0))
    return false;
  return true;
}

template <class Type>
bool Iterator<Type>::check(int line) const
{
  if (!ptr_.expired())
    return true;

  time_t t_time = time(NULL);
  throw deletedObj(__FILE__, typeid(*this).name(), line, ctime(&t_time));
  return false;
}

#endif /* class_Iter_h */
