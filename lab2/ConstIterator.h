#ifndef CONSTITER_H
#define CONSTITER_H

#include "BaseIter.h"
#include "Iterator.h"
#include "my_errors.h"
#include <memory>

template <VectorType Type>
class Vector;

template <VectorType Type>
class ConstIterator : public BaseIter
{
public:
    using iterator = ConstIterator;
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = typename Vector<Type>::difference_type;
    using value_type = typename Vector<Type>::value_type;
    using reference = value_type &;
    using pointer = value_type *;
    ConstIterator(const ConstIterator<Type> &iter);
    ConstIterator(ConstIterator<Type> &&iter);
    ConstIterator(const Vector<Type> &vec);
    ~ConstIterator() = default;

    const Type &operator*() const;
    const Type *operator->() const;
    operator bool() const override;

    ConstIterator<Type> &operator=(const Iterator<Type> &iter);
    ConstIterator<Type> &operator=(Iterator<Type> &&iter);

    ConstIterator<Type> &operator+=(int n);
    ConstIterator<Type> operator+(int n) const;
    ConstIterator<Type> &operator++();
    ConstIterator<Type> operator++(int);

    ConstIterator<Type> &operator-=(int n);
    ConstIterator<Type> operator-(int n) const;
    ConstIterator<Type> &operator--();
    ConstIterator<Type> operator--(int);

    difference_type operator-(const ConstIterator<Type> &iter);

    const Type &operator[](int index) const;

    bool operator<=(const ConstIterator<Type> &b) const;
    bool operator<(const ConstIterator<Type> &b) const;
    bool operator>=(const ConstIterator<Type> &b) const;
    bool operator>(const ConstIterator<Type> &b) const;
    bool operator==(const ConstIterator<Type> &b) const;
    bool operator!=(const ConstIterator<Type> &b) const;

    bool check(int line) const;

private:
    std::weak_ptr<Type[]> ptr_;

protected:
    Type *get_cur_ptr() const;
};

template <VectorType Type>
Type *ConstIterator<Type>::get_cur_ptr() const
{
    std::shared_ptr<Type[]> copy_ptr = ptr_.lock();
    return copy_ptr.get() + index_;
}

template <VectorType Type>
ConstIterator<Type>::ConstIterator(const Vector<Type> &vec)
{
    index_ = 0;
    num_elem_ = vec.num_elem_;
    ptr_ = vec.data_list_;
}

template <VectorType Type>
ConstIterator<Type>::ConstIterator(const ConstIterator<Type> &iter)
{
    ptr_ = iter.ptr_;
    index_ = iter.index_;
    num_elem_ = iter.num_elem_;
}

template <VectorType Type>
ConstIterator<Type>::ConstIterator(ConstIterator<Type> &&iter)
{
    ptr_ = std::move(iter.ptr_);
    index_ = iter.index_;
    num_elem_ = iter.num_elem_;
}

template <VectorType Type>
const Type &ConstIterator<Type>::operator*() const
{
    check(__LINE__);

    std::shared_ptr<Type[]> copy_ptr = ptr_.lock();
    return *get_cur_ptr();
}

template <VectorType Type>
const Type *ConstIterator<Type>::operator->() const
{
    check(__LINE__);

    return get_cur_ptr();
}

template <VectorType Type>
ConstIterator<Type> &ConstIterator<Type>::operator+=(int n)
{
    check(__LINE__);
    index_ += n;

    return *this;
}

template <VectorType Type>
ConstIterator<Type> ConstIterator<Type>::operator+(int n) const
{
    check(__LINE__);
    ConstIterator<Type> iter(*this);
    iter += n;

    return iter;
}

template <VectorType Type>
ConstIterator<Type> ConstIterator<Type>::operator++(int)
{
    check(__LINE__);
    ConstIterator<Type> new_iter(*this);
    ++(*this);
    return new_iter;
}

template <VectorType Type>
ConstIterator<Type> &ConstIterator<Type>::operator++()
{
    check(__LINE__);
    ++index_;

    return *this;
}

template <VectorType Type>
ConstIterator<Type> ConstIterator<Type>::operator-(int n) const
{
    check(__LINE__);

    ConstIterator<Type> iter(*this);
    iter -= n;

    return iter;
}

template <VectorType Type>
ConstIterator<Type> ConstIterator<Type>::operator--(int)
{
    check(__LINE__);
    ConstIterator<Type> new_iter(*this);
    --(*this);

    return new_iter;
}

template <VectorType Type>
ConstIterator<Type> &ConstIterator<Type>::operator--()
{
    check(__LINE__);
    --index_;

    return *this;
}
template <VectorType Type>
const Type &ConstIterator<Type>::operator[](int index) const
{
    time_t t_time = time(NULL);
    if (index + this->index_ < 0 || index + this->index_ >= num_elem_)
        throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    return *(*this + index);
}
template <VectorType Type>
bool ConstIterator<Type>::operator<=(const ConstIterator<Type> &b) const
{
    check(__LINE__);

    return !(*this > b);
}

template <VectorType Type>
bool ConstIterator<Type>::operator<(const ConstIterator<Type> &b) const
{
    check(__LINE__);

    return this->get_cur_ptr() + index_ < b.get_cur_ptr() + b.index_;
}

template <VectorType Type>
bool ConstIterator<Type>::operator>=(const ConstIterator<Type> &b) const
{
    check(__LINE__);

    return !(*this < b);
}

template <VectorType Type>
bool ConstIterator<Type>::operator>(const ConstIterator<Type> &b) const
{
    check(__LINE__);

    return !(*this < b) && !(*this == b);
}

template <VectorType Type>
bool ConstIterator<Type>::operator==(const ConstIterator<Type> &b) const
{
    check(__LINE__);

    return this->get_cur_ptr() + index_ == b.get_cur_ptr() + b.index_;
}

template <VectorType Type>
bool ConstIterator<Type>::operator!=(const ConstIterator<Type> &b) const
{
    check(__LINE__);

    return !(*this == b);
}

template <VectorType Type>
ConstIterator<Type>::operator bool() const
{
    check(__LINE__);

    if (index_ >= num_elem_ || index_ < 0 || (num_elem_ == 0))
        return false;
    return true;
}

template <VectorType Type>
bool ConstIterator<Type>::check(int line) const
{
    if (!ptr_.expired())
        return true;

    time_t t_time = time(NULL);
    throw deletedObj(__FILE__, typeid(*this).name(), line, ctime(&t_time));
    return false;
}

template <VectorType Type>
ConstIterator<Type> &ConstIterator<Type>::operator=(const Iterator<Type> &iter)
{
    check(__LINE__);

    ptr_ = iter.ptr_;
    num_elem_ = iter.num_elem_;
    index_ = iter.index_;
    return *this;
}

template <VectorType Type>
ConstIterator<Type> &ConstIterator<Type>::operator=(Iterator<Type> &&iter)
{
    check(__LINE__);

    ptr_ = std::move(iter.ptr_);
    num_elem_ = iter.num_elem_;
    index_ = iter.index_;
    return *this;
}

template <VectorType Type>
ConstIterator<Type> &ConstIterator<Type>::operator-=(int n)
{
    check(__LINE__);
    index_ -= n;

    return *this;
}

template <VectorType Type>
typename ConstIterator<Type>::difference_type ConstIterator<Type>::operator-(const ConstIterator<Type> &iter)
{
  return index_ - iter.index_;
}
#endif // CONSTITER_H
