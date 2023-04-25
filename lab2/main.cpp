#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <string>

#include "ConstIterator.h"
#include "Vector.hpp"
#include "my_errors.h"

struct Sum
{
  void operator()(int n) { sum += n; }
  int sum{0};
};

int main()
{
  try
  {

    std::cout << "Test constructors\n\n";

    Vector<double> v1;
    std::cout << "Default:\n";
    std::cout << v1 << "\n";

    std::cout << "With parameters: \n";
    Vector<double> v2(2, 3., 4.);
    Vector<double> v3(3, 3.0, 4.0, 0.0);
    std::cout << v2 << "\n"
              << v3 << "\n";

    std::cout << "From array: \n";
    double arr[5] = {5, 1, 7, 4, 0};
    Vector<double> v4(5, arr);
    std::cout << v4 << "\n";

    std::cout << "From existing vector:\n";
    Vector<double> v5(v3);
    std::cout << v5 << "\n";

    std::cout << "Move semancics:\n";
    Vector<double> vm(std::move(v5));
    std::cout << vm << std::endl;
    try
    {
      std::cout << v5 << std::endl;
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << std::endl << std::endl;
    }

    std::cout << "Move semancics with = operator:\n";
    v5 = std::move(vm);
    std::cout << v5 << std::endl;
    try
    {
      std::cout << vm << std::endl;
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << std::endl << std::endl;
    }

    std::cout << "\nTest methods\n\n";

    std::cout << "Length of vector (3, 4, 0): " << v3.len() << "\n";
    std::cout << "Size of vector (3, 4, 0): " << v3.size() << "\n";
    std::cout << "Get second element {5, 1, 7, 4, 0}: " << v4.get_elem_Vector(1)
              << "\n";

    std::cout << "Multiply by 10: " << (v4 *= 10) << "\n";
    std::cout << "Divide by 10: " << (v4 /= 10) << "\n";
    std::cout << "Change to opposite direction (unary minus) {3, 4, 0}: "
              << (-v3) << "\n\n";

    Vector<double> v12{1., 2., 3., 4., 5.};
    std::cout << "Init vector {1., 2., 3., 4., 5.}: " << v12 << "\n";
    v12[2] = 10.;
    std::cout << "Change third element using []: " << v12 << "\n";
    v12.set_elem_Vector(3, 11.);
    std::cout << "Change fourth element using set_elem_Vector method: " << v12
              << "\n";
    v12 = v12.get_single_vector();
    std::cout << "Get vector with lenght of one: " << v12 << "\n\n";

    Vector<double> v6(3, 3.0, 4.0, 0.0);
    Vector<int> v7(2, 10, 0);
    Vector<int> v8(2, 0, 10);
    std::cout << "Find angle between {10, 0} and {0, 10}: "
              << v7.angle_between_vectors(v8) << "\n";
    Vector<double> v9(2, 5., 5.);
    Vector<double> v10(2, 10., 0.0);
    std::cout << "Fing angle between {5, 5} and {10, 0}: "
              << v9.angle_between_vectors(v10) << "\n";
    Vector<double> v20(2, 20., 20.0);
    std::cout << "Check collinearity of {5, 5} and {20, 20}: "
              << v9.is_collinearity(v20) << "\n";
    std::cout << "Scalar multiplication {5, 5} and {10, 0}: " << (v9 ^ v10)
              << "\n\n";
    std::cout << "Scalar multiplication {5, 5} and {10, 0}: "
              << (v9.mult_vect_scalar(v10)) << "\n\n";

    Vector<double> v11(4, 1., 0., 0., 0.);
    std::cout << v11 << std::endl;
    std::cout << "Is vector of length one {4, 1, 0, 0, 0}? " << v11.is_single()
              << "\n";
    std::cout << "Are two vectors equal? {3, 4, 0} and {3, 4, 0}: "
              << (v3 == v6) << "\n";
    std::cout << "Are two vectors unequal? {3, 4, 0} and {3, 4, 0}: "
              << (v3 != v6) << "\n";

    Vector<int> v21({5, 2, 3, 4});
    std::cout << v11 + v21 << std::endl;
    std::cout << v21 - v11 << std::endl;
    std::cout << (v21 -= v11) << std::endl;
    std::cout << v21 - v11 << std::endl;
    Iterator<int> it1(v21);
    Iterator<int> it2(v21);
    // it1 = it2;
    it2 += 3;
    int *a = new int[2];
    int *b = a + 2;
    *a = 4;
    *(a + 1) = 55;
    Vector<int> v22(it1, it2);
    std::cout << v22 << std::endl;

    Vector<int> v23(a, b);
    std::cout << v23 << std::endl;
    it1++;
    std::cout << it1[0] << " " << it1[1] << std::endl;
    std::cout << *it1 << " " << *(it1 + 1) << std::endl;

    std::cout << "before: ";
    std::cout << v21 << std::endl;
    std::for_each(v21.begin(), v21.end(), [](int &n)
                  { n++; });

    Sum s = std::for_each(v21.begin(), v21.end(), Sum());
    std::cout << "after: ";
    std::cout << v21 << '\n';
    std::cout << "sum: " << s.sum << '\n';

    Vector<int> v24({1, 2, 3});
    Vector<double> v25({5, -2, 12});
    std::cout << (v24 & v25) << std::endl;
    v24 &= v25;
    std::cout << v24 << std::endl;

    Vector<int> v26({1, 2, 3});
    std::cout << v26.add(v25) << " " << v26 << std::endl;
    std::cout << v26.sub(v25) << std::endl;
    std::cout << 5 * v26 << "=" << v26 * 5 << std::endl;
    std::cout << (v26 *= 5) << std::endl;
    std::cout << (v26 /= 5) << std::endl;
    std::cout << v26.mult_num(5) << std::endl;
    std::cout << v26.div_num(5) << std::endl;
    std::cout << v26.mult_num(5.9) << std::endl;
    std::cout << v26.div_num(5.9) << std::endl;
    std::cout << Vector<int>::difference_vectors(v26, v25) << std::endl;
    std::cout << Vector<int>::sum_vectors(v26, v25) << std::endl;
    Vector<float> float_vector({1.5, 2.4, 9.1});
    Vector<int> int_vector(float_vector);
    std::cout << "Float version: " << float_vector << ", int version: " << int_vector << std::endl;
    int_vector = float_vector * 5;
    std::cout << "Float * 5 in int: " << int_vector << std::endl;
    Vector<std::string> string_vector({"First value", "Second value"});
    for (Vector<std::string>::iterator it = string_vector.begin(); it < string_vector.end(); it++)
      std::cout << *it << std::endl;
    //Required нас от этого защищает
    // int ptr1 = 5;
    // int ptr2 = 6;
    //Vector<int *> ptr_vector(&ptr1, &ptr2);
    //std::cout << string_vector + int_vector << std::endl;
  }
  catch (baseError &err)
  {
    std::cout << err.what() << std::endl;
  }
  return 0;
}
