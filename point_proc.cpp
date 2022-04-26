//
// Created by jarozin on 26.04.22.
//

#include "point_proc.h"
#include <math.h>
#include "error_handling.h"
#include "point.h"
#define _USE_MATH_DEFINES
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
int scale_point(point &my_point, point &center, point &scale)
{
    my_point.x = center.x + scale.x * (my_point.x - center.x);
    my_point.y = center.y + scale.y * (my_point.y - center.y);
    my_point.z = center.z + scale.z * (my_point.z - center.z);
    return NONE;
}
int scale_point_data(point_data &my_points, point &center, point &scale)
{
    for (int i = 0; i < my_points.n; i++)
    {
        scale_point(my_points.arr[i], center, scale);
    }
    return NONE;
}
// TODO поворот разделить на 3 функции по каждой оси
int rotate_point(point &my_point, point &center, point &rot)
{
    move_point(my_point, -center.x, -center.y, -center.z);

    rotate_point_x(my_point, center, rot.x);
    rotate_point_y(my_point, center, rot.y);
    rotate_point_z(my_point, center, rot.z);

    move_point(my_point, center.x, center.y, center.z);
    return NONE;
}
int rotate_point_x(point &my_point, point &center, double ax)
{
    double buf = my_point.y;
    my_point.y = my_point.y * cos(to_rad(ax)) - my_point.z * sin(to_rad(ax));
    my_point.z = buf * sin(to_rad(ax)) + my_point.z * cos(to_rad(ax));
    return NONE;
}
int rotate_point_y(point &my_point, point &center, double ay)
{
    double buf = my_point.x;
    my_point.x = my_point.z * sin(to_rad(ay)) + my_point.x * cos(to_rad(ay));
    my_point.z = my_point.z * sin(to_rad(ay)) - buf * sin(to_rad(ay));
    return NONE;
}
int rotate_point_z(point &my_point, point &center, double az)
{
    double buf = my_point.x;
    my_point.x = my_point.z * sin(to_rad(az)) + my_point.x * cos(to_rad(az));
    my_point.z = my_point.z * sin(to_rad(az)) - buf * sin(to_rad(az));
    return NONE;
}
int rotate_point_data(point_data &my_points, point &center, point &rot)
{
    for (int i = 0; i < my_points.n; i++)
    {
        rotate_point(my_points.arr[i], center, rot);
    }
    return NONE;
}
double to_rad(double ax)
{
    return ax * M_PI / 180;
}