//
// Created by jarozin on 25.04.22.
//

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

int links_alloc(links_data &connections, int len);
void links_free(links_data &connections);
int read_link(link* joints, FILE* f);
void free_links_data(links_data &src);
int read_link_data(links_data &dst, FILE *f);
int appoint_and_read_link_data(links_data &links, FILE *in);
#endif
