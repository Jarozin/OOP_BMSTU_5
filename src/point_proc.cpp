#include "point_proc.h"
#include <math.h>
#include "error_handling.h"
#include "point.h"
#define _USE_MATH_DEFINES
int add_point(point &dst, point &d_point)
{
    dst.x += d_point.x;
    dst.y += d_point.y;
    dst.z += d_point.z;
    return OK;
}

int sub_point(point &dst, point &d_point)
{
    dst.x -= d_point.x;
    dst.y -= d_point.y;
    dst.z -= d_point.z;
    return OK;
}

int move_all_points_data(point_data &dst, point &d_point)
{
    for (int i = 0; i < dst.n; i++)
    {
        add_point(dst.arr[i], d_point);
    }
    return OK;
}
int scale_point(point &my_point, point &center, point &scale)
{
    my_point.x = center.x + scale.x * (my_point.x - center.x);
    my_point.y = center.y + scale.y * (my_point.y - center.y);
    my_point.z = center.z + scale.z * (my_point.z - center.z);
    return OK;
}
int scale_point_data(point_data &my_points, point &center, point &scale)
{
    for (int i = 0; i < my_points.n; i++)
    {
        scale_point(my_points.arr[i], center, scale);
    }
    return OK;
}

int rotate_point(point &my_point, point &center, point &rot)
{
    sub_point(my_point, center);

    rotate_point_x(my_point, center, rot.x);
    rotate_point_y(my_point, center, rot.y);
    rotate_point_z(my_point, center, rot.z);

    add_point(my_point, center);
    return OK;
}
int rotate_point_x(point &my_point, point &center, double ax)
{
    double buf = my_point.y;
    my_point.y = my_point.y * cos(to_rad(ax)) - my_point.z * sin(to_rad(ax));
    my_point.z = buf * sin(to_rad(ax)) + my_point.z * cos(to_rad(ax));
    return OK;
}
int rotate_point_y(point &my_point, point &center, double ay)
{
    double buf = my_point.x;
    my_point.x = my_point.z * sin(to_rad(ay)) + my_point.x * cos(to_rad(ay));
    my_point.z = my_point.z * cos(to_rad(ay)) - buf * sin(to_rad(ay));
    return OK;
}
int rotate_point_z(point &my_point, point &center, double az)
{
    double buf = my_point.x;
    my_point.x = my_point.x * cos(to_rad(az)) - my_point.y * sin(to_rad(az));
    my_point.y = my_point.y * cos(to_rad(az)) + buf * sin(to_rad(az));
    return OK;
}
int rotate_point_data(point_data &my_points, point &center, point &rot)
{
    for (int i = 0; i < my_points.n; i++)
    {
        rotate_point(my_points.arr[i], center, rot);
    }
    return OK;
}
double to_rad(double ax)
{
    return ax * M_PI / 180;
}

