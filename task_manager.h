//
// Created by jarozin on 26.04.22.
//

#ifndef LAB1_TASK_MANAGER_H
#define LAB1_TASK_MANAGER_H
#include "error_handling.h"
#include "figure.h"
#include "canvas.h"
#include "headers.h"
#include "QObject"
enum task
{
    INIT,
    LOAD_FILE,
    MOVE,
    SCALE,
    TURN,
    DRAW,
    QUIT
};
struct move{
    point d_point;
};
int init_move(move &mv, point &d_point);
struct scale{
    point k_point;
    point center;
};
int init_scale(scale &sc, point &k_point, point &center);
struct turn{
    point rot_point;
    point center;
};
int init_turn(turn &tr, point &rot_point, point &center);
struct draw{
    QPainter *painter;
};
int init_draw(draw &dr, QPainter *);
struct request
{
    task t;
    const char* filename = "../cube.txt";
    union
    {
        struct move mo;
        struct scale sc;
        struct turn tu;
        struct draw dr;
    };
};

int task_manager(request args);
#endif //LAB1_TASK_MANAGER_H
