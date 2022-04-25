//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_CUBE_H
#define LAB1_CUBE_H
#include "links.h"
#include "point.h"
#include <iostream>
#include "error_handling.h"
#define POINTS_NUM 8
#define LINKS_NUM 12
struct cube{
    point_data points;
    links_data links;
};
//ввод сначала координаты 8 вершин потом 12 ребер связи

void free_cube(cube &);
cube* alloc_cube();
int read_cube(cube &);
#endif //LAB1_CUBE_H
