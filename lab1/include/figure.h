#ifndef LAB1_FIGURE_H
#define LAB1_FIGURE_H
#include "links.h"
#include "point.h"
#include <iostream>
struct figure{
    point_data points;
    links_data links;
};
//ввод сначала координаты 8 вершин потом 12 ребер связи
figure& init();
void free_figure(figure &);
int load_figure(figure &fig, FILE *in);
int load_figure_from_file(figure &, const char *filename);
#endif //LAB1_FIGURE_H
