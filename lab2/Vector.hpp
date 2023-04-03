#ifndef class_Vector_hpp
#define class_Vector_hpp

#include <iostream>
#include <stdlib.h>
#include <cstddef>

#include "Vector.h"
#include "my_errors.h"

int max(int num1, int num2)
{
    if (num1 >= num2)
        return num1;
    else
        return num2;
}

template<typename Type>
Vector<Type>::~Vector<Type>()
{
    if (data_list)
        data_list.reset();
}

template<typename Type>
Vector<Type>::Vector()
{
    num_elem = 0;
    new_dyn_mem(num_elem);
}

template<typename Type>
Vector<Type>::Vector(int num_elements)
{
    time_t t_time = time(NULL);
    if (num_elements <= 0)
        throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    
    num_elem = num_elements;
    new_dyn_mem(num_elem);
    
    if (!data_list)
        throw memError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    
    Iterator<Type> iter(*this);
    for (; iter; iter++)
        *iter = Type(0);
}

template<typename Type>
Vector<Type>::Vector(int num_elements, Type vec, ...)
{
    time_t t_time = time(NULL);
    if (num_elements < 1)
        throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    
    num_elem = num_elements;
    new_dyn_mem(num_elem);
    
    if (!data_list)
        throw memError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    
    Iterator<Type> iter(*this);
    va_list ap;
    va_start(ap, vec);
    for (; iter; iter++)
    {
        *iter = vec;
        vec = va_arg(ap, Type);
    }
    va_end(ap);
}

template<typename Type>
Vector<Type>::Vector(int num_elements, Type* vec)
{
    time_t t_time = time(NULL);
    if (num_elements <= 0)
        throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    
    num_elem = num_elements;
    new_dyn_mem(num_elem);
    
    Iterator<Type> iter(*this);
    for (int i = 0; iter; i++, iter++)
        *iter = vec[i];
}

template<typename Type>
Vector<Type>::Vector(std::initializer_list<Type> args)
{
    if (args.size() == 0)
        Vector();
    
    num_elem = int(args.size());
    new_dyn_mem(num_elem);
    
    Iterator<Type> iter(*this);
    for (auto &element : args)
    {
        *iter = element;
        iter++;
    }
}

template <typename Type>
template <typename InputIt>
Vector<Type>::Vector(InputIt iter1, InputIt iter2){
    time_t t_time = time(NULL);
    num_elem = 0;
    for (auto i = iter1; i < iter2; i++)
        num_elem++;
    if (num_elem <= 0)
        throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    new_dyn_mem(num_elem);
    Iterator<Type> new_iter(*this);
    for (auto i = iter1;i < iter2; i++, new_iter++)
        *new_iter = *i;
}
template<typename Type>
Type& Vector<Type>::get_elem_Vector(int index)
{
    time_t t_time = time(NULL);
    if (index < 0 || index >= num_elem)
        throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    
    Iterator<Type> iter(*this);
    for (int i = 0; i < index; i++, iter++)
        ;
    
    return *iter;
}

template<typename Type>
const Type& Vector<Type>::get_elem_Vector(int index) const
{
    time_t t_time = time(NULL);
    if (index < 0 || index >= num_elem)
        throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

    return *(this->cbegin() + index);
}


template <typename Type>
bool Vector<Type>::operator ==(const Vector<Type>& vec) const
{
    int equal = 1;
    if (num_elem != vec.num_elem)
        return false;
    else
    {
        Iterator<Type> iter1(*this);
        Iterator<Type> iter2(vec);
        
        for (; iter1 && equal; iter1++, iter2++)
            if (fabs(*iter1 - *iter2) > EPS)
                equal = 0;
    }
    return equal;
}

template <typename Type>
bool Vector<Type>::operator !=(const Vector<Type>& vec) const
{
    if (*this == vec)
        return false;
    else
        return true;
}

template<typename Type>
Type Vector<Type>::len(void) const
{
    time_t t_time = time(NULL);
    if (num_elem < 0)
        throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    
    Iterator<Type> iter(*this);
    double sum = 0;
    for (; iter; iter++)
        sum += *iter * *iter;
    
    return sqrt(sum);
}

template <typename Type>
template <typename S>
decltype(auto) Vector<Type>::operator ^(const Vector<S>& vec) const
{
    time_t t_time = time(NULL);
    if (num_elem < 0 || vec.size() < 0 || num_elem != vec.size())
        throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    
    int max_len = max(num_elem, vec.size());
    Vector<decltype((*this)[0] + vec[0])> new_vector(max_len);
    for (int i = 0; i < max_len; i++)
        if (i < vec.size() && i < this->size())
            new_vector[i] = (*this)[i] * vec[i];
    return new_vector.sum_all_elem();
}
template<typename Type>
template<typename S>
decltype(auto) Vector<Type>::operator +(const Vector<S>& vec) const
{
    time_t t_time = time(NULL);
    if (num_elem <= 0 || num_elem != vec.size())
        throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

    Vector<decltype((*this)[0] + vec[0])> new_vector(num_elem);
    for (int i = 0; i < num_elem; i++)
        new_vector[i] = (*this)[i] + vec[i];
   // new_vector = sum_vectors(*this, vec);
    return new_vector;
}

template <typename Type>
template <typename S>
Vector<Type>& Vector<Type>::operator +=(const Vector<S>& vec)
{
    time_t t_time = time(NULL);
    if (num_elem < 0 || vec.size() < 0 || num_elem != vec.size())
        throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

    return *this = *this + vec;
}

template<typename Type>
template<typename S>
decltype(auto) Vector<Type>::operator -(const Vector<S>& vec) const
{
    time_t t_time = time(NULL);
    if (num_elem <= 0 || vec.size() <= 0 || num_elem != vec.size())
        throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

    int max_len = max(num_elem, vec.size());
    Vector<decltype((*this)[0] + vec[0])> new_vector(max_len);
    for (int i = 0; i < max_len; i++)
        if (i < vec.size() && i < this->size())
            new_vector[i] = (*this)[i] - vec[i];
    // new_vector = sum_vectors(*this, vec);
    return new_vector;
}

template <typename Type>
template <typename S>
Vector<Type>& Vector<Type>::operator -=(const Vector<S>& vec)
{
    time_t t_time = time(NULL);
    if (num_elem < 0 || vec.size() < 0 || num_elem != vec.size())
        throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    return *this = *this - vec;
}

template<typename Type>
template<typename S>
Vector<Type>& Vector<Type>::operator *=(const S& mult)
{
    time_t t_time = time(NULL);
    if (num_elem < 0)
        throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    
    Iterator<Type> iter(*this);
    for (; iter; iter++)
        *iter *= mult;
    
    return *this;
}

template<typename Type>
template<typename S>
Vector<Type>& Vector<Type>::operator /=(const S& div)
{
    time_t t_time = time(NULL);
    if (!div)
        throw zero_divError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

    Iterator<Type> iter(*this);
    for (; iter; iter++)
        *iter /= div;

    return *this;
}

template<typename Type>
Type Vector<Type>::sum_all_elem()
{
    time_t t_time = time(NULL);
    if (num_elem <= 0)
        throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    
    Iterator<Type> iter(*this);
    Type sum = 0;
    for (; iter; iter++)
        sum += *iter;
    
    return sum;
}

template<typename Type>
template<typename S>
double Vector<Type>::angle_between_vectors(const Vector<S> &vec) const
{
    time_t t_time = time(NULL);
    if (!this->len() || !vec.len())
        throw zero_divError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    
    double angle = ((*this) ^ vec)/(this->len() * vec.len());
    return acos(angle) * 180 / M_PI;
}

template<typename Type>
bool Vector<Type>::is_single() const
{
    if (abs(this->len() - 1) < EPS)
        return true;
    else
        return false;
}

template<typename Type>
bool Vector<Type>::is_zero() const
{
    if (this->len() == 0)
        return true;
    else
        return false;
}



template<typename Type>
template<typename S>
Vector<Type> &Vector<Type>::operator=(const Vector<S> &vec)
{
    if (this->size() != vec.size())
    {
        num_elem = vec.size();
        new_dyn_mem(num_elem);
    }
    for (int i = 0; i < num_elem; i++) data_list[i] = vec[i];
    return *this;
}
template<typename Type>
Vector<Type> &Vector<Type>::operator=(const Vector<Type> &vec)
{
    if (this->size() != vec.size())
    {
        num_elem = vec.size();
        new_dyn_mem(num_elem);
    }
    for (int i = 0; i < num_elem; i++) data_list[i] = vec[i];
    return *this;
}
template<typename Type>
Vector<Type>& Vector<Type>::operator =(std::initializer_list<Type> args)
{
    num_elem = int(args.size());
    new_dyn_mem(num_elem);
    
    Iterator<Type> iter(*this);
    for (auto &element : args)
    {
        *iter = element;
        iter++;
    }
    
    return *this;
}

template<typename Type>
Vector<Type>& Vector<Type>::operator =(Vector<Type> &&vec) noexcept
{
    num_elem = vec.size();
    new_dyn_mem(num_elem);
    data_list = vec.data_list;
    vec.data_list.reset();
    
    return *this;
}

template<typename Type>
Vector<Type>::Vector(const Vector<Type> &vec)
{
    num_elem = vec.size();
    new_dyn_mem(num_elem);
    
    Iterator<Type> iter_new(*this);
    Iterator<Type> iter(vec);
    for (; iter_new; iter++, iter_new++)
        *iter_new = *iter;
}

template<typename Type>
Type& Vector<Type>::operator [](int index)
{
    return get_elem_Vector(index);
}

template<typename Type>
const Type& Vector<Type>::operator [](int index) const
{
    return get_elem_Vector(index);
}

template<typename Type>
bool Vector<Type>::set_elem_Vector(int index, const Type& num)
{
    if (index < 0 || index >= num_elem)
        return false;
    
    get_elem_Vector(index) = num;
    return true;
}

template<typename Type>
Vector<Type> Vector<Type>::get_single_vector() const
{
    Vector<Type> new_vector(*this);
    Type len = this->len();
    
    Iterator<Type> iter(new_vector);
    for (; iter; iter++)
        *iter /= len;
    
    return new_vector;
}

template<typename Type>
int Vector<Type>::size() const
{
    return num_elem;
}

template<typename Type>
template<typename S>
bool Vector<Type>::is_collinearity(const Vector<S>& vec) const
{
    if (this->angle_between_vectors(vec) < EPS)
        return true;
    else
        return false;
}

template<typename Type>
template<typename S>
bool Vector<Type>::is_orthogonality(const Vector<S>& vec) const
{
    if (abs(this->angle_between_vectors(vec) - 90) < EPS)
        return true;
    else
        return false;
}

template <typename Type>
template <typename S, typename R>
decltype(auto)  Vector<Type>::sum_vectors(const Vector<R>& vec1, const Vector<S>& vec2)
{
    int max_len = max(vec1.size(), vec2.size());
    Vector<decltype(vec1[0] + vec2[0])> result(max_len);
    Iterator<decltype(vec1[0] + vec2[0])> iter_result(result);
    Iterator<R> iter_vec1(vec1);
    Iterator<S> iter_vec2(vec2);
    for (int i = 0; iter_result; i++, iter_result++, iter_vec1++, iter_vec2++)
    {
        if (i >= vec1.size())
            *iter_result = *iter_vec2;
        else if (i >= vec2.size())
            *iter_result = *iter_vec1;
        else
            *iter_result = *iter_vec1 + *iter_vec2;
    }
    return result;
}

template <typename Type>
template <typename S, typename R>
decltype(auto)  Vector<Type>::difference_vectors(const Vector<R>& vec1, const Vector<S>& vec2)
{
    int max_len = max(vec1.size(), vec2.size());
    Vector<decltype(vec1[0] + vec2[0])> result(max_len);
    Iterator<decltype(vec1[0] + vec2[0])> iter_result(result);
    Iterator<R> iter_vec1(vec1);
    Iterator<S> iter_vec2(vec2);
    for (int i = 0; iter_result; i++, iter_result++, iter_vec1++, iter_vec2++)
    {
        if (i > vec1.size())
            *iter_result = -*iter_vec2;
        else if (i > vec2.size())
            *iter_result = *iter_vec1;
        else
            *iter_result = *iter_vec1 - *iter_vec2;
    }
    return result;
}


template <typename Type>
Vector<Type> Vector<Type>::operator -()
{
    Vector<Type> new_vector(*this);
    Iterator<Type> iter(new_vector);
    for (; iter; iter++)
        *iter = -*iter;
    
    return new_vector;
}

//пересоздает массив с умным указателем
template <typename Type>
void Vector<Type>::new_dyn_mem(int num_elements)
{
    data_list.reset();
    std::shared_ptr<Type[]> sp_temp(new Type[num_elements], std::default_delete<Type[]>());
    data_list = sp_temp;
}

template<typename Type>
Iterator<Type> Vector<Type>::begin() {
    return Iterator<Type>(*this);
}

template<typename Type>
Iterator<Type> Vector<Type>::end() {
    return Iterator<Type>(*this) + num_elem;
}

template<typename Type>
Vector<Type>::Vector(Vector<Type> &&vec) noexcept {
    num_elem = vec.size();
    new_dyn_mem(num_elem);
    data_list = vec.data_list;
    vec.data_list.reset();
}

template<typename Type>
template<typename S>
Vector<Type> &Vector<Type>::operator&=(const Vector<S> &vec) {
    time_t t_time = time(NULL);
    if (num_elem != 3 || vec.size() != 3)
        throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

    Vector<Type> new_vector(3);
    new_vector = mult_vect_cross(vec);
    *this = new_vector;
    return *this;
}

template<typename Type>
template<typename S>
Vector<Type>& Vector<Type>::mult_vect_cross(const Vector<S> &vec2){
    Vector<Type> result(3);
    Iterator<Type> iter_result(result);
    Iterator<Type> iter_vec1(*this);
    Iterator<S> iter_vec2(vec2);
    iter_result[0] = iter_vec1[1] * iter_vec2[2] - iter_vec1[2] * iter_vec2[1];
    iter_result[1] = iter_vec1[2] * iter_vec2[0] - iter_vec1[0] * iter_vec2[2];
    iter_result[2] = iter_vec1[0] * iter_vec2[1] - iter_vec1[1] * iter_vec2[0];
    *this = result;
    return *this;
}

template<typename Type>
template<typename S>
Vector<Type>& Vector<Type>::add(const Vector<S> &src) {
    return *this += src;
}
template<typename Type>
template<typename S>
Vector<Type>& Vector<Type>::sub(const Vector<S> &src) {
    return *this -= src;
}

template<typename Type>
template<typename S>
decltype(auto) Vector<Type>::operator&(const Vector<S> &vec) const {

    time_t t_time = time(NULL);
    if (num_elem < 0 || vec.size() < 0 || num_elem != vec.size())
        throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    Vector<decltype((*this)[0] + vec[0])> result(3);
    result[0] = (*this)[0];
    result[1] = (*this)[1];
    result[2] = (*this)[2];
    result.mult_vect_cross(vec);

    return result;
}

template<typename Type>
template<typename S>
decltype(auto) Vector<Type>::operator /(const S &div) const{
    time_t t_time = time(NULL);
    if (!div)
        throw zero_divError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    if (num_elem <= 0)
        throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    Type div_new = 1 / div;
    Vector<decltype((*this)[0] + div)> new_vector(num_elem);
    for (int i = 0; i < num_elem; i++)
        new_vector[i] = (*this)[i] * div_new;
    return new_vector;
}


template<typename Type>
template<typename S>
decltype(auto) Vector<Type>::mult_vect_scalar(const Vector<S> &vec) const {
    time_t t_time = time(NULL);
    if (num_elem <= 0 || vec.size() <= 0 || num_elem != vec.size())
        throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    Iterator<Type> it1(*this);
    Iterator<S> it2(vec);
    decltype(auto) sum = (*it1) * (*it2);
    it1++;
    it2++;
    for (;it1; it1++, it2++)
        sum += (*it1) * (*it2);
    return sum;
}

template<typename Type>
template<typename S>
Vector<Type> &Vector<Type>::mult_num(const S &mult) {
    return *this = (*this) *= mult;
}

template<typename Type>
template<typename S>
Vector<Type> &Vector<Type>::div_num(const S &mult) {
    return *this = *this /= mult;
}

template<typename Type>
template<typename S>
decltype(auto) Vector<Type>::operator*(const S &mult) const {
    time_t t_time = time(NULL);
    if (num_elem <= 0)
        throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

    Vector<decltype((*this)[0] + mult)> new_vector(num_elem);
    for (int i = 0; i < num_elem; i++)
        new_vector[i] = (*this)[i] * mult;
    // new_vector = sum_vectors(*this, vec);
    return new_vector;
}

template<typename Type>
ConstIterator<Type> Vector<Type>::cbegin() const {
    return ConstIterator<Type>(*this);
}

template<typename Type>
ConstIterator<Type> Vector<Type>::cend() const {
    return ConstIterator<Type>(*this) + num_elem;
}


#endif /* class_Vector_hpp */
