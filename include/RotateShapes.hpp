#pragma once

namespace opengles_workspace 
{ 
    class RotateShapes 
    {
        public:
            void rotate_bar(short mt[22][22], short moving_shape_mt_coords[8]);
            void rotate_T_shape(short mt[22][22], short moving_shape_mt_coords[8]);
            void rotate_L_left_shape(short mt[22][22], short moving_shape_mt_coords[8]);
            void rotate_L_right_shape(short mt[22][22], short moving_shape_mt_coords[8]);
            void rotate_Z_left_shape(short mt[22][22], short moving_shape_mt_coords[8]);
            void rotate_Z_right_shape(short mt[22][22], short moving_shape_mt_coords[8]);
    };
}