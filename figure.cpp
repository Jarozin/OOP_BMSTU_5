//
// Created by jarozin on 25.04.22.
//

#include "figure.h"
#include "links.h"
#include "point.h"
#include "error_handling.h"
#include "io.h"
figure& init()
{
    static figure fig;

    fig.points.n = 0;
    fig.points.arr = NULL;

    fig.links.n = 0;
    fig.links.arr = NULL;

    return fig;
}
void free_figure(figure &src)
{
    free_point_data(src.points);
    free_links_data(src.links);
}
int alloc_figure(figure &new_fig, int points_len, int links_len)
{
    int err = NONE;
    err = alloc_point_data_n(new_fig.points,  points_len);
    if (!err) {
        err = links_alloc(new_fig.links, links_len);
    }
    return err;
}

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
int create_and_read_figure(figure &my_fig, FILE *in)
{
    int err = NONE;
    int n;
    err = read_amount(&n, in);
    if (!err)
    {
        err = alloc_point_data_n(my_fig.points, n);
        if (!err) {
            err = read_point_data_n(my_fig.points, n, in);
            if (!err) {
                err = read_amount(&n, in);
                if (!err) {
                    err = links_alloc(my_fig.links, n);
                    if (!err)
                        err = read_link_data(my_fig.links, in);
                }
            }
        }
    }
    return err;
}
int load_figure_from_file(figure &new_figure, const char *filename)
{
    int err = NONE;
    FILE *in = fopen(filename, "r");
    if (in) {
        err = create_and_read_figure(new_figure, in);
        fclose(in);
    }
    else
        err = FILE_NOT_FOUND;
    return err;
}