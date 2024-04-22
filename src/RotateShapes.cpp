#include "RotateShapes.hpp"

namespace opengles_workspace 
{ 
    void RotateShapes::rotate_bar(short mt[22][22], short moving_shape_mt_coords[8]) 
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

    void RotateShapes::rotate_T_shape(short mt[22][22], short moving_shape_mt_coords[8]) 
    {
        if(moving_shape_mt_coords[0] == moving_shape_mt_coords[2] && moving_shape_mt_coords[3] < moving_shape_mt_coords[1]) 
        {
            if (mt[moving_shape_mt_coords[2] - 1][moving_shape_mt_coords[3] + 1] == 0 &&
                mt[moving_shape_mt_coords[4] + 1][moving_shape_mt_coords[5] + 1] == 0 &&
                mt[moving_shape_mt_coords[6] + 1][moving_shape_mt_coords[7] - 1] == 0) 
            {
                --moving_shape_mt_coords[2];
                ++moving_shape_mt_coords[3];
                ++moving_shape_mt_coords[4];
                ++moving_shape_mt_coords[5];
                ++moving_shape_mt_coords[6];
                --moving_shape_mt_coords[7];
            }
        }
        else if (moving_shape_mt_coords[1] == moving_shape_mt_coords[3] && moving_shape_mt_coords[2] < moving_shape_mt_coords[0]) 
        {
            if (mt[moving_shape_mt_coords[2] + 1][moving_shape_mt_coords[3] + 1] == 0 &&
                mt[moving_shape_mt_coords[4] + 1][moving_shape_mt_coords[5] - 1] == 0 &&
                mt[moving_shape_mt_coords[6] - 1][moving_shape_mt_coords[7] - 1] == 0) 
            {
                ++moving_shape_mt_coords[2];
                ++moving_shape_mt_coords[3];
                ++moving_shape_mt_coords[4];
                --moving_shape_mt_coords[5];
                --moving_shape_mt_coords[6];
                --moving_shape_mt_coords[7];
            }
        }
        else if (moving_shape_mt_coords[0] == moving_shape_mt_coords[2] && moving_shape_mt_coords[3] > moving_shape_mt_coords[1]) 
        {
            if (mt[moving_shape_mt_coords[2] + 1][moving_shape_mt_coords[3] - 1] == 0 &&
                mt[moving_shape_mt_coords[4] - 1][moving_shape_mt_coords[5] - 1] == 0 &&
                mt[moving_shape_mt_coords[6] - 1][moving_shape_mt_coords[7] + 1] == 0) 
            {
                ++moving_shape_mt_coords[2];
                --moving_shape_mt_coords[3];
                --moving_shape_mt_coords[4];
                --moving_shape_mt_coords[5];
                --moving_shape_mt_coords[6];
                ++moving_shape_mt_coords[7];
            }
        }
        else if (moving_shape_mt_coords[1] == moving_shape_mt_coords[3] && moving_shape_mt_coords[2] > moving_shape_mt_coords[0]) 
        {
            if (mt[moving_shape_mt_coords[2] - 1][moving_shape_mt_coords[3] - 1] == 0 &&
                mt[moving_shape_mt_coords[4] - 1][moving_shape_mt_coords[5] + 1] == 0 &&
                mt[moving_shape_mt_coords[6] + 1][moving_shape_mt_coords[7] + 1] == 0) 
            {
                --moving_shape_mt_coords[2];
                --moving_shape_mt_coords[3];
                --moving_shape_mt_coords[4];
                ++moving_shape_mt_coords[5];
                ++moving_shape_mt_coords[6];
                ++moving_shape_mt_coords[7];
            }
        }
    }

    void RotateShapes::rotate_L_left_shape(short mt[22][22], short moving_shape_mt_coords[8]) 
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

    void RotateShapes::rotate_L_right_shape(short mt[22][22], short moving_shape_mt_coords[8]) 
    {
        if(moving_shape_mt_coords[0] == moving_shape_mt_coords[2] && moving_shape_mt_coords[3] > moving_shape_mt_coords[1]) 
        {
            if (mt[moving_shape_mt_coords[2] + 1][moving_shape_mt_coords[3] - 1] == 0 &&
                mt[moving_shape_mt_coords[4]][moving_shape_mt_coords[5] - 2] == 0 && 
                mt[moving_shape_mt_coords[6] - 1][moving_shape_mt_coords[7] + 1] == 0) 
            {
                ++moving_shape_mt_coords[2];
                --moving_shape_mt_coords[3];
                moving_shape_mt_coords[5] -= 2;
                --moving_shape_mt_coords[6];
                ++moving_shape_mt_coords[7];
            }
        }
        else if (moving_shape_mt_coords[1] == moving_shape_mt_coords[3] && moving_shape_mt_coords[2] > moving_shape_mt_coords[0]) 
        {
            if (mt[moving_shape_mt_coords[2] - 1][moving_shape_mt_coords[3] - 1] == 0 &&
                mt[moving_shape_mt_coords[4] - 2][moving_shape_mt_coords[5]] == 0 && 
                mt[moving_shape_mt_coords[6] + 1][moving_shape_mt_coords[7] + 1] == 0) 
            {
                --moving_shape_mt_coords[2];
                --moving_shape_mt_coords[3];
                moving_shape_mt_coords[4] -= 2;
                ++moving_shape_mt_coords[6];
                ++moving_shape_mt_coords[7];
            }
        }
        else if (moving_shape_mt_coords[0] == moving_shape_mt_coords[2] && moving_shape_mt_coords[3] < moving_shape_mt_coords[1]) 
        {
            if (mt[moving_shape_mt_coords[2] - 1][moving_shape_mt_coords[3] + 1] == 0 &&
                mt[moving_shape_mt_coords[4]][moving_shape_mt_coords[5] + 2] == 0 && 
                mt[moving_shape_mt_coords[6] + 1][moving_shape_mt_coords[7] - 1] == 0) 
            {
                --moving_shape_mt_coords[2];
                ++moving_shape_mt_coords[3];
                moving_shape_mt_coords[5] += 2;
                ++moving_shape_mt_coords[6];
                --moving_shape_mt_coords[7];
            }
        }
        else if (moving_shape_mt_coords[1] == moving_shape_mt_coords[3] && moving_shape_mt_coords[2] < moving_shape_mt_coords[0]) 
        {
            if (mt[moving_shape_mt_coords[2] + 1][moving_shape_mt_coords[3] + 1] == 0 &&
                mt[moving_shape_mt_coords[4] + 2][moving_shape_mt_coords[5]] == 0 && 
                mt[moving_shape_mt_coords[6] - 1][moving_shape_mt_coords[7] - 1] == 0) 
            {
                ++moving_shape_mt_coords[2];
                ++moving_shape_mt_coords[3];
                moving_shape_mt_coords[4] += 2;
                --moving_shape_mt_coords[6];
                --moving_shape_mt_coords[7];
            }
        }
    }

    void RotateShapes::rotate_Z_left_shape(short mt[22][22], short moving_shape_mt_coords[8]) 
    {
        if (moving_shape_mt_coords[0] == moving_shape_mt_coords[2]) 
        {
            if (mt[moving_shape_mt_coords[2] - 1][moving_shape_mt_coords[3] + 1] == 0 &&
                mt[moving_shape_mt_coords[4] - 1][moving_shape_mt_coords[5] - 1] == 0 &&
                mt[moving_shape_mt_coords[6]][moving_shape_mt_coords[7] - 2] == 0) 
            {
                --moving_shape_mt_coords[2];
                ++moving_shape_mt_coords[3];
                --moving_shape_mt_coords[4];
                --moving_shape_mt_coords[5];
                moving_shape_mt_coords[7] -= 2;
            }
        } 
        else 
        {
            if (mt[moving_shape_mt_coords[2] + 1][moving_shape_mt_coords[3] - 1] == 0 &&
                mt[moving_shape_mt_coords[4] + 1][moving_shape_mt_coords[5] + 1] == 0 &&
                mt[moving_shape_mt_coords[6]][moving_shape_mt_coords[7] + 2] == 0) 
            {
                ++moving_shape_mt_coords[2];
                --moving_shape_mt_coords[3];
                ++moving_shape_mt_coords[4];
                ++moving_shape_mt_coords[5];
                moving_shape_mt_coords[7] += 2;
            }
        }
    }

    void RotateShapes::rotate_Z_right_shape(short mt[22][22], short moving_shape_mt_coords[8]) 
    {
        if (moving_shape_mt_coords[0] == moving_shape_mt_coords[2]) 
        {
            if (mt[moving_shape_mt_coords[2] - 1][moving_shape_mt_coords[3] - 1] == 0 &&
                mt[moving_shape_mt_coords[4] - 1][moving_shape_mt_coords[5] + 1] == 0 &&
                mt[moving_shape_mt_coords[6]][moving_shape_mt_coords[7] + 2] == 0) 
            {
                --moving_shape_mt_coords[2];
                --moving_shape_mt_coords[3];
                --moving_shape_mt_coords[4];
                ++moving_shape_mt_coords[5];
                moving_shape_mt_coords[7] += 2;
            }
        } 
        else 
        {
            if (mt[moving_shape_mt_coords[2] + 1][moving_shape_mt_coords[3] + 1] == 0 &&
                mt[moving_shape_mt_coords[4] + 1][moving_shape_mt_coords[5] - 1] == 0 &&
                mt[moving_shape_mt_coords[6]][moving_shape_mt_coords[7] - 2] == 0) 
            {
                ++moving_shape_mt_coords[2];
                ++moving_shape_mt_coords[3];
                ++moving_shape_mt_coords[4];
                --moving_shape_mt_coords[5];
                moving_shape_mt_coords[7] -= 2;
            }
        }
    }

}