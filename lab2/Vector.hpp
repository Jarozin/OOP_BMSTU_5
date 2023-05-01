#ifndef class_Vector_hpp
#define class_Vector_hpp

#include <stdlib.h>

#include <cstddef>
#include <iostream>
#include <utility>
#include <concepts>
#include <algorithm>

#include "Vector.h"
#include "my_errors.h"

int max(int num1, int num2)
{
  if (num1 >= num2)
    return num1;
  return num2;
}

template <VectorType Type>
Vector<Type>::~Vector()
{
  if (data_list_)
    data_list_.reset();
}

template <VectorType Type>
Vector<Type>::Vector()
{
  new_dyn_mem(0);
}

template <VectorType Type>
requires is_null_constractable<Type>
Vector<Type>::Vector(int num_elements)
{
  time_t t_time = time(NULL);
  if (num_elements <= 0)
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

  new_dyn_mem(num_elements);

  if (!data_list_)
    throw memError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

  for (auto &iter : *this)
    iter = Type(0);
}

template <VectorType Type>
Vector<Type>::Vector(int num_elements, Type vec, ...)
{
  time_t t_time = time(NULL);
  if (num_elements < 1)
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

  new_dyn_mem(num_elements);

  if (!data_list_)
    throw memError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

  va_list ap;
  va_start(ap, vec);
  for (auto &iter : *this)
  {
    iter = vec;
    vec = va_arg(ap, Type);
  }
  va_end(ap);
}

template <VectorType Type>
template <typename Container>
Vector<Type>::Vector(const Container& container)
{
  new_dyn_mem(container.size());
  auto my_it = this->begin();
  for (const auto& it : container)
  {
    *my_it = it;
    my_it++;
  }
};

template <VectorType Type>
Vector<Type>::Vector(int num_elements, Type *vec)
{
  time_t t_time = time(NULL);
  if (num_elements <= 0)
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

  new_dyn_mem(num_elements);

  Iterator<Type> iter(*this);
  for (int i = 0; iter; i++, iter++)
    *iter = vec[i];
}

template <VectorType Type>
Vector<Type>::Vector(std::initializer_list<Type> args)
{
  if (args.size() == 0)
    Vector();

  new_dyn_mem(int(args.size()));

  Iterator<Type> iter(*this);
  for (auto &element : args)
  {
    *iter = element;
    iter++;
  }
}

template <VectorType Type>
template <typename InputIt>
requires std::random_access_iterator<InputIt>
Vector<Type>::Vector(InputIt &iter1, InputIt &iter2)
{
  time_t t_time = time(NULL);
  num_elem_ = std::distance(iter1, iter2);
  if (num_elem_ <= 0)
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  new_dyn_mem(num_elem_);
  Iterator<Type> new_iter(*this);
  for (auto i = iter1; i < iter2; i++, new_iter++)
    *new_iter = *i;
}

template <VectorType Type>
Type &Vector<Type>::get_elem_Vector(int index)
{
  time_t t_time = time(NULL);
  if (index < 0 || index >= num_elem_)
    throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

  return *(this->begin() + index);
}

template <VectorType Type>
const Type &Vector<Type>::get_elem_Vector(int index) const
{
  time_t t_time = time(NULL);
  if (index < 0 || index >= num_elem_)
    throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

  return *(this->cbegin() + index);
}

template <VectorType Type>
bool Vector<Type>::operator==(const Vector<Type> &vec) const
{
  return std::equal(this->cbegin(), this->cend(), vec.cbegin(), vec.cend());
}

template <VectorType Type>
bool Vector<Type>::operator!=(const Vector<Type> &vec) const
{
  return !(*this == vec);
}

template <VectorType Type>
auto Vector<Type>::len(void) const
{
  time_t t_time = time(NULL);
  if (num_elem_ <= 0)
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

  ConstIterator<Type> iter(*this);
  double sum = 0;
  for (; iter; iter++)
    sum += *iter * *iter;

  return sqrt(sum);
}

template <VectorType Type>
template <VectorType S>
requires convertable<Type, S> && is_multiplyable<Type,S>
decltype(auto) Vector<Type>::operator^(const Vector<S> &vec) const
{
  time_t t_time = time(NULL);
  if (num_elem_ <= 0 || num_elem_ != vec.size())
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

  Vector<decltype((*this)[0] + vec[0])> new_vector(num_elem_);
  for (int i = 0; i < new_vector.size(); i++)
    new_vector[i] = (*this)[i] * vec[i];
  return new_vector.sum_all_elem();
}

template <VectorType Type>
template <VectorType S>
requires convertable<Type, S> && is_addible<Type,S>
decltype(auto) Vector<Type>::operator+(const Vector<S> &vec) const
{
  time_t t_time = time(NULL);
  if (num_elem_ <= 0 || num_elem_ != vec.size())
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

  Vector<decltype((*this)[0] + vec[0])> new_vector(num_elem_);
  for (int i = 0; i < num_elem_; i++)
    new_vector[i] = (*this)[i] + vec[i];
  return new_vector;
}

template <VectorType Type>
template <VectorType S>
requires is_addible<Type,S>
Vector<Type> &Vector<Type>::operator+=(const Vector<S> &vec)
{
  time_t t_time = time(NULL);
  if (num_elem_ <= 0 || num_elem_ != vec.size())
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

  return *this = *this + vec;
}

template <VectorType Type>
template <VectorType S>
requires convertable<Type, S>
decltype(auto) Vector<Type>::operator-(const Vector<S> &vec) const
{
  time_t t_time = time(NULL);
  if (num_elem_ <= 0 || num_elem_ != vec.size())
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

  Vector<decltype((*this)[0] + vec[0])> new_vector(num_elem_);
  for (int i = 0; i < new_vector.size(); i++)
    new_vector[i] = (*this)[i] - vec[i];
  return new_vector;
}

template <VectorType Type>
template <VectorType S>
requires is_substractable<Type,S>
Vector<Type> &Vector<Type>::operator-=(const Vector<S> &vec)
{
  time_t t_time = time(NULL);
  if (num_elem_ <= 0 || num_elem_ != vec.size())
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  return *this = *this - vec;
}

template <VectorType Type>
template <typename S>
requires is_multiplyable<Type,S>
Vector<Type> &Vector<Type>::operator*=(const S &mult)
{
  time_t t_time = time(NULL);
  if (num_elem_ <= 0)
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  for (auto &iter : *this)
    iter *= mult;

  return *this;
}

template <VectorType Type>
template <typename S>
requires is_divisible<Type,S>
Vector<Type> &Vector<Type>::operator/=(const S &div)
{
  time_t t_time = time(NULL);
  if (num_elem_ <= 0)
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

  if (!div)
    throw zero_divError(__FILE__, typeid(*this).name(), __LINE__,
                        ctime(&t_time));

  for (auto &iter : *this)
    iter /= div;

  return *this;
}

template <VectorType Type>
Type Vector<Type>::sum_all_elem() const
{
  time_t t_time = time(NULL);
  if (num_elem_ <= 0)
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

  ConstIterator<Type> iter(*this);
  Type sum = 0;
  for (; iter; iter++)
    sum += *iter;

  return sum;
}

template <VectorType Type>
template <VectorType S>
double Vector<Type>::angle_between_vectors(const Vector<S> &vec) const
{
  time_t t_time = time(NULL);
  if (!this->len() || !vec.len())
    throw zero_divError(__FILE__, typeid(*this).name(), __LINE__,
                        ctime(&t_time));

  double angle = ((*this) ^ vec) / (this->len() * vec.len());
  return acos(angle) * 180 / M_PI;
}

template <VectorType Type>
bool Vector<Type>::is_single() const
{
  if (abs(this->len() - 1) < EPS)
    return true;
  return false;
}

template <VectorType Type>
bool Vector<Type>::is_zero() const
{
  if (abs(this->len()) < EPS)
    return true;
  return false;
}

template <VectorType Type>
template <VectorType S>
Vector<Type> &Vector<Type>::operator=(const Vector<S> &vec)
{
  if (this->size() != vec.size())
  {
    new_dyn_mem(vec.size());
  }
  for (int i = 0; i < num_elem_; i++)
    data_list_[i] = vec[i];
  return *this;
}

template <VectorType Type>
Vector<Type> &Vector<Type>::operator=(const Vector<Type> &vec)
{
  if (this->size() != vec.size())
  {
    new_dyn_mem(vec.size());
  }
  for (int i = 0; i < num_elem_; i++)
    data_list_[i] = vec[i];
  return *this;
}
template <VectorType Type>
Vector<Type> &Vector<Type>::operator=(std::initializer_list<Type> args)
{
  new_dyn_mem(int(args.size()));

  Iterator<Type> iter(*this);
  for (auto &element : args)
  {
    *iter = element;
    iter++;
  }

  return *this;
}

template <VectorType Type>
Vector<Type> &Vector<Type>::operator=(Vector<Type> &&vec) noexcept
{
  num_elem_ = vec.size();
  data_list_ = std::move(vec.data_list_);
  return *this;
}

template <VectorType Type>
template <typename Container>
Vector<Type> &Vector<Type>::operator=(const Container &container)
{
  new_dyn_mem(container.size());
  auto my_it = this->begin();
  for (const auto& it : container)
  {
    *my_it = it;
    my_it++;
  }
  return *this;
}


template <VectorType Type>
Vector<Type>::Vector(const Vector<Type> &vec)
{
  new_dyn_mem(vec.size());

  Iterator<Type> iter_new(*this);
  Iterator<Type> iter(vec);
  for (; iter_new; iter++, iter_new++)
    *iter_new = *iter;
}

template <VectorType Type>
template <VectorType S>
Vector<Type>::Vector(const Vector<S> &vec)
{
  new_dyn_mem(vec.size());

  Iterator<Type> iter_new(*this);
  Iterator<S> iter(vec);
  for (; iter_new; iter++, iter_new++)
    *iter_new = *iter;
}

template <VectorType Type>
Type &Vector<Type>::operator[](int index)
{
  return get_elem_Vector(index);
}

template <VectorType Type>
const Type &Vector<Type>::operator[](int index) const
{
  return get_elem_Vector(index);
}

template <VectorType Type>
bool Vector<Type>::set_elem_Vector(int index, const Type &num)
{
  if (index < 0 || index >= num_elem_)
    return false;

  get_elem_Vector(index) = num;
  return true;
}

template <VectorType Type>
Vector<Type> Vector<Type>::get_single_vector() const
{
  Vector<Type> new_vector(*this);
  Type len = this->len();

  for (auto &iter : new_vector)
    iter /= len;

  return new_vector;
}

template <VectorType Type>
int Vector<Type>::size() const
{
  return num_elem_;
}

template <VectorType Type>
template <VectorType S>
bool Vector<Type>::is_collinearity(const Vector<S> &vec) const
{
  if (this->angle_between_vectors(vec) < EPS)
    return true;
  return false;
}

template <VectorType Type>
template <VectorType S>
bool Vector<Type>::is_orthogonality(const Vector<S> &vec) const
{
  if (abs(this->angle_between_vectors(vec) - 90) < EPS)
    return true;
  return false;
}

template <VectorType Type>
Vector<Type> Vector<Type>::operator-()
{
  Vector<Type> new_vector(*this);
  for (auto &iter : new_vector)
    iter = -iter;

  return new_vector;
}

// пересоздает массив с умным указателем
template <VectorType Type>
void Vector<Type>::new_dyn_mem(int num_elements)
{
  data_list_.reset();
  num_elem_ = num_elements;
  std::shared_ptr<Type[]> sp_temp(new Type[num_elements],
                                  std::default_delete<Type[]>());
  data_list_ = sp_temp;
}

template <VectorType Type>
Iterator<Type> Vector<Type>::begin()
{
  return Iterator<Type>(*this);
}

template <VectorType Type>
ConstIterator<Type> Vector<Type>::begin() const
{
  return this->cbegin();
}


template <VectorType Type>
Iterator<Type> Vector<Type>::end()
{
  return Iterator<Type>(*this) + num_elem_;
}

template <VectorType Type>
ConstIterator<Type> Vector<Type>::end() const
{
  return this->cend();
}

template <VectorType Type>
Vector<Type>::Vector(Vector<Type> &&vec) noexcept
{
  num_elem_ = vec.size();
  // Shared ptr сам чистит при присв. move
  data_list_ = std::move(vec.data_list_);
}

template <VectorType Type>
template <VectorType S>
Vector<Type> &Vector<Type>::operator&=(const Vector<S> &vec)
{
  time_t t_time = time(NULL);
  if (num_elem_ != 3 || vec.size() != 3)
    throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

  Vector<Type> new_vector(3);
  new_vector = mult_vect_cross(vec);
  *this = new_vector;
  return *this;
}

template <VectorType Type>
template <VectorType S>
requires convertable<Type,S> && is_multiplyable<Type,S> &&
(is_substractable<Type,Type> || is_substractable<S,S>)
Vector<Type> &Vector<Type>::mult_vect_cross(const Vector<S> &vec2)
{
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

template <VectorType Type>
template <VectorType S>
requires is_addible<Type,S>
Vector<Type> &Vector<Type>::add(const Vector<S> &src)
{
  return *this += src;
}
template <VectorType Type>
template <VectorType S>
requires is_substractable<Type,S>
Vector<Type> &Vector<Type>::sub(const Vector<S> &src)
{
  return *this -= src;
}

template <VectorType Type>
template <VectorType S>
requires convertable<Type, S>
decltype(auto) Vector<Type>::operator&(const Vector<S> &vec) const
{
  time_t t_time = time(NULL);
  if (num_elem_ <= 0 || num_elem_ != vec.size())
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  Vector<decltype((*this)[0] + vec[0])> result(3);
  result[0] = (*this)[0];
  result[1] = (*this)[1];
  result[2] = (*this)[2];
  result.mult_vect_cross(vec);

  return result;
}

template <VectorType Type>
template <typename S>
requires convertable<Type, S> && is_divisible<Type,S>
decltype(auto) Vector<Type>::operator/(const S &div) const
{
  time_t t_time = time(NULL);
  if (!div)
    throw zero_divError(__FILE__, typeid(*this).name(), __LINE__,
                        ctime(&t_time));
  if (num_elem_ <= 0)
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  Type div_new = 1 / div;
  Vector<decltype((*this)[0] + div)> new_vector(num_elem_);
  for (int i = 0; i < num_elem_; i++)
    new_vector[i] = (*this)[i] * div_new;
  return new_vector;
}

template <VectorType Type>
template <VectorType S>
requires convertable<Type, S> && is_multiplyable<Type,S>
decltype(auto) Vector<Type>::mult_vect_scalar(const Vector<S> &vec) const
{
  time_t t_time = time(NULL);
  if (num_elem_ <= 0 || vec.size() <= 0 || num_elem_ != vec.size())
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
  Iterator<Type> it1(*this);
  Iterator<S> it2(vec);
  decltype(auto) sum = (*it1) * (*it2);
  it1++;
  it2++;
  for (; it1; it1++, it2++)
    sum += (*it1) * (*it2);
  return sum;
}

template <VectorType Type>
template <typename S>
requires is_multiplyable<Type,S>
Vector<Type> &Vector<Type>::mult_num(const S &mult)
{
  return *this *= mult;
}

template <VectorType Type>
template <typename S>
requires is_divisible<Type,S>
Vector<Type> &Vector<Type>::div_num(const S &mult)
{
  return *this /= mult;
}

template <VectorType Type>
template <typename S>
requires convertable<Type, S> && is_multiplyable<Type,S>
decltype(auto) Vector<Type>::operator*(const S &mult) const
{
  time_t t_time = time(NULL);
  if (num_elem_ <= 0)
    throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

  Vector<decltype((*this)[0] + mult)> new_vector(num_elem_);
  for (int i = 0; i < num_elem_; i++)
    new_vector[i] = (*this)[i] * mult;
  return new_vector;
}

template <VectorType Type>
ConstIterator<Type> Vector<Type>::cbegin() const
{
  return ConstIterator<Type>(*this);
}

template <VectorType Type>
ConstIterator<Type> Vector<Type>::cend() const
{
  return ConstIterator<Type>(*this) + num_elem_;
}

#endif /* class_Vector_hpp */
