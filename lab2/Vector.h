#ifndef class_Vector_h
#define class_Vector_h

#include <stdarg.h>

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

template <VectorType Type>
class Vector : public BaseVector
{
public:
  using value_type = Type;
  using size_type = size_t;
  using difference_type = std::ptrdiff_t;
  using iterator = Iterator<Type>;
  using const_iterator = ConstIterator<Type>;

  Vector();
  explicit Vector(int num_elements);
  // заполнить массивом
  Vector(int num_elements, Type *vec);
  Vector(int num_elements, Type var, ...);
  Vector(std::initializer_list<Type> args);
  template <typename Container>
  Vector(const Container container);
  // iterator начала и конца, не зависит от типов
  template <typename InputIt>
  //requires std::random_access_iterator<InputIt>
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

  Type &operator[](int index);
  const Type &operator[](int index) const;

  bool is_zero() const;
  bool is_single() const;
  int size() const override;

  Iterator<Type> begin();
  ConstIterator<Type> cbegin() const;
  Iterator<Type> end();
  ConstIterator<Type> cend() const;

  // нахождение длины стороны из координат в векторе
  Type len() const;

  Type &get_elem_Vector(int index);
  const Type &get_elem_Vector(int index) const;
  bool set_elem_Vector(int index, const Type &vec);

  // приводит вектор к единичному(в длину)
  Vector<Type> get_single_vector() const;

  // умножение и деление на число
  template <VectorType S>
  Vector<Type> &operator*=(const S &mult);
  template <VectorType S>
  requires convertable<Type, S>
  decltype(auto) operator*(const S &mult) const;
  template <VectorType S>
  Vector<Type> &mult_num(const S &mult);

  template <VectorType S>
  Vector<Type> &operator/=(const S &div);
  template <VectorType S>
    requires convertable<Type, S>
  decltype(auto) operator/(const S &div) const;
  template <VectorType S>
  Vector<Type> &div_num(const S &mult);

  // унарный минус
  Vector<Type> operator-();

  // скалярное умнжение
  template <VectorType S>
    requires convertable<Type, S> decltype(auto)
  operator^(const Vector<S> &vec) const;
  template <VectorType S>
    requires convertable<Type, S> decltype(auto)
  mult_vect_scalar(const Vector<S> &vec2) const;

  // векторное умножение
  template <VectorType S>
  Vector<Type> &operator&=(const Vector<S> &vec);
  template <VectorType S>
    requires convertable<Type, S> decltype(auto)
  operator&(const Vector<S> &) const;
  template <VectorType S>
  Vector<Type> &mult_vect_cross(const Vector<S> &vec2);

  // поэлементное сложение
  template <VectorType S>
    requires convertable<Type, S> decltype(auto)
  operator+(const Vector<S> &) const;
  template <VectorType S>
  Vector<Type> &operator+=(const Vector<S> &);
  template <VectorType S>
  Vector<Type> &add(const Vector<S> &);
  template <VectorType S, typename R>
    requires convertable<R, S>
  static decltype(auto) sum_vectors(const Vector<R> &vec1,
                                    const Vector<S> &vec2);

  // поэлементное вычитание
  template <VectorType S>
    requires convertable<Type, S> decltype(auto)
  operator-(const Vector<S> &) const;
  template <VectorType S>
  Vector<Type> &sub(const Vector<S> &);
  template <VectorType S>
  Vector<Type> &operator-=(const Vector<S> &);
  template <VectorType S, typename R>
    requires convertable<R, S>
  static decltype(auto) difference_vectors(const Vector<R> &vec1,
                                           const Vector<S> &vec2);

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

protected:
  Type sum_all_elem() const;

  void new_dyn_mem(int);
};

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
