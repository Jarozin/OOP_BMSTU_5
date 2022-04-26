//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_FIGURE_H
#define LAB1_FIGURE_H
#include "links.h"
#include "point.h"
#include <iostream>
#define POINTS_NUM 8
#define LINKS_NUM 12
struct figure{
    point_data points;
    links_data links;
};
//ввод сначала координаты 8 вершин потом 12 ребер связи
figure& init();
void free_figure(figure &);
int alloc_figure(figure &new_fig);
int read_figure(figure &my_cube, FILE *in);
int create_and_read_figure(figure &my_fig, FILE *in);
int load_figure_from_file(figure &, const char *filename);
#endif //LAB1_FIGURE_H
