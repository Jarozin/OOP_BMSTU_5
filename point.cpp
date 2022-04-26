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

int setup_points_list_n(point_data *dst, int n, FILE *in)
{
    int err = NONE;
    if (n < 1)
        err = NO_DOTS;
    if (!err)
    {
        dst = alloc_point_data_n(n);
        if (dst != nullptr)
        {
            err = read_point_data_n(*dst, n, in);
        }
    }
    return err;
}

int move_point(point &dst, double dx, double dy, double dz)
{
    dst.x += dx;
    dst.y += dy;
    dst.z += dz;
    return NONE;
}

int move_all_points_data(point_data &dst, double dx, double dy, double dz)
{
    for (int i = 0; i < dst.n; i++)
    {
        move_point(dst.arr[i], dx, dy, dz);
    }
    return NONE;
}
int scale_point(point &my_point, point &center, double kx, double ky, double kz)
{
    my_point.x = my_point.x + kx * (center.x - my_point.x);
    my_point.y = my_point.y + ky * (center.y - my_point.y);
    my_point.z = my_point.z + kz * (center.z - my_point.z);
    return NONE;
}
int scale_point_data(point_data &my_points, point &center, double kx, double ky, double kz)
{
    for (int i = 0; i < my_points.n; i++)
    {
        scale_point(my_points.arr[i], center, kx, ky, kz);
    }
    return NONE;
}
// TODO поворот разделить на 3 функции по каждой оси
int rotate_point(point &my_point, point &center, double ax, double ay, double az)
{
    move_point(my_point, -center.x, -center.y, -center.z);
    double x = my_point.x;
    double y = my_point.y;
    double z = my_point.z;


    my_point.y = y * std::cos(ax * PI / 180) - z * std::sin(ax * PI / 180);
    my_point.z = y * std::sin(ax * PI / 180) + z * std::cos(ax * PI / 180);

    x = my_point.x;
    y = my_point.y;
    z = my_point.z;
    my_point.x = z * std::sin(ay * PI / 180) + x * std::cos(ay * PI / 180);
    my_point.z = z * std::sin(ay * PI / 180) - x * std::sin(ay * PI / 180);

    x = my_point.x;
    y = my_point.y;
    z = my_point.z;
    my_point.x = x * std::cos(az * PI / 180) - y * std::sin(az * PI / 180);
    my_point.y = y * std::cos(az * PI / 180) + x * std::sin(az * PI / 180);
    move_point(my_point, center.x, center.y, center.z);
    return NONE;
}
int rotate_point_x(point &my_point, point &center, double ax)
{
    move_point(my_point, -center.x, -center.y, -center.z);
    my_point.y = my_point.y * std::cos(ax * PI / 180) - my_point.z * std::sin(ax * PI / 180);
    my_point.z = my_point.y * std::sin(ax * PI / 180) + my_point.z * std::cos(ax * PI / 180);
    move_point(my_point, center.x, center.y, center.z);
    return NONE;
}
int rotate_point_y(point &my_point, point &center, double ay);
int rotate_point_z(point &my_point, point &center, double az);
int rotate_point_data(point_data &my_points, point &center, double ax, double ay, double az)
{
    for (int i = 0; i < my_points.n; i++)
    {
        rotate_point(my_points.arr[i], center, ax, ay, az);
    }
    return NONE;
}