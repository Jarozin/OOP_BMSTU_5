//
// Created by jarozin on 25.04.22.
//

#include "funcs.h"
int rotate_cube(cube &);
int scale_cube(cube &, point center, double kx, double ky, double kz);
int move_cube(cube &my_cube, double dx, double dy, double dz)
{
    inc_all_points_data(my_cube.points, dx, dy, dz);
    return NONE;
}