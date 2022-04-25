//
// Created by jarozin on 25.04.22.
//

#include "cube.h"
void free_cube(cube &src)
{
    free_point_data(src.points);
    free_links_data(src.links);
    delete &src;
}
cube* alloc_cube()
{
    point_data *new_points = alloc_point_data_n(POINTS_NUM);
    links_data *new_links = alloc_link_data(LINKS_AMOUNT);
    cube *new_cube = new cube;
    if (new_cube == nullptr || new_links == nullptr || new_points == nullptr)
    {
        free_links_data(*new_links);
        free_point_data(*new_points);
        delete new_cube;
        new_cube = nullptr;
    }
    else
    {
        new_cube->points = *new_points;
        new_cube->links = *new_links;
    }
    return new_cube;
}
int read_cube(cube &my_cube, FILE *in)
{
    int err = NONE;
    err = read_point_data_n(my_cube.points, POINTS_NUM, in);
    if (!err)
    {
        err = read_n_links(my_cube.links.arr, my_cube.links.n, in);
    }
    return err;
}