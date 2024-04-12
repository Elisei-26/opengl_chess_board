#pragma once
#include <iostream>
#include <vector>

namespace opengles_workspace 
{
    class Shapes 
    {
        private:
            std::vector<short> mt_coords_for_new_cube_shape;
            std::vector<short> mt_coords_for_new_bar_shape;
            std::vector<short> mt_coords_for_new_T_shape;
            std::vector<short> mt_coords_for_new_L_left_shape;
            std::vector<short> mt_coords_for_new_L_right_shape;
            std::vector<short> mt_coords_for_new_Z_left_shape;
            std::vector<short> mt_coords_for_new_Z_right_shape;
            
        public:
            Shapes();
            std::vector<short> get_mt_coords_of_new_cube();
            std::vector<short> get_mt_coords_of_new_bar();
            std::vector<short> get_mt_coords_of_new_T();
            std::vector<short> get_mt_coords_of_new_L_left();
            std::vector<short> get_mt_coords_of_new_L_right();
            std::vector<short> get_mt_coords_of_new_Z_left();
            std::vector<short> get_mt_coords_of_new_Z_right();
    };
}