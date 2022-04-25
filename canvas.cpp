//
// Created by jarozin on 25.04.22.
//
#include "canvas.h"

void Canvas::rotate()
{
    QObject *parent = this->parent();


}

void Canvas::move() {
    QObject *parent = this->parent();
    double dx, dy, dz;
    QLineEdit *line = parent->findChild<QLineEdit *>("dx");
    dx = line->text().toDouble();
    line = parent->findChild<QLineEdit *>("dy");
    dy = line->text().toDouble();
    line = parent->findChild<QLineEdit *>("dz");
    dz = line->text().toDouble();
    move_cube(*this->my_cube, dx, dy, dz);
    this->update();
}

void Canvas::scale() {
    QObject *parent = this->parent();
    double kx, ky, kz;
    QLineEdit *line = parent->findChild<QLineEdit *>("kx");
    kx = line->text().toDouble();
    line = parent->findChild<QLineEdit *>("ky");
    ky = line->text().toDouble();
    line = parent->findChild<QLineEdit *>("kz");
    kz = line->text().toDouble();
    double cx, cy, cz;
    line = parent->findChild<QLineEdit *>("cx");
    cx = line->text().toDouble();
    line = parent->findChild<QLineEdit *>("cy");
    cy = line->text().toDouble();
    line = parent->findChild<QLineEdit *>("cz");
    cz = line->text().toDouble();
    point *center = create_point(cx, cy, cz);
    scale_cube(*this->my_cube, *center, kx, ky, kz);
    free_point(*center);
    this->update();
}

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    int err = NONE;
    this->filename = SRC_FILE;
    err = this->setup_cube();
}

Canvas::~Canvas() {
    free_cube(*this->my_cube);
    //delete &this->my_cube;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setPen(Qt::black);
    draw_cube(*this->my_cube, painter);
   // painter.setFont(QFont("Arial", 30));
    //painter.drawText(rect(), Qt::AlignCenter, "Qt");
}

int Canvas::setup_cube() {
    int err = NONE;
    FILE *in = fopen(this->filename.c_str(), "r");
    cube *new_cube = nullptr;
    new_cube = alloc_cube();
    if (new_cube != nullptr)
    {
        this->my_cube = new_cube;
        err = read_cube(*this->my_cube, in);
    }
    else
    {
        err = EMPTY_PTR_ERR;
    }
    error_handling(static_cast<errors>(err));
    fclose(in);
    return err;
}
