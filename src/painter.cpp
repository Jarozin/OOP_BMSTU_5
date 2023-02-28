
//сделать точки хода с выбором в меню
#include "painter.h"
#include "headers.h"
#include "figure.h"
#include "error_handling.h"
#include "task_manager.h"
#include "graph.h"
QPointF convert_point(point &a)
{
    return QPointF(a.x + 300, a.y + 300);
}

QLineF convert_to_line(point &a, point &b)
{
    return QLineF(convert_point(a), convert_point(b));
}
int draw_figure_req(figure &fig, struct draw &dr)
{
    graphics a;
    int err = init_graph(a, dr.view);
    if (!err)
    {
        draw_links_data(fig.points, fig.links, a.scene);
        set(dr.view, a);
        dr.view->show();
    }
    return err;
}
int draw_links_data(point_data &points, links_data &links, QGraphicsScene *scene)
{
    link num;
    for (int i = 0; i < links.n; i++)
    {
        num = links.arr[i];
        scene->addLine(convert_to_line(points.arr[num.p1], points.arr[num.p2]));
    }
    return OK;
}