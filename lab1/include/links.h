#ifndef LAB1_LINKS_H
#define LAB1_LINKS_H
//структура хранящая связи точек в кубе
#include "point.h"

struct link
{
    int p1;
    int p2;
};

struct links_data
{
    int n;
    link *arr;
};

int alloc_links(links_data &connections, int len);
int read_link(link &, FILE* f);
void free_links(links_data &src);
int read_links(links_data &dst, FILE *f);
int load_links(links_data &links, FILE *in);
#endif
