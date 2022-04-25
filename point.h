//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_POINT_H
#define LAB1_POINT_H

#endif //LAB1_POINT_H
#include <iostream>
#include "error_handling.h"
struct point{
    double x;
    double y;
    double z;
};

point* create_point(double x, double y, double z);
void delete_point(point *point);
void copy(point &dst, point src);
int read_point(point &dst, FILE *in);
int read_n_points(point *arr, FILE *in, int n);
int setup_n_points(point *dst, FILE *in, int n);