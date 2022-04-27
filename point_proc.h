//
// Created by jarozin on 26.04.22.
//

#ifndef LAB1_POINT_PROC_H
#define LAB1_POINT_PROC_H
#include "point.h"
double to_rad(double ax);
int sub_point(point &dst, point &d_point);
int add_point(point &dst, point &d_point);
int move_all_points_data(point_data &dst, point &d_point);
int scale_point(point &my_point, point &center, point &scale);
int scale_point_data(point_data &my_points, point &center, point &scale);
int rotate_point_data(point_data &my_points, point &center, point &rot);
int rotate_point(point &my_point, point &center, point &rot);
int rotate_point_x(point &my_point, point &center, double ax);
int rotate_point_y(point &my_point, point &center, double ay);
int rotate_point_z(point &my_point, point &center, double az);
#endif //LAB1_POINT_PROC_H
