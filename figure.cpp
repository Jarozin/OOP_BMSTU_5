//
// Created by jarozin on 25.04.22.
//

#include "figure.h"
#include "links.h"
#include "point.h"
#include <iostream>
#include "error_handling.h"
void free_figure(figure &src)
{
    free_point_data(src.points);
    free_links_data(src.links);
    free(&src);
}
figure* alloc_figure()
{
    point_data *new_points = alloc_point_data_n(POINTS_NUM);
    links_data *new_links = alloc_link_data(LINKS_AMOUNT);
    figure *new_cube = (figure *)malloc(sizeof(figure));
    if (new_cube == nullptr || new_links == nullptr || new_points == nullptr)
    {
        free_links_data(*new_links);
        free_point_data(*new_points);
        free(new_cube);
        new_cube = nullptr;
    }
    else
    {
        new_cube->points = *new_points;
        new_cube->links = *new_links;
    }
    return new_cube;
}
// TODO количества надо вводить
int read_figure(figure &my_cube, FILE *in)
{
    int err = NONE;
    err = read_point_data_n(my_cube.points, POINTS_NUM, in);
    if (!err)
    {
        err = read_link_data(my_cube.links, in);
    }
    return err;
}