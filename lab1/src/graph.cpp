#include "graph.h"
#include "error_handling.h"

int init_graph(graphics &a, QGraphicsView *gV)
{
    a.scene = new QGraphicsScene(gV);
    if (!a.scene)
        return EMPTY_PTR_ERR;

    a.pen = QPen(Qt::black);

    return OK;
}

void del(graphics &a)
{
    delete a.scene;
}

void set(QGraphicsView *gV, graphics &a)
{
    QGraphicsScene *prev = gV->scene();
    delete prev;
    gV->setScene(a.scene);
}