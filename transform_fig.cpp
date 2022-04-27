//
// Created by jarozin on 25.04.22.
//

#include "transform_fig.h"
#include "point_proc.h"
#include "error_handling.h"
#include "task_manager.h"
int rotate_figure_req(figure &my_cube, struct turn rot)
{
    rotate_point_data(my_cube.points, rot.center, rot.rot_point);
    return NONE;
}
int scale_figure_req(figure &my_cube, struct scale sc)
{
    scale_point_data(my_cube.points, sc.center, sc.k_point);
    return NONE;
}
int move_figure_req(figure &my_cube, struct move mo)
{
    move_all_points_data(my_cube.points, mo.d_point);
    return NONE;
}
