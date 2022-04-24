//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_CUBE_H
#define LAB1_CUBE_H
#include "point.h"
#define N 8
struct Cube{
    Point vertexes[N];
};

Cube *create_cube(Point (&vertexes)[N]);
void free_cube(Cube &);
#endif //LAB1_CUBE_H
