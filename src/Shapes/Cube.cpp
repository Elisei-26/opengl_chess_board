#include "Shapes/Cube.hpp"

namespace opengles_workspace 
{
    Cube::Cube(short moving_shape_mt_coords[]) 
    {
        for (short i = 0; i < 8; ++i) 
        {
            moving_shape_mt_coords[i] = this->_mt_coords_of_shape[i];
        }
    }

    std::vector<short> Cube::get_mt_coords_of_shape() const  
    {
        return this->_mt_coords_of_shape;
    }

    void Cube::rotate_shape(short mt[22][22], short moving_shape_mt_coords[8]) 
    {
        // the cube doesn't need to rotate
    }
}