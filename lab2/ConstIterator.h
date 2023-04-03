#ifndef CONSTITER_H
#define CONSTITER_H

#include "BaseIter.h"
#include "my_errors.h"

template<class Type>
class Vector;

template<typename Type>
class ConstIterator : public BaseIter
{
public:
    ConstIterator(const ConstIterator<Type>& iter);
    ConstIterator(const Vector<Type>& vec);
    ~ConstIterator() = default;

    const Type& operator*() const;
    const Type* operator->() const;
    operator bool() const override;

    ConstIterator<Type>& operator=(const Iterator<Type>& iter);

    ConstIterator<Type>& operator+=(int n);
    ConstIterator<Type> operator+(int n) const;
    ConstIterator<Type>& operator++();
    ConstIterator<Type> operator++(int);

    ConstIterator<Type>& operator-=(int n);
    ConstIterator<Type> operator-(int n) const;
    ConstIterator<Type>& operator--();
    ConstIterator<Type> operator--(int);

    const Type& operator [](int index) const;

    bool operator<=(const ConstIterator<Type>& b) const;
    bool operator<(const ConstIterator<Type>& b) const;
    bool operator>=(const ConstIterator<Type>& b) const;
    bool operator>(const ConstIterator<Type>& b) const;
    bool operator==(const ConstIterator<Type>& b) const;
    bool operator!=(const ConstIterator<Type>& b) const;

    bool check(int line) const;

private:
    std::weak_ptr<Type[]> ptr;

protected:
    Type* get_cur_ptr() const;
};

template<class Type>
Type* ConstIterator<Type>::get_cur_ptr() const
{
    time_t t_time = time(NULL);
    if (index < 0 || index >= num_elem)
        throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    std::shared_ptr<Type[]> copy_ptr = ptr.lock();
    return copy_ptr.get() + index;
}

template<class Type>
ConstIterator<Type>::ConstIterator(const Vector<Type>& vec)
{
    index = 0;
    num_elem = vec.num_elem;
    ptr = vec.data_list;
}

template<class Type>
ConstIterator<Type>::ConstIterator(const ConstIterator<Type>& iter)
{
    ptr = iter.ptr;
    index = iter.index;
    num_elem = iter.num_elem;
}

template<class Type>
const Type& ConstIterator<Type>::operator*() const
{
    check(__LINE__);

    std::shared_ptr<Type[]> copy_ptr = ptr.lock();
    return *get_cur_ptr();
}

template<class Type>
const Type* ConstIterator<Type>::operator->() const
{
    check(__LINE__);

    return get_cur_ptr();
}

template<class Type>
ConstIterator<Type>& ConstIterator<Type>::operator+=(int n)
{
    check(__LINE__);
    index += n;

    return *this;
}

template<class Type>
ConstIterator<Type> ConstIterator<Type>::operator+(int n) const
{
    check(__LINE__);
    ConstIterator<Type> iter(*this);
    iter += n;

    return iter;
}

template<class Type>
ConstIterator<Type> ConstIterator<Type>::operator++(int)
{
    check(__LINE__);
    ++(*this);

    return *this;
}

template<class Type>
ConstIterator<Type>& ConstIterator<Type>::operator++()
{
    check(__LINE__);
    ConstIterator<Type> new_iter(*this);
    ++(*this);

    return new_iter;
}

template<class Type>
ConstIterator<Type> ConstIterator<Type>::operator-(int n) const
{
    check(__LINE__);

    ConstIterator<Type> iter(*this);
    iter -= n;

    return iter;
}

template<class Type>
ConstIterator<Type> ConstIterator<Type>::operator--(int)
{
    check(__LINE__);
    ConstIterator<Type> new_iter(*this);
    --(*this);

    return new_iter;
}

template<class Type>
ConstIterator<Type>& ConstIterator<Type>::operator--()
{
    check(__LINE__);
    --index;

    return *this;
}
template<class Type>
const Type& ConstIterator<Type>::operator [](int index) const
{
    time_t t_time = time(NULL);
    if (index + this->index < 0 || index + this->index >= num_elem)
        throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    return *(*this + index);
}
template<class Type>
bool ConstIterator<Type>::operator<=(const ConstIterator<Type>& b) const
{
    check(__LINE__);

    return this->get_cur_ptr() <= b.get_cur_ptr();
}

template<class Type>
bool ConstIterator<Type>::operator<(const ConstIterator<Type>& b) const
{
    check(__LINE__);

    return this->get_cur_ptr() < b.get_cur_ptr();
}

template<class Type>
bool ConstIterator<Type>::operator>=(const ConstIterator<Type>& b) const
{
    check(__LINE__);

    return this->get_cur_ptr() >= b.get_cur_ptr();
}

template<class Type>
bool ConstIterator<Type>::operator>(const ConstIterator<Type>& b) const
{
    check(__LINE__);

    return this->get_cur_ptr() > b.get_cur_ptr();
}

template<class Type>
bool ConstIterator<Type>::operator==(const ConstIterator<Type>& b) const
{
    check(__LINE__);

    return this->get_cur_ptr() == b.get_cur_ptr();
}

template<class Type>
bool ConstIterator<Type>::operator!=(const ConstIterator<Type>& b) const
{
    check(__LINE__);

    return this->get_cur_ptr() != b.get_cur_ptr();
}

template<class Type>
ConstIterator<Type>::operator bool() const
{
    check(__LINE__);

    if (index >= num_elem || index < 0 || (num_elem == 0))
        return false;
    else
        return true;
}

template<class Type>
bool ConstIterator<Type>::check(int line) const
{
    if (!ptr.expired())
        return true;

    time_t t_time = time(NULL);
    throw deletedObj(__FILE__, typeid(*this).name(), line, ctime(&t_time));
    return false;
}

template<typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator=(const Iterator<Type> &iter) {
    check(__LINE__);

    ptr = iter.ptr;
    num_elem = iter.num_elem;
    index = iter.index;
    return *this;
}

template<typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator-=(int n) {
    check(__LINE__);
    index -= n;

    return *this;
}

#endif // CONSTITER_H