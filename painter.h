//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_PAINTER_H
#define LAB1_PAINTER_H
#include "headers.h"
#include "figure.h"
#include "task_manager.h"
QPointF convert_point(point &a);
int draw_figure_req(figure &fig, struct draw &dr);
int draw_links_data(point_data &points, links_data &links, QGraphicsScene *scene);
#endif //LAB1_PAINTER_H
