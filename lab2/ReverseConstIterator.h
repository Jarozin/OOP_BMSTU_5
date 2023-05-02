#ifndef REVERSECONSTITER_H
#define REVERSECONSTITER_H

#include "BaseIter.h"
#include "Iterator.h"
#include "my_errors.h"
#include <memory>
#include "ReverseIterator.h"

template <VectorType Type>
class Vector;

template <VectorType Type>
class ReverseConstIterator : public BaseIter
{
public:
    using iterator = ReverseConstIterator;
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = typename Vector<Type>::difference_type;
    using value_type = const typename Vector<Type>::value_type;
    using reference = value_type &;
    using pointer = value_type *;
    using size_type = typename Vector<Type>::size_type;

    ReverseConstIterator(const ReverseConstIterator<Type> &iter);
    ReverseConstIterator(ReverseConstIterator<Type> &&iter);
    ReverseConstIterator(const Vector<Type> &vec);
    ~ReverseConstIterator() = default;
    ReverseConstIterator(const ReverseIterator<Type> &iter);

    const Type &operator*() const;
    const Type *operator->() const;
    operator bool() const override;

    ReverseConstIterator<Type> &operator=(const ReverseIterator<Type> &iter);
    ReverseConstIterator<Type> &operator=(ReverseIterator<Type> &&iter);

    ReverseConstIterator<Type> &operator+=(int n);
    ReverseConstIterator<Type> operator+(int n) const;
    ReverseConstIterator<Type> &operator++();
    ReverseConstIterator<Type> operator++(int);

    ReverseConstIterator<Type> &operator-=(int n);
    ReverseConstIterator<Type> operator-(int n) const;
    ReverseConstIterator<Type> &operator--();
    ReverseConstIterator<Type> operator--(int);

    difference_type operator-(const ReverseConstIterator<Type> &iter);

    const Type &operator[](int index) const;

    bool operator<=(const ReverseConstIterator<Type> &b) const;
    bool operator<(const ReverseConstIterator<Type> &b) const;
    bool operator>=(const ReverseConstIterator<Type> &b) const;
    bool operator>(const ReverseConstIterator<Type> &b) const;
    bool operator==(const ReverseConstIterator<Type> &b) const;
    bool operator!=(const ReverseConstIterator<Type> &b) const;

    bool check(int line) const;

private:
    std::weak_ptr<Type[]> ptr_;

protected:
    Type *get_cur_ptr() const;
};
template <VectorType Type>
Iterator<Type> operator+(const int& n, const ReverseConstIterator<Type> &it)
{
  return it + n;
}
template <VectorType Type>
Type *ReverseConstIterator<Type>::get_cur_ptr() const
{
    std::shared_ptr<Type[]> copy_ptr = ptr_.lock();
    return copy_ptr.get() + index_;
}

template <VectorType Type>
ReverseConstIterator<Type>::ReverseConstIterator(const Vector<Type> &vec)
{
    num_elem_ = vec.num_elem_;
    index_ = num_elem_ - 1;
    ptr_ = vec.data_list_;
}

template <VectorType Type>
ReverseConstIterator<Type>::ReverseConstIterator(const ReverseConstIterator<Type> &iter)
{
    ptr_ = iter.ptr_;
    index_ = iter.index_;
    num_elem_ = iter.num_elem_;
}

template <VectorType Type>
ReverseConstIterator<Type>::ReverseConstIterator(const ReverseIterator<Type> &iter)
{
    ptr_ = iter.ptr_;
    index_ = iter.index_;
    num_elem_ = iter.num_elem_;
}

template <VectorType Type>
ReverseConstIterator<Type>::ReverseConstIterator(ReverseConstIterator<Type> &&iter)
{
    ptr_ = std::move(iter.ptr_);
    index_ = iter.index_;
    num_elem_ = iter.num_elem_;
}

template <VectorType Type>
const Type &ReverseConstIterator<Type>::operator*() const
{
    check(__LINE__);

    std::shared_ptr<Type[]> copy_ptr = ptr_.lock();
    return *get_cur_ptr();
}

template <VectorType Type>
const Type *ReverseConstIterator<Type>::operator->() const
{
    check(__LINE__);

    return get_cur_ptr();
}

template <VectorType Type>
ReverseConstIterator<Type> &ReverseConstIterator<Type>::operator+=(int n)
{
    check(__LINE__);
    index_ -= n;

    return *this;
}

template <VectorType Type>
ReverseConstIterator<Type> ReverseConstIterator<Type>::operator+(int n) const
{
    check(__LINE__);
    ReverseConstIterator<Type> iter(*this);
    iter += n;

    return iter;
}

template <VectorType Type>
ReverseConstIterator<Type> ReverseConstIterator<Type>::operator++(int)
{
    check(__LINE__);
    ReverseConstIterator<Type> new_iter(*this);
    ++(*this);
    return new_iter;
}

template <VectorType Type>
ReverseConstIterator<Type> &ReverseConstIterator<Type>::operator++()
{
    check(__LINE__);
    --index_;

    return *this;
}

template <VectorType Type>
ReverseConstIterator<Type> ReverseConstIterator<Type>::operator-(int n) const
{
    check(__LINE__);

    ReverseConstIterator<Type> iter(*this);
    iter -= n;

    return iter;
}

template <VectorType Type>
ReverseConstIterator<Type> ReverseConstIterator<Type>::operator--(int)
{
    check(__LINE__);
    ReverseConstIterator<Type> new_iter(*this);
    --(*this);

    return new_iter;
}

template <VectorType Type>
ReverseConstIterator<Type> &ReverseConstIterator<Type>::operator--()
{
    check(__LINE__);
    ++index_;

    return *this;
}
template <VectorType Type>
const Type &ReverseConstIterator<Type>::operator[](int index) const
{
    time_t t_time = time(NULL);
    if (index + this->index_ < 0 || index + this->index_ >= num_elem_)
        throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    return *(*this + index);
}
template <VectorType Type>
bool ReverseConstIterator<Type>::operator<=(const ReverseConstIterator<Type> &b) const
{
    check(__LINE__);

    return !(*this > b);
}

template <VectorType Type>
bool ReverseConstIterator<Type>::operator<(const ReverseConstIterator<Type> &b) const
{
    check(__LINE__);

    return this->get_cur_ptr() + index_ > b.get_cur_ptr() + b.index_;
}

template <VectorType Type>
bool ReverseConstIterator<Type>::operator>=(const ReverseConstIterator<Type> &b) const
{
    check(__LINE__);

    return !(*this > b);
}

template <VectorType Type>
bool ReverseConstIterator<Type>::operator>(const ReverseConstIterator<Type> &b) const
{
    check(__LINE__);

    return !(*this > b) && !(*this == b);
}

template <VectorType Type>
bool ReverseConstIterator<Type>::operator==(const ReverseConstIterator<Type> &b) const
{
    check(__LINE__);

    return this->get_cur_ptr() + index_ == b.get_cur_ptr() + b.index_;
}

template <VectorType Type>
bool ReverseConstIterator<Type>::operator!=(const ReverseConstIterator<Type> &b) const
{
    check(__LINE__);

    return !(*this == b);
}

template <VectorType Type>
ReverseConstIterator<Type>::operator bool() const
{
    check(__LINE__);

    if (index_ >= num_elem_ || index_ < 0 || (num_elem_ == 0))
        return false;
    return true;
}

template <VectorType Type>
bool ReverseConstIterator<Type>::check(int line) const
{
    if (!ptr_.expired())
        return true;

    time_t t_time = time(NULL);
    throw deletedObj(__FILE__, typeid(*this).name(), line, ctime(&t_time));
    return false;
}

template <VectorType Type>
ReverseConstIterator<Type> &ReverseConstIterator<Type>::operator=(const ReverseIterator<Type> &iter)
{
    check(__LINE__);

    ptr_ = iter.ptr_;
    num_elem_ = iter.num_elem_;
    index_ = iter.index_;
    return *this;
}

template <VectorType Type>
ReverseConstIterator<Type> &ReverseConstIterator<Type>::operator=(ReverseIterator<Type> &&iter)
{
    check(__LINE__);

    ptr_ = std::move(iter.ptr_);
    num_elem_ = iter.num_elem_;
    index_ = iter.index_;
    return *this;
}

template <VectorType Type>
ReverseConstIterator<Type> &ReverseConstIterator<Type>::operator-=(int n)
{
    check(__LINE__);
    index_ += n;

    return *this;
}

template <VectorType Type>
typename ReverseConstIterator<Type>::difference_type ReverseConstIterator<Type>::operator-(const ReverseConstIterator<Type> &iter)
{
  if (this->ptr_.lock() != iter.ptr_.lock())
  {
    time_t t_time = time(NULL);
    throw iteratorPtrError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  }
  return iter.index_ - index_;
}

#endif // CONSTITER_H
