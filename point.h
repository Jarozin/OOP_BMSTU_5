//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_POINT_H
#define LAB1_POINT_H

#include <iostream>
struct point{
    double x;
    double y;
    double z;
};

struct point_data{
    point *arr;
    int n;
};
int create_point(point &new_point, double x, double y, double z);
int read_point(point &dst, FILE *in);
int read_n_points(point *arr, FILE *in, int n);

int alloc_point_data_n(point_data &dst, int n);
void free_point_data(point_data &src);
int read_point_data_n(point_data &dst, int n, FILE *in);
#endif //LAB1_POINT_H