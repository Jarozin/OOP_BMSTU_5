//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_CUBE_H
#define LAB1_CUBE_H
#include "point.h"
#include <iostream>
#include "error_handling.h"
#define N 8
struct Cube{
    Point vertexes[N];
};
//ввод сначала координаты 8 вершин потом 12 ребер связи
int read_cube(Cube &, FILE *in);
int print_cube(Cube &, FILE *out);
Cube *create_cube(Point (&vertexes)[N]);
void free_cube(Cube &);
#endif //LAB1_CUBE_H
