//
// Created by jarozin on 25.04.22.
//
#include "headers.h"
#ifndef LAB1_CANVAS_H
#define LAB1_CANVAS_H
class Canvas: public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

signals:

public slots:
    void rotate();
    void move();
    void scale();
};
#endif //LAB1_CANVAS_H
