//
// Created by jarozin on 25.04.22.
//

#include "point.h"
Point* create_point(double x, double y, double z)
{
    Point *newPoint = new Point;
    newPoint->x = x;
    newPoint->y = y;
    newPoint->z = z;
    return newPoint;
}

void delete_point(Point &point)
{
    delete &point;
}
void copy(Point &dst, Point src)
{
    dst.x = src.x;
    dst.y = src.y;
    dst.z = src.z;
}