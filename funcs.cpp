//
// Created by jarozin on 25.04.22.
//

// TODO ax, ay, az = point sdelat
#include "funcs.h"
#include "point_proc.h"
int rotate_cube(figure &my_cube, point &center, double ax, double ay, double az)
{
    rotate_point_data(my_cube.points, center, ax, ay, az);
}
int scale_cube(figure &my_cube, point &center, point &scale)
{
    scale_point_data(my_cube.points, center, scale);
}
int move_cube(figure &my_cube, double dx, double dy, double dz)
{
    move_all_points_data(my_cube.points, dx, dy, dz);
    return NONE;
}
