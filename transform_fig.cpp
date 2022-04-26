//
// Created by jarozin on 25.04.22.
//

#include "transform_fig.h"
#include "point_proc.h"
#include "error_handling.h"
#include "task_manager.h"
int rotate_figure(figure &my_cube, point &center, point &rot)
{
    rotate_point_data(my_cube.points, center, rot);
    return NONE;
}
int scale_figure(figure &my_cube, point &center, point &scale)
{
    scale_point_data(my_cube.points, center, scale);
    return NONE;
}
int move_figure(figure &my_cube, point &d_point)
{
    move_all_points_data(my_cube.points, d_point);
    return NONE;
}
int rotate_figure_req(figure &my_cube, turn rot)
{
    rotate_point_data(my_cube.points, rot.center, rot.rot_point);
    return NONE;
}
int scale_figure_req(figure &my_cube, scale sc)
{
    scale_point_data(my_cube.points, sc.center, sc.k_point);
    return NONE;
}
int move_figure_req(figure &my_cube, move mo)
{
    move_all_points_data(my_cube.points, mo.d_point);
    return NONE;
}
