//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_POINT_H
#define LAB1_POINT_H

#endif //LAB1_POINT_H
struct Point{
    double x;
    double y;
    double z;
};

Point* create_point(double x, double y, double z);
void delete_point(Point *point);
void copy(Point &dst, Point src);