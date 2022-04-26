//
// Created by jarozin on 26.04.22.
//
#include "painter.h"
#include "task_manager.h"
#include "transform_fig.h"
#include "canvas.h"
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
        case QUIT:
            free_figure(fig);
            break;
        default:
            err = UNKNOWN_COMMAND;
    }

    return err;
}
