//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_POINT_H
#define LAB1_POINT_H


#include <iostream>
#include "error_handling.h"
#include <cmath>
#define PI 3.14159265

struct point{
    double x;
    double y;
    double z;
};

struct point_data{
    point *arr;
    int n;
};
point* create_point(double x, double y, double z);
void free_point(point &point);
void copy(point &dst, point src);
int read_point(point &dst, FILE *in);
int read_n_points(point *arr, FILE *in, int n);
int setup_n_points(point *dst, FILE *in, int n);

point_data *alloc_point_data_n(int n);
void free_point_data(point_data &src);
int read_point_data_n(point_data &dst, int n, FILE *in);
int setup_points_list_n(point_data *dst, int n, FILE *in);
int move_point(point &dst, double dx, double dy, double dz);
int move_all_points_data(point_data &dst, double dx, double dy, double dz);
int scale_point(point &my_point, point &center, double kx, double ky, double kz);
int scale_point_data(point_data &my_points, point &center, double kx, double ky, double kz);
int rotate_point_data(point_data &my_points, point &center, double ax, double ay, double az);
int rotate_point(point &my_point, point &center, double ax, double ay, double az);
int rotate_point_x(point &my_point, point &center, double ax);
int rotate_point_y(point &my_point, point &center, double ay);
int rotate_point_z(point &my_point, point &center, double az);
#endif //LAB1_POINT_H