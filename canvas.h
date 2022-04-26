//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_CANVAS_H
#define LAB1_CANVAS_H
#include "headers.h"
#define SRC_FILE "../cube.txt"
#include "figure.h"
#include "painter.h"
#include "funcs.h"
class Canvas: public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();
    void paintEvent(QPaintEvent *event) override;
    int setup_cube();
signals:

public slots:
    void rotate();
    void move();
    void scale();
private:
    figure *my_cube;
};
#endif //LAB1_CANVAS_H
