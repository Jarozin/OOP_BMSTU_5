//
// Created by jarozin on 25.04.22.
//

#include "point.h"
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
void copy(point &dst, point src)
{
    dst.x = src.x;
    dst.y = src.y;
    dst.z = src.z;
}
int read_point(point &dst, FILE *in)
{
    int err = NONE;
    if (in == nullptr)
        err = EMPTY_PTR_ERR;
    if (!err)
    {
        if (fscanf(in, "%lf%lf", &dst.x, &dst.y) != 2)
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
int setup_n_points(point *dst, FILE *in, int n)
{
    int err = NONE;
    if (n < 1)
        err = NO_DOTS;
    if (!err) {
        dst = new point[n];
        if (!dst)
            err = EMPTY_PTR_ERR;
        if (!err)
        {
            err = read_n_points(dst, in, n);
        }
    }
    return err;
}


point_list *alloc_point_list_n(int n)
{
    point_list *new_list = new point_list;
    if (new_list != nullptr) {
        new_list->n = n;
        new_list->arr = new point[n];
        if (new_list->arr == nullptr) {
            free_point_list(*new_list);
            return nullptr;
        }
    }
    return new_list;
}
void free_point_list(point_list &src)
{
    if (src.arr != nullptr) {
        delete[] src.arr;
    }
    delete &src;
}

int read_point_list_n(point_list &dst, int n, FILE *in)
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

int setup_points_list_n(point_list *dst, int n, FILE *in)
{
    int err = NONE;
    if (n < 1)
        err = NO_DOTS;
    if (!err)
    {
        dst = alloc_point_list_n(n);
        if (dst != nullptr)
        {
            err = read_point_list_n(*dst, n, in);
        }
    }
    return err;
}