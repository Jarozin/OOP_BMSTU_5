//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_LINKS_H
#define LAB1_LINKS_H
#define LINKS_AMOUNT 12
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

int links_alloc(links_data &connections, int len);
void links_free(links_data &connections);
int read_link(link* joints, FILE* f);
void free_links_data(links_data &src);
int read_link_data(links_data &dst, FILE *f);
#endif
