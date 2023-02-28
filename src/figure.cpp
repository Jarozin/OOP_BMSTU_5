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
    free_points(src.points);
    free_links(src.links);
}

int read_figure(figure &fig, FILE *in)
{
    int err = OK;
    int n;
    err = load_points(fig.points, in);
    if (!err)
    {
        err = load_links(fig.links, in);
        if (err)
            free_points(fig.points);
    }
    return err;
}
int load_figure_from_file(figure &fig, const char *filename)
{
    int err = OK;
    figure new_fig;
    FILE *in = fopen(filename, "r");
    if (in) {
        err = read_figure(new_fig, in);
        fclose(in);
    }
    else
        err = FILE_NOT_FOUND;
    if (!err)
    {
        free_figure(fig);
        fig = new_fig;
    }
    return err;
}