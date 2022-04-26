//
// Created by jarozin on 25.04.22.
//

#include "point.h"
// TODO perenesti vse podkluchenia is .h v .cpp
#include "error_handling.h"
#include <iostream>
point* create_point(double x, double y, double z)
{
    point *newPoint = new point;
    newPoint->x = x;
    newPoint->y = y;
    newPoint->z = z;
    return newPoint;
}

void free_point(point &point)
{
    delete &point;
}

int read_point(point &dst, FILE *in)
{
    int err = NONE;
    if (in == nullptr)
        err = EMPTY_PTR_ERR;
    if (!err)
    {
        if (fscanf(in, "%lf%lf%lf", &dst.x, &dst.y, &dst.z) != 3)
            err = FILE_CONTENT_ERR;
    }
    return err;
}

int read_n_points(point *arr, FILE *in, int n)
{
    int err = NONE;
    if (n < 1)
        err = NO_DOTS;
    for (int i = 0; i < n && !err; i++)
    {
        err = read_point(arr[i], in);
    }
    return err;
}

point_data *alloc_point_data_n(int n)
{
    point_data *new_list = new point_data;
    if (new_list != nullptr) {
        new_list->n = n;
        new_list->arr = new point[n];
        if (new_list->arr == nullptr) {
            free_point_data(*new_list);
            return nullptr;
        }
    }
    return new_list;
}
void free_point_data(point_data &src)
{
    if (src.arr != nullptr) {
        delete[] src.arr;
    }
}

int read_point_data_n(point_data &dst, int n, FILE *in)
{
    int err = NONE;
    if (in == nullptr)
        err = EMPTY_PTR_ERR;
    if (!err)
    {
        if (n < 1)
            err = NO_DOTS;
        if (!err)
        {
            dst.n = n;
            err = read_n_points(dst.arr, in, n);
        }
    }
    return err;
}

