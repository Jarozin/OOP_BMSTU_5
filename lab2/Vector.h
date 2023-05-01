#ifndef class_Vector_h
#define class_Vector_h

#include <stdarg.h>

#include "ReverseIterator.h"
#include "ReverseConstIterator.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <iterator>

#include "BaseVector.h"
#include "ConstIterator.h"
#include "Iterator.h"
#define EPS 1e-5

template <typename T, typename S>
concept convertable = std::convertible_to<T, S> || std::convertible_to<S, T>;

template <typename Type>
concept is_null_constractable = requires {
  Type(0);
};

template <typename Type, typename S>
concept is_multiplyable = requires(Type t, S s) {
  t * s;
};

template <typename Type, typename S>
concept is_divisible = requires(Type t, S s) {
  t / s;
};

template <typename Type, typename S>
concept is_addible = requires(Type t, S s) {
  t + s;
};

template <typename Type, typename S>
concept is_substractable = requires(Type t, S s) {
  t - s;
};

template <VectorType Type>
class Vector : public BaseVector
{
public:
  using value_type = Type;
  using size_type = size_t;
  using difference_type = int;
  using iterator = Iterator<Type>;
  using const_iterator = ConstIterator<Type>;
  using reverse_iterator = ReverseIterator<Type>;
  using const_reverse_iterator = ReverseConstIterator<Type>;

  Vector();
  explicit Vector(int num_elements);
  // заполнить массивом
  Vector(int num_elements, Type *vec);
  Vector(int num_elements, Type var, ...);
  Vector(std::initializer_list<Type> args);
  template <typename Container>
  Vector(const Container &container);
  // iterator начала и конца, не зависит от типов
  template <typename InputIt>
  requires std::random_access_iterator<InputIt>
  Vector(InputIt &iter1, InputIt &iter2);
  explicit Vector(const Vector<Type> &vec);
  Vector(Vector<Type> &&vec) noexcept;
  template <VectorType S>
  explicit Vector(const Vector<S> &vec);
  ~Vector() override;

  Vector<Type> &operator=(const Vector<Type> &vec);
  Vector<Type> &operator=(Vector<Type> &&vec) noexcept;
  Vector<Type> &operator=(std::initializer_list<Type> args);
  template <VectorType S>
  Vector<Type> &operator=(const Vector<S> &vec);
  template <typename Container>
  Vector<Type> &operator=(const Container &container);

  bool is_zero() const;
  bool is_single() const;
  int size() const override;

  Iterator<Type> begin();
  ConstIterator<Type> begin() const;
  ConstIterator<Type> cbegin() const;

  ReverseIterator<Type> rbegin();
  ReverseConstIterator<Type> rbegin() const;
  ReverseConstIterator<Type> crbegin() const;

  Iterator<Type> end();
  ConstIterator<Type> end() const;
  ConstIterator<Type> cend() const;

  ReverseIterator<Type> rend();
  ReverseConstIterator<Type> rend() const;
  ReverseConstIterator<Type> crend() const;
  // нахождение длины стороны из координат в векторе
  auto len() const;

  Type &get_elem_Vector(int index);
  const Type &get_elem_Vector(int index) const;
  bool set_elem_Vector(int index, const Type &vec);
  Type &operator[](int index);
  const Type &operator[](int index) const;

  // приводит вектор к единичному(в длину)
  Vector<Type> get_single_vector() const;

  // умножение и деление на число
  template <typename S>
  requires is_multiplyable<Type,S>
  Vector<Type> &operator*=(const S &mult);
  template <typename S>
  requires convertable<Type, S> && is_multiplyable<Type,S>
  decltype(auto) operator*(const S &mult) const;
  template <typename S>
  requires is_multiplyable<Type,S>
  Vector<Type> &mult_num(const S &mult);

  template <typename S>
  requires is_divisible<Type,S>
  Vector<Type> &operator/=(const S &div);
  template <typename S>
  requires convertable<Type, S> && is_divisible<Type,S>
  decltype(auto) operator/(const S &div) const;
  template <typename S>
  requires is_divisible<Type,S>
  Vector<Type> &div_num(const S &div);

  // унарный минус
  Vector<Type> operator-();

  // скалярное умнжение
  template <VectorType S>
  requires convertable<Type, S> && is_multiplyable<Type,S>
  decltype(auto) operator^(const Vector<S> &vec) const;
  template <VectorType S>
  requires convertable<Type, S> && is_multiplyable<Type,S>
  decltype(auto) mult_vect_scalar(const Vector<S> &vec2) const;

  // векторное умножение
  template <VectorType S>
  Vector<Type> &operator&=(const Vector<S> &vec);
  template <VectorType S>
  requires convertable<Type, S>
  decltype(auto) operator&(const Vector<S> &) const;
  template <VectorType S>
  requires convertable<Type,S> && is_multiplyable<Type,S> &&
  (is_substractable<Type,Type> || is_substractable<S,S>)
  Vector<Type> &mult_vect_cross(const Vector<S> &vec2);

  // поэлементное сложение
  template <VectorType S>
  requires convertable<Type, S> && is_addible<Type,S>
  decltype(auto) operator+(const Vector<S> &) const;
  template <VectorType S>
  requires is_addible<Type,S>
  Vector<Type> &operator+=(const Vector<S> &);
  template <VectorType S>
  requires is_addible<Type,S>
  Vector<Type> &add(const Vector<S> &);

  // поэлементное вычитание
  template <VectorType S>
  requires convertable<Type, S>
  decltype(auto) operator-(const Vector<S> &) const;
  template <VectorType S>
  requires is_substractable<Type,S>
  Vector<Type> &sub(const Vector<S> &);
  template <VectorType S>
  requires is_substractable<Type,S>
  Vector<Type> &operator-=(const Vector<S> &);

  template <VectorType S>
  double angle_between_vectors(const Vector<S> &) const;
  template <VectorType S>
  bool is_collinearity(const Vector<S> &) const;
  template <VectorType S>
  bool is_orthogonality(const Vector<S> &) const;

  bool operator==(const Vector<Type> &) const;
  bool operator!=(const Vector<Type> &) const;

private:
  std::shared_ptr<Type[]> data_list_;
  friend class Iterator<Type>;
  friend class ConstIterator<Type>;
  friend class ReverseIterator<Type>;
  friend class ReverseConstIterator<Type>;
protected:
  Type sum_all_elem() const;

  void new_dyn_mem(int);
};

template <VectorType S, VectorType R>
requires convertable<R, S>
decltype(auto) sum_vectors(const Vector<R> &vec1,
                                         const Vector<S> &vec2)
{
  return vec1 + vec2;
}

template <VectorType S, typename R>
requires convertable<R, S>
decltype(auto) difference_vectors(const Vector<R> &vec1,
                                                const Vector<S> &vec2)
{
  return vec1 - vec2;
}


template <typename Type, VectorType S>
  requires convertable<Type, S> decltype(auto)
operator*(const S &mult, const Vector<Type> &vec)
{
  return vec * mult;
}


template <typename Type>
std::ostream &operator<<(std::ostream &os, const Vector<Type> &vec)
{
  Iterator<Type> iter(vec);

  if (!iter)
  {
    os << "Vector is empty.";
    return os;
  }

  os << '(' << *iter;
  for (iter++; iter; iter++)
    os << ", " << *iter;
  os << ')';

  return os;
}

#endif
