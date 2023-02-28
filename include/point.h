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

int alloc_points(point_data &dst, int n);
void free_points(point_data &src);
int read_points(point_data &dst, FILE *in);
int load_points(point_data &points, FILE *in);
#endif //LAB1_POINT_H