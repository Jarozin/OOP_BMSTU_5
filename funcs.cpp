//
// Created by jarozin on 25.04.22.
//

// TODO ax, ay, az = point sdelat
#include "funcs.h"
int rotate_cube(cube &my_cube, point &center, double ax, double ay, double az)
{
    rotate_point_data(my_cube.points, center, ax, ay, az);
}
int scale_cube(cube &my_cube, point &center, double kx, double ky, double kz)
{
    scale_point_data(my_cube.points, center, kx, ky, kz);
}
int move_cube(cube &my_cube, double dx, double dy, double dz)
{
    move_all_points_data(my_cube.points, dx, dy, dz);
    return NONE;
}
