#pragma once
#include <iostream>
#include <vector>
#include <array>

namespace opengles_workspace 
{
    class Shapes 
    {
        private:
            std::vector<short> _mt_coords_for_new_cube_shape = {2, 10, 2, 11, 3, 10, 3, 11};
            std::vector<short> _mt_coords_for_new_bar_shape = {2, 10, 2, 9, 2, 11, 2, 12};
            std::vector<short> _mt_coords_for_new_T_shape = {3, 10, 3, 9, 2, 10, 3, 11};
            std::vector<short> _mt_coords_for_new_L_left_shape = {2, 10, 2, 9, 3, 9, 2, 11};
            std::vector<short> _mt_coords_for_new_L_right_shape = {2, 10, 2, 11, 3, 11, 2, 9};
            std::vector<short> _mt_coords_for_new_Z_left_shape = {2, 10, 2, 9, 3, 10, 3, 11};
            std::vector<short> _mt_coords_for_new_Z_right_shape = {2, 10, 2, 11, 3, 10, 3, 9};
            short _which_shape = 1;
            
        public:
            std::vector<short> get_mt_coords_of_new_cube() const;
            std::vector<short> get_mt_coords_of_new_bar() const;
            std::vector<short> get_mt_coords_of_new_T() const;
            std::vector<short> get_mt_coords_of_new_L_left() const;
            std::vector<short> get_mt_coords_of_new_L_right() const;
            std::vector<short> get_mt_coords_of_new_Z_left() const;
            std::vector<short> get_mt_coords_of_new_Z_right() const;

            void generate_new_shape(short moving_shape_mt_coords[]);
            void update_moving_shape_mt_coords(short moving_shape_mt_coords[], std::vector<short> new_coords);
            
            void rotate_bar(short mt[22][22], short moving_shape_mt_coords[8]);
            void rotate_T_shape(short mt[22][22], short moving_shape_mt_coords[8]);
            void rotate_L_left_shape(short mt[22][22], short moving_shape_mt_coords[8]);
            void rotate_L_right_shape(short mt[22][22], short moving_shape_mt_coords[8]);
            void rotate_Z_left_shape(short mt[22][22], short moving_shape_mt_coords[8]);
            void rotate_Z_right_shape(short mt[22][22], short moving_shape_mt_coords[8]);

            void rotate_shape(short mt[22][22], short moving_shape_mt_coords[]);
    };
}