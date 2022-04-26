//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_FUNCS_H
#define LAB1_FUNCS_H
#include "figure.h"
int rotate_cube(figure &my_cube, point &center, point &rot);
int scale_cube(figure &my_cube, point &center, point &scale);
int move_cube(figure &, double dx, double dy, double dz);
#endif //LAB1_FUNCS_H
