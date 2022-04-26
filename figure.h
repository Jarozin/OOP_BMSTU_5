//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_FIGURE_H
#define LAB1_FIGURE_H
#include "links.h"
#include "point.h"
#include <iostream>
#include "error_handling.h"
#define POINTS_NUM 8
#define LINKS_NUM 12
struct figure{
    point_data points;
    links_data links;
};
//ввод сначала координаты 8 вершин потом 12 ребер связи

void free_figure(figure &);
figure* alloc_figure();
int read_figure(figure &my_cube, FILE *in);
#endif //LAB1_FIGURE_H
