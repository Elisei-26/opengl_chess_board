#include "Shapes/L_Left.hpp"

namespace opengles_workspace 
{
    L_Left::L_Left(short moving_shape_mt_coords[]) 
    {
        for (short i = 0; i < 8; ++i) 
        {
            moving_shape_mt_coords[i] = this->_mt_coords_of_shape[i];
        }
    }

    std::vector<short> L_Left::get_mt_coords_of_shape() const  
    {
        return this->_mt_coords_of_shape;
    }

    void L_Left::rotate_shape(short mt[22][22], short moving_shape_mt_coords[8]) 
    {
        if(moving_shape_mt_coords[0] == moving_shape_mt_coords[2] && moving_shape_mt_coords[3] < moving_shape_mt_coords[1]) 
        {
            if (mt[moving_shape_mt_coords[2] - 1][moving_shape_mt_coords[3] + 1] == 0 &&
                mt[moving_shape_mt_coords[4] - 2][moving_shape_mt_coords[5]] == 0 && 
                mt[moving_shape_mt_coords[6] + 1][moving_shape_mt_coords[7] - 1] == 0) 
            {
                --moving_shape_mt_coords[2];
                ++moving_shape_mt_coords[3];
                moving_shape_mt_coords[4] -= 2;
                ++moving_shape_mt_coords[6];
                --moving_shape_mt_coords[7];
            }
        }
        else if (moving_shape_mt_coords[1] == moving_shape_mt_coords[3] && moving_shape_mt_coords[2] < moving_shape_mt_coords[0]) 
        {
            if (mt[moving_shape_mt_coords[2] + 1][moving_shape_mt_coords[3] + 1] == 0 &&
                mt[moving_shape_mt_coords[4]][moving_shape_mt_coords[5] + 2] == 0 && 
                mt[moving_shape_mt_coords[6] - 1][moving_shape_mt_coords[7] - 1] == 0) 
            {
                ++moving_shape_mt_coords[2];
                ++moving_shape_mt_coords[3];
                moving_shape_mt_coords[5] += 2;
                --moving_shape_mt_coords[6];
                --moving_shape_mt_coords[7];
            }
        }
        else if (moving_shape_mt_coords[0] == moving_shape_mt_coords[2] && moving_shape_mt_coords[3] > moving_shape_mt_coords[1]) 
        {
            if (mt[moving_shape_mt_coords[2] + 1][moving_shape_mt_coords[3] - 1] == 0 &&
                mt[moving_shape_mt_coords[4] + 2][moving_shape_mt_coords[5]] == 0 && 
                mt[moving_shape_mt_coords[6] - 1][moving_shape_mt_coords[7] + 1] == 0) 
            {
                ++moving_shape_mt_coords[2];
                --moving_shape_mt_coords[3];
                moving_shape_mt_coords[4] += 2;
                --moving_shape_mt_coords[6];
                ++moving_shape_mt_coords[7];
            }
        }
        else if (moving_shape_mt_coords[1] == moving_shape_mt_coords[3] && moving_shape_mt_coords[2] > moving_shape_mt_coords[0]) 
        {
            if (mt[moving_shape_mt_coords[2] - 1][moving_shape_mt_coords[3] - 1] == 0 &&
                mt[moving_shape_mt_coords[4]][moving_shape_mt_coords[5] - 2] == 0 && 
                mt[moving_shape_mt_coords[6] + 1][moving_shape_mt_coords[7] + 1] == 0) 
            {
                --moving_shape_mt_coords[2];
                --moving_shape_mt_coords[3];
                moving_shape_mt_coords[5] -= 2;
                ++moving_shape_mt_coords[6];
                ++moving_shape_mt_coords[7];
            }
        }
    }
}