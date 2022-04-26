//
// Created by jarozin on 25.04.22.
//

#include "figure.h"
#include "links.h"
#include "point.h"
#include <iostream>
#include "error_handling.h"
#include "io.h"
void free_figure(figure &src)
{
    free_point_data(src.points);
    free_links_data(src.links);
    free(&src);
}
int alloc_figure(figure &new_fig)
{
    int err = NONE;
    err = alloc_point_data_n(new_fig.points, POINTS_NUM);
    if (!err) {
        err = links_alloc(new_fig.links, LINKS_AMOUNT);
    }
    return err;
}
// TODO количества надо вводить
int read_figure(figure &my_cube, FILE *in)
{
    int err = NONE;
    int n;
    err = read_amount(&n, in);
    if (!err)
    {
        err = read_point_data_n(my_cube.points, n, in);
        if (!err)
        {
            err = read_amount(&n, in);
            if (!err)
            {
                err = read_link_data(my_cube.links, in);
            }
        }
    }
    return err;
}