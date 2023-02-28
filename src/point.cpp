#include "point.h"
#include "error_handling.h"
#include <iostream>
#include "io.h"
int change_point(point &new_point, double x, double y, double z)
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

int read_points(point_data &dst, FILE *in)
{
    int err = OK;
    if (dst.n < 1)
        err = NO_DOTS;
    for (int i = 0; i < dst.n && !err; i++)
    {
        err = read_point(dst.arr[i], in);
    }
    return err;
}

int alloc_points(point_data &dst, int n)
{
    int err = OK;
    dst.n = n;
    dst.arr = (point *)malloc(sizeof(point) * n);
    if (!dst.arr) 
        err = EMPTY_PTR_ERR;
    return err;
}
void free_points(point_data &src)
{
    if (!src.arr) {
        free(src.arr);
    }
}

int load_points(point_data &points, FILE *in)
{
    int err = OK;
    int n = 0;
    err = read_amount(&n, in);
    if (!err) {
        err = alloc_points(points, n);
        if (!err)
        {
            err = read_points(points, in);
            if (err)
                free_points(points);
        }
    }
    return err;
}