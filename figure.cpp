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

int create_and_read_figure(figure &my_fig, FILE *in)
{
    int err = OK;
    int n;
    err = alloc_and_read_point_data(my_fig.points, in);
    if (!err)
    {
        err = appoint_and_read_link_data(my_fig.links, in);
        if (err)
        {
            free_point_data(my_fig.points);
        }
    }
    return err;
}
int load_figure_from_file(figure &new_figure, const char *filename)
{
    int err = OK;
    FILE *in = fopen(filename, "r");
    if (in) {
        err = create_and_read_figure(new_figure, in);
        fclose(in);
    }
    else
        err = FILE_NOT_FOUND;
    return err;
}