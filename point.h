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

struct point_list{
    point *arr;
    int n;
};
point* create_point(double x, double y, double z);
void delete_point(point *point);
void copy(point &dst, point src);
int read_point(point &dst, FILE *in);
int read_n_points(point *arr, FILE *in, int n);
int setup_n_points(point *dst, FILE *in, int n);

point_list *alloc_point_list_n(int n);
void free_point_list(point_list &src);
int read_point_list_n(point_list &dst, int n, FILE *in);