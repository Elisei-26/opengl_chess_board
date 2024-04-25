#include "Shapes/Bar.hpp"

namespace opengles_workspace 
{
    Bar::Bar(short moving_shape_mt_coords[]) 
    {
        for (short i = 0; i < 8; ++i) 
        {
            moving_shape_mt_coords[i] = this->_mt_coords_of_shape[i];
        }
    }

    std::vector<short> Bar::get_mt_coords_of_shape() const  
    {
        return this->_mt_coords_of_shape;
    }

    void Bar::rotate_shape(short mt[22][22], short moving_shape_mt_coords[8]) 
    {
        if (moving_shape_mt_coords[0] == moving_shape_mt_coords[2]) 
        {
            if (mt[moving_shape_mt_coords[2] - 1][moving_shape_mt_coords[3] + 1] == 0 &&
                mt[moving_shape_mt_coords[4] + 1][moving_shape_mt_coords[5] - 1] == 0 &&
                mt[moving_shape_mt_coords[6] + 2][moving_shape_mt_coords[7] - 2] == 0) 
            {
                --moving_shape_mt_coords[2];
                ++moving_shape_mt_coords[3];
                ++moving_shape_mt_coords[4];
                --moving_shape_mt_coords[5];
                moving_shape_mt_coords[6] += 2;
                moving_shape_mt_coords[7] -= 2;
            }
        } 
        else 
        {
            if (mt[moving_shape_mt_coords[2] + 1][moving_shape_mt_coords[3] - 1] == 0 &&
                mt[moving_shape_mt_coords[4] - 1][moving_shape_mt_coords[5] + 1] == 0 &&
                mt[moving_shape_mt_coords[6] - 2][moving_shape_mt_coords[7] + 2] == 0) 
            {
                ++moving_shape_mt_coords[2];
                --moving_shape_mt_coords[3];
                --moving_shape_mt_coords[4];
                ++moving_shape_mt_coords[5];
                moving_shape_mt_coords[6] -= 2;
                moving_shape_mt_coords[7] += 2;
            }
        }
    }
}