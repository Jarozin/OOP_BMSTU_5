#include "error_handling.h"
#include "links.h"
#include "io.h"
int alloc_links(links_data &connections, int len)
{
    int err = OK;
    connections.n = len;
    connections.arr = (link *)malloc(sizeof(link) * len);
    if (!connections.arr)
        err = EMPTY_PTR_ERR;

    return err;
}


void free_links(links_data &src)
{
    if (!src.arr)
        free(src.arr);

}
int read_link(link &dst, FILE* f)
{
    int err = OK;
    if (f == nullptr)
        err = EMPTY_PTR_ERR;
    if (!err)
    {
        if (fscanf(f, "%d%d", &dst.p1, &dst.p2) != 2)
            err = FILE_FORMAT_ERR;
    }
    return err;
}


int read_links(links_data &dst, FILE *f)
{
    int err = 0;
    if (dst.n < 1)
        err = NO_LINKS;
    for (int i = 0; !err && i < dst.n; i++)
    {
        err = read_link(dst.arr[i], f);
    }
    return err;
}

int load_links(links_data &links, FILE *in)
{
    int n = 0;
    int err = OK;
    err = read_amount(&n, in);
    if (!err) {
        err = alloc_links(links, n);
        if (!err)
        {
            err = read_links(links, in);
            if (err)
                free_links(links);
        }
    }
    return err;
}