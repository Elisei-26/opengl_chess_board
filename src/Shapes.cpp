#include "../include/Shapes.hpp"

namespace opengles_workspace 
{
    Shapes::Shapes() 
    {
        mt_coords_for_new_cube_shape = {2, 10, 2, 11, 3, 10, 3, 11};
        mt_coords_for_new_bar_shape = {2, 10, 2, 9, 2, 11, 2, 12};
        mt_coords_for_new_T_shape = {3, 10, 3, 9, 2, 10, 3, 11};
        mt_coords_for_new_L_left_shape = {2, 10, 2, 9, 3, 9, 2, 11};
        mt_coords_for_new_L_right_shape = {2, 10, 2, 11, 3, 11, 2, 9};
        mt_coords_for_new_Z_left_shape = {2, 10, 2, 9, 3, 10, 3, 11};
        mt_coords_for_new_Z_right_shape = {2, 10, 2, 11, 3, 10, 3, 9};
    }

    std::vector<short> Shapes::get_mt_coords_of_new_cube() 
    {
        return this->mt_coords_for_new_cube_shape;
    }

    std::vector<short> Shapes::get_mt_coords_of_new_bar() 
    {
        return this->mt_coords_for_new_bar_shape;
    }

    std::vector<short> Shapes::get_mt_coords_of_new_T() 
    {
        return this->mt_coords_for_new_T_shape;
    }

    std::vector<short> Shapes::get_mt_coords_of_new_L_left() 
    {
        return this->mt_coords_for_new_L_left_shape;
    }

    std::vector<short> Shapes::get_mt_coords_of_new_L_right() 
    {
        return this->mt_coords_for_new_L_right_shape;
    }

    std::vector<short> Shapes::get_mt_coords_of_new_Z_left() 
    {
        return this->mt_coords_for_new_Z_left_shape;
    }

    std::vector<short> Shapes::get_mt_coords_of_new_Z_right() 
    {
        return this->mt_coords_for_new_Z_right_shape;
    }
}
