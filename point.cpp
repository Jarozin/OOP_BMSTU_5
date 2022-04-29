//
// Created by jarozin on 25.04.22.
//

#include "point.h"
#include "error_handling.h"
#include <iostream>
int create_point(point &new_point, double x, double y, double z)
{
    new_point.x = x;
    new_point.y = y;
    new_point.z = z;
    return OK;
}

int read_point(point &dst, FILE *in)
{
    int err = OK;
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
    int err = OK;
    if (n < 1)
        err = NO_DOTS;
    for (int i = 0; i < n && !err; i++)
    {
        err = read_point(arr[i], in);
    }
    return err;
}

int alloc_point_data_n(point_data &dst, int n)
{
    int err = OK;
    dst.n = n;
    dst.arr = (point *)malloc(sizeof(point) * n);
    if (!dst.arr) {
        err = EMPTY_PTR_ERR;
    }
    return err;
}
void free_point_data(point_data &src)
{
    if (src.arr != nullptr) {
        free(src.arr);
    }
}

int read_point_data_n(point_data &dst, int n, FILE *in)
{
    int err = OK;
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

