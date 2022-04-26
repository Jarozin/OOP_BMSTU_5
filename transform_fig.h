//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_TRANSFORM_FIG_H
#define LAB1_TRANSFORM_FIG_H
#include "figure.h"
#include "task_manager.h"
int rotate_figure(figure &my_cube, point &center, point &rot);
int scale_figure(figure &my_cube, point &center, point &scale);
int move_figure(figure &my_cube, point &d_point);
int move_figure_req(figure &my_cube, move mo);
int scale_figure_req(figure &my_cube, scale sc);
int rotate_figure_req(figure &my_cube, turn rot);
#endif //LAB1_TRANSFORM_FIG_H
