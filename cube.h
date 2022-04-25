//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_CUBE_H
#define LAB1_CUBE_H
#include "links.h"
#include "point.h"
#include <iostream>
#include "error_handling.h"
#define N 8
struct cube{
    point vertexes[N];
    links_data links;
};
//ввод сначала координаты 8 вершин потом 12 ребер связи
int read_cube(cube &, FILE *in);
int print_cube(cube &, FILE *out);
cube *create_cube(point (&vertexes)[N]);
void free_cube(cube &);
#endif //LAB1_CUBE_H
