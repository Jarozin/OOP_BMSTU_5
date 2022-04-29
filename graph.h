//
// Created by jarozin on 30.04.22.
//

#ifndef LAB1_GRAPH_H
#define LAB1_GRAPH_H
#include "QGraphicsView"

struct graphics
{
    QGraphicsScene *scene;
    QPen pen;
};

int init_graph(graphics &a, QGraphicsView *gV);
void del(graphics &a);
void set(QGraphicsView *gV, graphics &a);
#endif //LAB1_GRAPH_H
