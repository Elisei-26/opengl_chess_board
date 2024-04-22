#include "Shapes.hpp"

namespace opengles_workspace 
{
    std::vector<short> Shapes::get_mt_coords_of_new_cube() const  
    {
        return this->_mt_coords_for_new_cube_shape;
    }

    std::vector<short> Shapes::get_mt_coords_of_new_bar() const  
    {
        return this->_mt_coords_for_new_bar_shape;
    }

    std::vector<short> Shapes::get_mt_coords_of_new_T() const  
    {
        return this->_mt_coords_for_new_T_shape;
    }

    std::vector<short> Shapes::get_mt_coords_of_new_L_left() const  
    {
        return this->_mt_coords_for_new_L_left_shape;
    }

    std::vector<short> Shapes::get_mt_coords_of_new_L_right() const  
    {
        return this->_mt_coords_for_new_L_right_shape;
    }

    std::vector<short> Shapes::get_mt_coords_of_new_Z_left() const  
    {
        return this->_mt_coords_for_new_Z_left_shape;
    }

    std::vector<short> Shapes::get_mt_coords_of_new_Z_right() const  
    {
        return this->_mt_coords_for_new_Z_right_shape;
    }
}
