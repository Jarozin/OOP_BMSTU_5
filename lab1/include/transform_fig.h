#ifndef LAB1_TRANSFORM_FIG_H
#define LAB1_TRANSFORM_FIG_H
#include "figure.h"
#include "task_manager.h"
int move_figure_req(figure &my_cube, struct move mo);
int scale_figure_req(figure &my_cube, struct scale sc);
int rotate_figure_req(figure &my_cube, struct turn rot);
#endif //LAB1_TRANSFORM_FIG_H
