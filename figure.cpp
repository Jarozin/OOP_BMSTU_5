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
    delete &src;
}
figure* alloc_figure()
{
    point_data *new_points = alloc_point_data_n(POINTS_NUM);
    links_data *new_links = alloc_link_data(LINKS_AMOUNT);
    figure *new_cube = new figure;
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
// TODO количества надо вводить
int read_figure(figure &my_cube, FILE *in)
{
    int err = NONE;
    err = read_point_data_n(my_cube.points, POINTS_NUM, in);
    if (!err)
    {
        // TODO нужно будет не передавать по два аргумента, а просто саму структуру
        err = read_n_links(my_cube.links.arr, my_cube.links.n, in);
    }
    return err;
}