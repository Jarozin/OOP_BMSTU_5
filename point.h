//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_POINT_H
#define LAB1_POINT_H

#endif //LAB1_POINT_H
struct Point{
    int x;
    int y;
    int z;
};

Point* create_point(int x, int y, int z);
void delete_point(Point *point);
void copy(Point &dst, Point src);