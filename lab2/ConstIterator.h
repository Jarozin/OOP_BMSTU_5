#ifndef CONSTITER_H
#define CONSTITER_H

#include "BaseIter.h"
#include "Iterator.h"
#include "my_errors.h"
#include <memory>

template <class Type>
class Vector;

template <typename Type>
class ConstIterator : public BaseIter
{
public:
    ConstIterator(const ConstIterator<Type> &iter);
    ConstIterator(const Vector<Type> &vec);
    ~ConstIterator() = default;

    const Type &operator*() const;
    const Type *operator->() const;
    operator bool() const override;

    ConstIterator<Type> &operator=(const Iterator<Type> &iter);

    ConstIterator<Type> &operator+=(int n);
    ConstIterator<Type> operator+(int n) const;
    ConstIterator<Type> &operator++();
    ConstIterator<Type> operator++(int);

    ConstIterator<Type> &operator-=(int n);
    ConstIterator<Type> operator-(int n) const;
    ConstIterator<Type> &operator--();
    ConstIterator<Type> operator--(int);

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

template <class Type>
Type *ConstIterator<Type>::get_cur_ptr() const
{
    time_t t_time = time(NULL);
    if (index_ < 0 || index_ >= num_elem_)
        throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    std::shared_ptr<Type[]> copy_ptr = ptr_.lock();
    return copy_ptr.get() + index_;
}

template <class Type>
ConstIterator<Type>::ConstIterator(const Vector<Type> &vec)
{
    index_ = 0;
    num_elem_ = vec.num_elem_;
    ptr_ = vec.data_list_;
}

template <class Type>
ConstIterator<Type>::ConstIterator(const ConstIterator<Type> &iter)
{
    ptr_ = iter.ptr_;
    index_ = iter.index_;
    num_elem_ = iter.num_elem_;
}

template <class Type>
const Type &ConstIterator<Type>::operator*() const
{
    check(__LINE__);

    std::shared_ptr<Type[]> copy_ptr = ptr_.lock();
    return *get_cur_ptr();
}

template <class Type>
const Type *ConstIterator<Type>::operator->() const
{
    check(__LINE__);

    return get_cur_ptr();
}

template <class Type>
ConstIterator<Type> &ConstIterator<Type>::operator+=(int n)
{
    check(__LINE__);
    index_ += n;

    return *this;
}

template <class Type>
ConstIterator<Type> ConstIterator<Type>::operator+(int n) const
{
    check(__LINE__);
    ConstIterator<Type> iter(*this);
    iter += n;

    return iter;
}

template <class Type>
ConstIterator<Type> ConstIterator<Type>::operator++(int)
{
    check(__LINE__);
    ConstIterator<Type> new_iter(*this);
    ++(*this);
    return new_iter;
}

template <class Type>
ConstIterator<Type> &ConstIterator<Type>::operator++()
{
    check(__LINE__);
    ++index_;

    return *this;
}

template <class Type>
ConstIterator<Type> ConstIterator<Type>::operator-(int n) const
{
    check(__LINE__);

    ConstIterator<Type> iter(*this);
    iter -= n;

    return iter;
}

template <class Type>
ConstIterator<Type> ConstIterator<Type>::operator--(int)
{
    check(__LINE__);
    ConstIterator<Type> new_iter(*this);
    --(*this);

    return new_iter;
}

template <class Type>
ConstIterator<Type> &ConstIterator<Type>::operator--()
{
    check(__LINE__);
    --index_;

    return *this;
}
template <class Type>
const Type &ConstIterator<Type>::operator[](int index) const
{
    time_t t_time = time(NULL);
    if (index + this->index_ < 0 || index + this->index_ >= num_elem_)
        throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    return *(*this + index);
}
template <class Type>
bool ConstIterator<Type>::operator<=(const ConstIterator<Type> &b) const
{
    check(__LINE__);

    return this->get_cur_ptr() <= b.get_cur_ptr();
}

template <class Type>
bool ConstIterator<Type>::operator<(const ConstIterator<Type> &b) const
{
    check(__LINE__);

    return this->get_cur_ptr() < b.get_cur_ptr();
}

template <class Type>
bool ConstIterator<Type>::operator>=(const ConstIterator<Type> &b) const
{
    check(__LINE__);

    return this->get_cur_ptr() >= b.get_cur_ptr();
}

template <class Type>
bool ConstIterator<Type>::operator>(const ConstIterator<Type> &b) const
{
    check(__LINE__);

    return this->get_cur_ptr() > b.get_cur_ptr();
}

template <class Type>
bool ConstIterator<Type>::operator==(const ConstIterator<Type> &b) const
{
    check(__LINE__);

    return this->get_cur_ptr() == b.get_cur_ptr();
}

template <class Type>
bool ConstIterator<Type>::operator!=(const ConstIterator<Type> &b) const
{
    check(__LINE__);

    return this->get_cur_ptr() != b.get_cur_ptr();
}

template <class Type>
ConstIterator<Type>::operator bool() const
{
    check(__LINE__);

    if (index_ >= num_elem_ || index_ < 0 || (num_elem_ == 0))
        return false;
    return true;
}

template <class Type>
bool ConstIterator<Type>::check(int line) const
{
    if (!ptr_.expired())
        return true;

    time_t t_time = time(NULL);
    throw deletedObj(__FILE__, typeid(*this).name(), line, ctime(&t_time));
    return false;
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator=(const Iterator<Type> &iter)
{
    check(__LINE__);

    ptr_ = iter.ptr_;
    num_elem_ = iter.num_elem_;
    index_ = iter.index_;
    return *this;
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator-=(int n)
{
    check(__LINE__);
    index_ -= n;

    return *this;
}

#endif // CONSTITER_H
