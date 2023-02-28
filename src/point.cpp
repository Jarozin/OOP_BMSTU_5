#include "point.h"
#include "error_handling.h"
#include <iostream>
#include "io.h"
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
    point_data new_data;
    new_data.n = n;
    new_data.arr = (point *)malloc(sizeof(point) * n);
    if (!new_data.arr) {
        err = EMPTY_PTR_ERR;
    }
    if (!err)
    {
        free_point_data(dst);
        dst = new_data;
    }
    return err;
}
void free_point_data(point_data &src)
{
    if (!src.arr) {
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

int read_points(point_data &points, FILE *in)
{
    int err = OK;
    int n = 0;
    point_data new_points;
    err = read_amount(&n, in);
    if (!err) {
        err = alloc_point_data_n(new_points, n);
        if (!err) {
            err = read_point_data_n(new_points, n, in);
        }
    }
    if (err)
        free_point_data(new_points);
    else
    {
        free_point_data(points);
        points = new_points;
    }
    return err;
}