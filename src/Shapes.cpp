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

    void Shapes::update_moving_shape_mt_coords(short moving_shape_mt_coords[], std::vector<short> new_coords) 
    {
        int x = sizeof(moving_shape_mt_coords)/sizeof(moving_shape_mt_coords[0]);
        for (short i = 0; i < 8; ++i) 
        {
            moving_shape_mt_coords[i] = new_coords[i];
        }
    }////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Shapes::generate_new_shape(short moving_shape_mt_coords[]) 
    {
        this->_which_shape = rand() % 8;
        switch (this->_which_shape)
        {
        case 1:
            update_moving_shape_mt_coords(moving_shape_mt_coords, this->_mt_coords_for_new_cube_shape);
            break;
        case 2:
            update_moving_shape_mt_coords(moving_shape_mt_coords, this->_mt_coords_for_new_bar_shape);
            break;
        case 3:
            update_moving_shape_mt_coords(moving_shape_mt_coords, this->_mt_coords_for_new_T_shape);
            break;
        case 4:
            update_moving_shape_mt_coords(moving_shape_mt_coords, this->_mt_coords_for_new_L_left_shape);
            break;
        case 5:
            update_moving_shape_mt_coords(moving_shape_mt_coords, this->_mt_coords_for_new_L_right_shape);
            break;
        case 6:
            update_moving_shape_mt_coords(moving_shape_mt_coords, this->_mt_coords_for_new_Z_left_shape);
            break;
        case 7:
            update_moving_shape_mt_coords(moving_shape_mt_coords, this->_mt_coords_for_new_Z_right_shape);
            break;
        default:
            break;
        }
    }

    void Shapes::rotate_bar(short mt[22][22], short moving_shape_mt_coords[8]) 
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

    void Shapes::rotate_T_shape(short mt[22][22], short moving_shape_mt_coords[8]) 
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

    void Shapes::rotate_L_left_shape(short mt[22][22], short moving_shape_mt_coords[8]) 
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

    void Shapes::rotate_L_right_shape(short mt[22][22], short moving_shape_mt_coords[8]) 
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

    void Shapes::rotate_Z_left_shape(short mt[22][22], short moving_shape_mt_coords[8]) 
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

    void Shapes::rotate_Z_right_shape(short mt[22][22], short moving_shape_mt_coords[8]) 
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

    void Shapes::rotate_shape(short mt[22][22], short moving_shape_mt_coords[])
    {
        switch (this->_which_shape)
        {
            case 2: // bar shape
                this->rotate_bar(mt, moving_shape_mt_coords);
                break;
            case 3: // T shape
                this->rotate_T_shape(mt, moving_shape_mt_coords);
                break;
            case 4: // L left shape
                this->rotate_L_left_shape(mt, moving_shape_mt_coords);
                break;
            case 5: // L right shape
                this->rotate_L_right_shape(mt, moving_shape_mt_coords);
                break;
            case 6: // Z left shape
                this->rotate_Z_left_shape(mt, moving_shape_mt_coords);
                break;
            case 7: // Z right shape
                this->rotate_Z_right_shape(mt, moving_shape_mt_coords);
                break;
            default:
                break;
        }
    }
}
