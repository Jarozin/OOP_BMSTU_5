//
// Created by jarozin on 25.04.22.
//

#include "cube.h"
cube *create_cube(point (&vertexes)[N])
{
    if (vertexes == nullptr)
        return nullptr;
    cube *new_cube = new cube;
    for (int i = 0; i < N; i++)
    {
        copy(new_cube->vertexes[i], vertexes[i]);
    }
    return new_cube;
}
void free_cube(cube &cube)
{
    delete &cube;
}
int read_cube(cube *, FILE *in)
{
    errors rc = NONE;
    if (in == nullptr)
        rc = EMPTY_PTR_ERR;
    if (rc == NONE)
    {

    }
    return rc;
}
int print_cube(cube &, FILE *out);