#pragma once
#include <vector>

namespace opengles_workspace 
{
    struct Shapes 
    {
        private:
            std::vector<short> _mt_coords_for_new_cube_shape = {2, 10, 2, 11, 3, 10, 3, 11};
            std::vector<short> _mt_coords_for_new_bar_shape = {2, 10, 2, 9, 2, 11, 2, 12};
            std::vector<short> _mt_coords_for_new_T_shape = {3, 10, 3, 9, 2, 10, 3, 11};
            std::vector<short> _mt_coords_for_new_L_left_shape = {2, 10, 2, 9, 3, 9, 2, 11};
            std::vector<short> _mt_coords_for_new_L_right_shape = {2, 10, 2, 11, 3, 11, 2, 9};
            std::vector<short> _mt_coords_for_new_Z_left_shape = {2, 10, 2, 9, 3, 10, 3, 11};
            std::vector<short> _mt_coords_for_new_Z_right_shape = {2, 10, 2, 11, 3, 10, 3, 9};
            
        public:
            std::vector<short> get_mt_coords_of_new_cube() const;
            std::vector<short> get_mt_coords_of_new_bar() const;
            std::vector<short> get_mt_coords_of_new_T() const;
            std::vector<short> get_mt_coords_of_new_L_left() const;
            std::vector<short> get_mt_coords_of_new_L_right() const;
            std::vector<short> get_mt_coords_of_new_Z_left() const;
            std::vector<short> get_mt_coords_of_new_Z_right() const;
    };
}