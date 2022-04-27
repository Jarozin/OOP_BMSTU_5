//
// Created by jarozin on 25.04.22.
//
#include "canvas.h"
#include "headers.h"
#include "figure.h"
#include "error_handling.h"
void Canvas::rotate()
{
    errors err = NONE;
    QObject *parent = this->parent();
    double ax, ay, az;
    QLineEdit *line = parent->findChild<QLineEdit *>("ax");
    ax = line->text().toDouble();
    line = parent->findChild<QLineEdit *>("ay");
    ay = line->text().toDouble();
    line = parent->findChild<QLineEdit *>("az");
    az = line->text().toDouble();

    double cx, cy, cz;
    line = parent->findChild<QLineEdit *>("cx");
    cx = line->text().toDouble();
    line = parent->findChild<QLineEdit *>("cy");
    cy = line->text().toDouble();
    line = parent->findChild<QLineEdit *>("cz");
    cz = line->text().toDouble();
    point center;
    create_point(center, cx, cy ,cz);
    point rot;
    create_point(rot, ax, ay, az);

    request req;
    req.tu.rot_point = rot;
    req.tu.center = center;
    req.t = TURN;
    err = (errors)task_manager(req);
    error_handling(err);

    this->update();
}

void Canvas::move() {
    QObject *parent = this->parent();
    errors err = NONE;
    double dx, dy, dz;
    QLineEdit *line = parent->findChild<QLineEdit *>("dx");
    dx = line->text().toDouble();
    line = parent->findChild<QLineEdit *>("dy");
    dy = line->text().toDouble();
    line = parent->findChild<QLineEdit *>("dz");
    dz = line->text().toDouble();
    point m_point;
    create_point(m_point, dx, dy, dz);

    request req;
    req.mo.d_point = m_point;
    req.t = MOVE;
    err = (errors)task_manager(req);
    error_handling(err);
    this->update();
}
// TODO этот код скорее всего стоит сократить
void Canvas::scale() {
    QObject *parent = this->parent();
    errors err = NONE;
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
    point center;
    create_point(center, cx, cy, cz);
    point scale_data;
    create_point(scale_data, kx, ky, kz);

    request req;
    req.sc.k_point = scale_data;
    req.sc.center = center;
    req.t = SCALE;
    err = (errors)task_manager(req);
    error_handling(err);
    this->update();
}

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    int err = NONE;
    request req;
    req.t = INIT;
    err = task_manager(req);
    if (!err)
    {
        req.t = LOAD_FILE;
        err = task_manager(req);
    }
    if (err)
    {
        error_handling((errors)err);
    }
    this->update();
}

Canvas::~Canvas() {
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    request req;
    req.dr.painter = &painter;
    painter.setPen(Qt::black);
    req.t = DRAW;
    errors err = NONE;
    err = (errors)task_manager(req);
    error_handling(err);
}