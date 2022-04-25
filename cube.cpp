//
// Created by jarozin on 25.04.22.
//

#include "cube.h"
Cube *create_cube(Point (&vertexes)[N])
{
    if (vertexes == nullptr)
        return nullptr;
    Cube *new_cube = new Cube;
    for (int i = 0; i < N; i++)
    {
        copy(new_cube->vertexes[i], vertexes[i]);
    }
    return new_cube;
}
void free_cube(Cube &cube)
{
    delete &cube;
}
int read_cube(Cube *, FILE *in)
{
    errors rc = NONE;
    if (in == nullptr)
        rc = EMPTY_PTR_ERR;
    if (rc == NONE)
    {

    }
    return rc;
}
int print_cube(Cube &, FILE *out);