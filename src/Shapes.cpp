#include "../include/Shapes.hpp"

namespace opengles_workspace 
{
    const std::vector<short> Shapes::get_mt_coords_of_new_cube() 
    {
        return this->_mt_coords_for_new_cube_shape;
    }

    const std::vector<short> Shapes::get_mt_coords_of_new_bar() 
    {
        return this->_mt_coords_for_new_bar_shape;
    }

    const std::vector<short> Shapes::get_mt_coords_of_new_T() 
    {
        return this->_mt_coords_for_new_T_shape;
    }

    const std::vector<short> Shapes::get_mt_coords_of_new_L_left() 
    {
        return this->_mt_coords_for_new_L_left_shape;
    }

    const std::vector<short> Shapes::get_mt_coords_of_new_L_right() 
    {
        return this->_mt_coords_for_new_L_right_shape;
    }

    const std::vector<short> Shapes::get_mt_coords_of_new_Z_left() 
    {
        return this->_mt_coords_for_new_Z_left_shape;
    }

    const std::vector<short> Shapes::get_mt_coords_of_new_Z_right() 
    {
        return this->_mt_coords_for_new_Z_right_shape;
    }
}
