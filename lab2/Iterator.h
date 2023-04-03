#ifndef class_Iter_h
#define class_Iter_h

#include "BaseIter.h"

template<class Type>
class Vector;

template<typename Type>
class Iterator : public BaseIter
{
public:
    Iterator(const Iterator<Type>& iter);
    Iterator(const Vector<Type>& vec);
    ~Iterator() = default;

    Type& operator*();
    const Type& operator*() const;
    Type* operator->();
    const Type* operator->() const;
    operator bool() const override;
    
    Iterator<Type>& operator=(const Iterator<Type>& iter);

    Iterator<Type>& operator+=(int n);
    Iterator<Type> operator+(int n) const;
    Iterator<Type>& operator++();
    Iterator<Type> operator++(int);
    
    Iterator<Type>& operator-=(int n);
    Iterator<Type> operator-(int n) const;
    Iterator<Type>& operator--();
    Iterator<Type> operator--(int);

    Type& operator [](int index) const;

    bool operator<=(const Iterator<Type>& b) const;
    bool operator<(const Iterator<Type>& b) const;
    bool operator>=(const Iterator<Type>& b) const;
    bool operator>(const Iterator<Type>& b) const;
    bool operator==(const Iterator<Type>& b) const;
    bool operator!=(const Iterator<Type>& b) const;
    
    bool check(int line) const;

private:
    std::weak_ptr<Type[]> ptr;
    
protected:
    Type* get_cur_ptr() const;
};

template<class Type>
Type* Iterator<Type>::get_cur_ptr() const
{
    std::shared_ptr<Type[]> copy_ptr = ptr.lock();
    return copy_ptr.get() + index;
}

template<class Type>
Iterator<Type>::Iterator(const Vector<Type>& vec)
{
    index = 0;
    num_elem = vec.num_elem;
    ptr = vec.data_list;
}

template<class Type>
Iterator<Type>::Iterator(const Iterator<Type>& iter)
{
    ptr = iter.ptr;
    index = iter.index;
    num_elem = iter.num_elem;
}

template<class Type>
Type& Iterator<Type>::operator*()
{
    time_t t_time = time(NULL);
    check(__LINE__);
    if (index < 0 || index >= num_elem)
        throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    return *get_cur_ptr();
}

template<class Type>
const Type& Iterator<Type>::operator*() const
{
    time_t t_time = time(NULL);
    check(__LINE__);
    if (index < 0 || index >= num_elem)
        throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    return *get_cur_ptr();
}

template<class Type>
Type* Iterator<Type>::operator->()
{
    time_t t_time = time(NULL);
    check(__LINE__);
    if (index < 0 || index >= num_elem)
        throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    return get_cur_ptr();
}

template<class Type>
const Type* Iterator<Type>::operator->() const
{
    time_t t_time = time(NULL);
    check(__LINE__);
    if (index < 0 || index >= num_elem)
        throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    return get_cur_ptr();
}

template<class Type>
Iterator<Type>& Iterator<Type>::operator=(const Iterator<Type>& iter)
{
    check(__LINE__);

    ptr = iter.ptr;
    num_elem = iter.num_elem;
    index = iter.index;
    return *this;
}

template<class Type>
Iterator<Type>& Iterator<Type>::operator+=(int n)
{
    check(__LINE__);
    index += n;

    return *this;
}

template<class Type>
Iterator<Type> Iterator<Type>::operator+(int n) const
{
    check(__LINE__);
    Iterator<Type> iter(*this);
    iter += n;
    
    return iter;
}

template<class Type>
Iterator<Type> Iterator<Type>::operator++(int)
{
    check(__LINE__);
    Iterator<Type> new_iter(*this);
    ++(*this);
    return new_iter;
}

template<class Type>
Iterator<Type>& Iterator<Type>::operator++()
{
    check(__LINE__);
    ++index;
    
    return *this;
}

template<class Type>
Iterator<Type>& Iterator<Type>::operator-=(int n)
{
    check(__LINE__);
    index -= n;
    
    return *this;
}

template<class Type>
Iterator<Type> Iterator<Type>::operator-(int n) const
{
    check(__LINE__);
    
    Iterator<Type> iter(*this);
    iter -= n;
    
    return iter;
}

template<class Type>
Iterator<Type> Iterator<Type>::operator--(int)
{
    check(__LINE__);

    Iterator<Type> new_iter(*this);
    --(*this);
    
    return new_iter;
}

template<class Type>
Iterator<Type>& Iterator<Type>::operator--()
{
    check(__LINE__);
    --index;
    return *this;
}

template<class Type>
bool Iterator<Type>::operator<=(const Iterator<Type>& b) const
{
    check(__LINE__);
    
    return this->get_cur_ptr() <= b.get_cur_ptr();
}

template<class Type>
bool Iterator<Type>::operator<(const Iterator<Type>& b) const
{
    check(__LINE__);
    
    return this->get_cur_ptr() < b.get_cur_ptr();
}

template<class Type>
bool Iterator<Type>::operator>=(const Iterator<Type>& b) const
{
    check(__LINE__);
    
    return this->get_cur_ptr() >= b.get_cur_ptr();
}

template<class Type>
bool Iterator<Type>::operator>(const Iterator<Type>& b) const
{
    check(__LINE__);

    return this->get_cur_ptr() > b.get_cur_ptr();
}

template<class Type>
bool Iterator<Type>::operator==(const Iterator<Type>& b) const
{
    check(__LINE__);

    return this->get_cur_ptr() == b.get_cur_ptr();
}

template<class Type>
bool Iterator<Type>::operator!=(const Iterator<Type>& b) const
{
    check(__LINE__);

    return this->get_cur_ptr() != b.get_cur_ptr();
}


template<typename Type>
Type& Iterator<Type>::operator [](int index) const
{
    time_t t_time = time(NULL);
    if (index + this->index < 0 || index + this->index >= num_elem)
        throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    return *(*this + index);
}

template<class Type>
Iterator<Type>::operator bool() const
{
    check(__LINE__);
    
    if (index >= num_elem || index < 0 || (num_elem == 0))
        return false;
    else
        return true;
}

template<class Type>
bool Iterator<Type>::check(int line) const
{
    if (!ptr.expired())
        return true;
    
    time_t t_time = time(NULL);
    throw deletedObj(__FILE__, typeid(*this).name(), line, ctime(&t_time));
    return false;
}

#endif /* class_Iter_h */
