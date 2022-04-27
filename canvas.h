//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_CANVAS_H
#define LAB1_CANVAS_H
#include "headers.h"
#include "figure.h"
#include "painter.h"
#include "transform_fig.h"
#include "task_manager.h"
class Canvas: public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();
    void paintEvent(QPaintEvent *event) override;
signals:

public slots:
    void rotate();
    void move();
    void scale();
};
#endif //LAB1_CANVAS_H
