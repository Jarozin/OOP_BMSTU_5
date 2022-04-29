//
// Created by jarozin on 25.04.22.
//
#include "error_handling.h"
#include "links.h"
int links_alloc(links_data &connections, int len)
{
    connections.n = len;

    connections.arr = (link *)malloc(sizeof(link) * len);
    if (!connections.arr)
        return EMPTY_PTR_ERR;

    return OK;
}

void links_free(links_data &connections)
{
    if (connections.arr)
        free(connections.arr);
}

void free_links_data(links_data &src)
{
    links_free(src);
}


int read_link(link* joints, FILE* f)
{
    if (fscanf(f, "%d%d", &joints->p1, &joints->p2) != 2)
        return FILE_FORMAT_ERR;

    return OK;
}


int read_link_data(links_data &dst, FILE *f)
{
    int err = 0;
    for (int i = 0; !err && i < dst.n; i++)
    {
        if (read_link(&dst.arr[i], f))
            err = FILE_FORMAT_ERR;
    }
    return err;
}