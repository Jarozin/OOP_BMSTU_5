#include "painter.h"
#include "task_manager.h"
#include "transform_fig.h"
int task_manager(request req)
{
    static figure fig = init();
    int  err = 0;
    switch (req.t)
    {
        case INIT:
            break;
        case LOAD_FILE:
            err = load_figure_from_file(fig, req.filename);
            break;
        case MOVE:
            err = move_figure_req(fig, req.mo);
            break;
        case SCALE:
            err = scale_figure_req(fig, req.sc);
            break;
        case TURN:
            err = rotate_figure_req(fig, req.tu);
            break;
        case DRAW:
            err = draw_figure_req(fig, req.dr);
            break;
        case QUIT:
            free_figure(fig);
            break;
        default:
            err = UNKNOWN_COMMAND;
    }

    return err;
}
int init_move(move &mv, point &d_point)
{
    mv.d_point = d_point;
    return OK;
}

int init_scale(scale &sc, point &k_point, point &center) {
    sc.center = center;
    sc.k_point = k_point;
    return OK;
}

int init_turn(turn &tr, point &rot_point, point &center) {
    tr.center = center;
    tr.rot_point = rot_point;
    return OK;
}
int init_draw(draw &dr, QGraphicsView *view)
{
    dr.view = view;
    return OK;
}