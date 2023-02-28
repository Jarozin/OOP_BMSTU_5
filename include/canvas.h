#ifndef LAB1_CANVAS_H
#define LAB1_CANVAS_H
#include "headers.h"
#include "figure.h"
#include "painter.h"
#include "transform_fig.h"
#include "task_manager.h"
class Canvas: public QGraphicsView
{
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
