//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_FUNCS_H
#define LAB1_FUNCS_H
#include "cube.h"
#include "canvas.h"
int rotate_cube(cube &);
int scale_cube(cube &, point& center, double kx, double ky, double kz);
int move_cube(cube &, double dx, double dy, double dz);
#endif //LAB1_FUNCS_H
