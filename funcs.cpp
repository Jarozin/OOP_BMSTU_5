//
// Created by jarozin on 25.04.22.
//

#include "funcs.h"
#include "point_proc.h"
#include "error_handling.h"
int rotate_cube(figure &my_cube, point &center, point &rot)
{
    rotate_point_data(my_cube.points, center, rot);
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
