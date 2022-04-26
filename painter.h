//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_PAINTER_H
#define LAB1_PAINTER_H
#include "headers.h"
#include "figure.h"
#include "task_manager.h"
QPointF convert_point(point &a);
int draw_figure(figure &my_cube, QPainter &qp);
int draw_point(point &a, QPainter &qp);
int draw_point_data(point_data &a, QPainter &qp);
int draw_links_data(point_data &points, links_data &links, QPainter &qp);
#endif //LAB1_PAINTER_H
