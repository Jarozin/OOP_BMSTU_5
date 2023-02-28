#include "canvas.h"
#include "headers.h"
#include "figure.h"
#include "error_handling.h"
void Canvas::rotate()
{
    errors err = OK;
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
    init_turn(req.tu, rot, center);
    req.t = TURN;
    err = (errors)task_manager(req);
    error_handling(err);

    if (!err) {
        req.t = DRAW;
        init_draw(req.dr, this);
        err = (errors) task_manager(req);
        error_handling(err);
    }
}

void Canvas::move() {
    QObject *parent = this->parent();
    errors err = OK;
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
    init_move(req.mo, m_point);
    req.t = MOVE;
    err = (errors)task_manager(req);
    error_handling(err);

    if (!err) {
        req.t = DRAW;
        init_draw(req.dr, this);
        err = (errors) task_manager(req);
        error_handling(err);
    }
}
void Canvas::scale() {
    QObject *parent = this->parent();
    errors err = OK;
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
    init_scale(req.sc, scale_data, center);
    req.t = SCALE;
    err = (errors)task_manager(req);
    error_handling(err);

    if (!err) {
        req.t = DRAW;
        init_draw(req.dr, this);
        err = (errors) task_manager(req);
        error_handling(err);
    }
}

Canvas::Canvas(QWidget *parent) : QGraphicsView(parent)
{
}

Canvas::~Canvas() {
}