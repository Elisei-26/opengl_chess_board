#include "../include/Table.hpp"

namespace opengles_workspace 
{           
    Table::Table() 
    {
        for (short i = 0; i < 22; ++i) // create a virtual margin in matrix that represent game status
        {
            this->mt_game_status[i][0] = 1;
            this->mt_game_status[0][i] = 1;
            this->mt_game_status[i][21] = 1;
            this->mt_game_status[21][i] = 1;
        }

        this->which_shape = 1;
        this->score = 0;
        this->move_shape_y_status = 0.0f;
        this->axis_y_speed = 0.0f;
        this->nr_frames = 0;
        this->one_shape_nr_vertices = 72;
        this->vertices_length = one_shape_nr_vertices;
    }

    std::vector<float> Table::get_vertices_array() 
    {
        return this->vertices;
    }
    
    void Table::set_nr_frames(int nr_fps) 
    {
        this->nr_frames = nr_fps;
    }

    void Table::set_axis_y_speed() 
    {
        this->axis_y_speed = (float)1 / this->nr_frames * -1.0f;
    }

    float Table::get_axis_y_speed() 
    {
        return this->axis_y_speed;
    }

    short Table::get_vertices_length() 
    {
        return this->vertices_length;
    }

    bool Table::game_over() 
    {
        if (this->mt_game_status[2][10] == 0) 
        {
            return false;
        }
        return true;
    }

    short Table::get_score() 
    {
        return this->score;
    }

    void Table::delete_line_from_mt(short line) 
    {
        for (short j = 1; j < 21; ++j) 
        {
            this->mt_game_status[line][j] = 0;
        }
        this->score += 10;
    }

    void Table::move_mt_upper_lines_down(short line) 
    {
        for (short i = line; i > 1; --i) 
        {
            for (short j = 1; j < 21; ++j) 
            {
                this->mt_game_status[i][j] = this->mt_game_status[i - 1][j];
            }
        }
    }

    void Table::check_mt_lines_completed() 
    {
        bool line_completed = true;
        for (short i = 20; i > 0; --i) 
        {
            line_completed = true;
            for (short j = 1; j < 21; ++j) // check if line is complete
            {
                if (this->mt_game_status[i][j] == 0) 
                {
                    line_completed = false;
                }
            }

            if (line_completed)
            {
                delete_line_from_mt(i);
                move_mt_upper_lines_down(i);
                ++i; // if more than one line is completed with one shape, we need to check the current line twice
            }
        }
    }

    void Table::delete_excess_of_vertices(short new_vert_length) 
    {
        vertices.resize(vertices.size() - (this->vertices_length - new_vert_length));
        this->vertices_length = new_vert_length;
    }

    void Table::calculate_vert_coords_using_mt() 
    {
        short vert_ind = 0;
        float mt_line_to_x_coord = 0.0f;
        float mt_col_to_y_coord = 0.0f;
        float adjust_x_y_coord = 0.1f;

        for (short i = 20; i > 0; --i) 
        {
            for (short j = 1; j < 21; ++j) 
            {
                if (mt_game_status[i][j] == 2)
                {
                    mt_line_to_x_coord = (float)j / 10.0f - 1.1f;
                    mt_col_to_y_coord = ((float)i / 10.0f - 1.0f) * -1.0f;

                    this->vertices[vert_ind++] = mt_line_to_x_coord;
                    this->vertices[vert_ind++] = mt_col_to_y_coord;
                    this->vertices[vert_ind++] = 0.0f;

                    this->vertices[vert_ind++] = mt_line_to_x_coord + adjust_x_y_coord;
                    this->vertices[vert_ind++] = mt_col_to_y_coord;
                    this->vertices[vert_ind++] = 0.0f;

                    this->vertices[vert_ind++] = mt_line_to_x_coord;
                    this->vertices[vert_ind++] = mt_col_to_y_coord + adjust_x_y_coord;
                    this->vertices[vert_ind++] = 0.0f;

                    this->vertices[vert_ind++] = mt_line_to_x_coord;
                    this->vertices[vert_ind++] = mt_col_to_y_coord + adjust_x_y_coord;
                    this->vertices[vert_ind++] = 0.0f;

                    this->vertices[vert_ind++] = mt_line_to_x_coord + adjust_x_y_coord;
                    this->vertices[vert_ind++] = mt_col_to_y_coord;
                    this->vertices[vert_ind++] = 0.0f;

                    this->vertices[vert_ind++] = mt_line_to_x_coord + adjust_x_y_coord;
                    this->vertices[vert_ind++] = mt_col_to_y_coord + adjust_x_y_coord;
                    this->vertices[vert_ind++] = 0.0f;
                }
            }
        } 
        delete_excess_of_vertices(vert_ind);
    }

    void Table::update_moving_shape_mt_coords(short new_coords[]) 
    {
        for (short i = 0; i < 8; ++i) 
        {
            this->moving_shape_mt_coords[i] = new_coords[i];
        }
    }

    void Table::update_mt_game_status(short coords_of_landed_shape[]) 
    {
        for (short i = 0; i < 8; i += 2) 
        {
            this->mt_game_status[coords_of_landed_shape[i]][coords_of_landed_shape[i + 1]] = 2;
        }
    }

    void Table::calculate_new_shape_vert_coords(short mt_coords[]) 
    {
        short vert_ind = 0;
        float mt_line_to_x_coord = 0.0f;
        float mt_col_to_y_coord = 0.0f;
        float adjust_x_y_coord = 0.1f;

        for (short i = 0; i < 8; i += 2) 
        {
            mt_line_to_x_coord = (float)mt_coords[i + 1] / 10.0f - 1.1f;
            mt_col_to_y_coord = ((float)mt_coords[i] / 10.0f - 1.0f) * -1.0f;
            
            this->vert_coords_generated_shape[vert_ind++] = mt_line_to_x_coord;
            this->vert_coords_generated_shape[vert_ind++] = mt_col_to_y_coord;
            this->vert_coords_generated_shape[vert_ind++] = 0.0f;

            this->vert_coords_generated_shape[vert_ind++] = mt_line_to_x_coord + adjust_x_y_coord;
            this->vert_coords_generated_shape[vert_ind++] = mt_col_to_y_coord;
            this->vert_coords_generated_shape[vert_ind++] = 0.0f;

            this->vert_coords_generated_shape[vert_ind++] = mt_line_to_x_coord;
            this->vert_coords_generated_shape[vert_ind++] = mt_col_to_y_coord + adjust_x_y_coord;
            this->vert_coords_generated_shape[vert_ind++] = 0.0f;

            this->vert_coords_generated_shape[vert_ind++] = mt_line_to_x_coord;
            this->vert_coords_generated_shape[vert_ind++] = mt_col_to_y_coord + adjust_x_y_coord;
            this->vert_coords_generated_shape[vert_ind++] = 0.0f;

            this->vert_coords_generated_shape[vert_ind++] = mt_line_to_x_coord + adjust_x_y_coord;
            this->vert_coords_generated_shape[vert_ind++] = mt_col_to_y_coord;
            this->vert_coords_generated_shape[vert_ind++] = 0.0f;

            this->vert_coords_generated_shape[vert_ind++] = mt_line_to_x_coord + adjust_x_y_coord;
            this->vert_coords_generated_shape[vert_ind++] = mt_col_to_y_coord + adjust_x_y_coord;
            this->vert_coords_generated_shape[vert_ind++] = 0.0f;
        }
    }

    void Table::update_vert_coords_of_moving_shape() 
    {
        vertices.resize(vertices.size() - one_shape_nr_vertices); // delete last shape because I'm updating it's coords
        for (short i = 0; i < this->one_shape_nr_vertices; ++i) 
        {
            vertices.push_back(this->vert_coords_generated_shape[i]);
        }

    }

    void Table::add_new_shape_vert_coords_in_vertices_vect() 
    {
        this->vertices_length += one_shape_nr_vertices;
        for (short i = 0; i < this->one_shape_nr_vertices; ++i) 
        {
            vertices.push_back(this->vert_coords_generated_shape[i]);
        }
    }

    bool Table::sth_under_falling_shape() 
    {
        bool falling = true;
        for (short i = 0; i < 8; i += 2) // check if there is sth under the shape
        {
            if (this->mt_game_status[this->moving_shape_mt_coords[i] + 1][this->moving_shape_mt_coords[i + 1]] != 0) 
            {
                falling = false;
            }
        }
        return falling;
    }

    void Table::move_shape_down(float axis_y_speed) 
    {	
        bool falling = sth_under_falling_shape();
        if (falling) // daca forma se afla in cadere
        {
            this->move_shape_y_status = this->move_shape_y_status + (this->axis_y_speed * -1);
            if (this->move_shape_y_status >= 0.1f) // daca forma s-a deplasat in jos o pozitie din matrice
            {
                this->move_shape_y_status = 0.0f;
                for (short i = 0; i < 8; i += 2) 
                {
                    ++this->moving_shape_mt_coords[i];
                }
            }

            short first_vert_coord_of_moving_shape = this->vertices_length - this->one_shape_nr_vertices + 1;
            for (short i = first_vert_coord_of_moving_shape; i < vertices_length; i += 3)
            {
                this->vertices[i] += this->axis_y_speed;
            }
        }
        else if (!falling) // daca forma a terminat caderea
        {			
            update_mt_game_status(this->moving_shape_mt_coords);
            check_mt_lines_completed();
            calculate_vert_coords_using_mt();

            which_shape = rand() % 8;
            switch (which_shape)
            {
            case 1:
                update_moving_shape_mt_coords(get_mt_coords_of_new_cube().data());
                calculate_new_shape_vert_coords(get_mt_coords_of_new_cube().data());
                break;
            case 2:
                update_moving_shape_mt_coords(get_mt_coords_of_new_bar().data());
                calculate_new_shape_vert_coords(get_mt_coords_of_new_bar().data());
                break;
            case 3:
                update_moving_shape_mt_coords(get_mt_coords_of_new_T().data());
                calculate_new_shape_vert_coords(get_mt_coords_of_new_T().data());
                break;
            case 4:
                update_moving_shape_mt_coords(get_mt_coords_of_new_L_left().data());
                calculate_new_shape_vert_coords(get_mt_coords_of_new_L_left().data());
                break;
            case 5:
                update_moving_shape_mt_coords(get_mt_coords_of_new_L_right().data());
                calculate_new_shape_vert_coords(get_mt_coords_of_new_L_right().data());
                break;
            case 6:
                update_moving_shape_mt_coords(get_mt_coords_of_new_Z_left().data());
                calculate_new_shape_vert_coords(get_mt_coords_of_new_Z_left().data());
                break;
            case 7:
                update_moving_shape_mt_coords(get_mt_coords_of_new_Z_right().data());
                calculate_new_shape_vert_coords(get_mt_coords_of_new_Z_right().data());
                break;
            default:
                break;
            }
            score += 3;
            add_new_shape_vert_coords_in_vertices_vect();
        }
    }

    void Table::move_shape_to_right() 
    {
        bool can_move_right = true;
        for (short i = 0; i < 8; i += 2) 
        {
            // nu are margine sau alta forma in partea dreapta && nu are margine sau forma in partea dreapta cu o pozitie mai jos
            if (this->mt_game_status[this->moving_shape_mt_coords[i]][this->moving_shape_mt_coords[i + 1] + 1] != 0 && this->mt_game_status[this->moving_shape_mt_coords[i] + 1][this->moving_shape_mt_coords[i + 1] + 1] != 0)
            {
                can_move_right = false;
                i = 8;
            }
        }

        if (can_move_right)
        {
            for (short i = 1; i < 8; i += 2) 
            {
                ++this->moving_shape_mt_coords[i];
            }
            short first_vert_coord_of_moving_shape = this->vertices_length - this->one_shape_nr_vertices;
            float one_table_position = 0.1f;
            for (short i = first_vert_coord_of_moving_shape; i < this->vertices_length; i += 3) 
            {
                this->vertices[i] += one_table_position;
            }
        }
    }

    void Table::move_shape_to_left() 
    {
        bool can_move_left = true;
        for (short i = 0; i < 8; i += 2) 
        {
            // nu are margine sau alta forma in partea stanga && nu are margine sau forma in partea stanga cu o pozitie mai jos
            if (this->mt_game_status[this->moving_shape_mt_coords[i]][this->moving_shape_mt_coords[i + 1] - 1] != 0 && this->mt_game_status[this->moving_shape_mt_coords[i] + 1][this->moving_shape_mt_coords[i + 1] - 1] != 0)
            {
                can_move_left = false;
                i = 8;
            }
        }

        if (can_move_left)
        {
            for (short i = 1; i < 8; i += 2) 
            {
                --this->moving_shape_mt_coords[i];
            }
            short first_vert_coord_of_moving_shape = vertices_length - one_shape_nr_vertices;
            float one_table_position = -0.1f;
            for (short i = first_vert_coord_of_moving_shape; i < vertices_length; i += 3) 
            {
                this->vertices[i] += one_table_position;
            }
        }
    }

    void Table::rotate_shape() 
    {
        switch (which_shape)
        {
            case 2: // bar shape
                if (this->moving_shape_mt_coords[0] == this->moving_shape_mt_coords[2]) 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] - 1][this->moving_shape_mt_coords[3] + 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4] + 1][this->moving_shape_mt_coords[5] - 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[6] + 2][this->moving_shape_mt_coords[7] - 2] == 0) 
                    {
                        --this->moving_shape_mt_coords[2];
                        ++this->moving_shape_mt_coords[3];
                        ++this->moving_shape_mt_coords[4];
                        --this->moving_shape_mt_coords[5];
                        this->moving_shape_mt_coords[6] += 2;
                        this->moving_shape_mt_coords[7] -= 2;
                    }
                } 
                else 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] + 1][this->moving_shape_mt_coords[3] - 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4] - 1][this->moving_shape_mt_coords[5] + 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[6] - 2][this->moving_shape_mt_coords[7] + 2] == 0) 
                    {
                        ++this->moving_shape_mt_coords[2];
                        --this->moving_shape_mt_coords[3];
                        --this->moving_shape_mt_coords[4];
                        ++this->moving_shape_mt_coords[5];
                        this->moving_shape_mt_coords[6] -= 2;
                        this->moving_shape_mt_coords[7] += 2;
                    }
                }
                calculate_new_shape_vert_coords(this->moving_shape_mt_coords);
                update_vert_coords_of_moving_shape();
                break;
            case 3: // T shape
                if(this->moving_shape_mt_coords[0] == this->moving_shape_mt_coords[2] && this->moving_shape_mt_coords[3] < this->moving_shape_mt_coords[1]) 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] - 1][this->moving_shape_mt_coords[3] + 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4] + 1][this->moving_shape_mt_coords[5] + 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[6] + 1][this->moving_shape_mt_coords[7] - 1] == 0) 
                    {
                        --this->moving_shape_mt_coords[2];
                        ++this->moving_shape_mt_coords[3];
                        ++this->moving_shape_mt_coords[4];
                        ++this->moving_shape_mt_coords[5];
                        ++this->moving_shape_mt_coords[6];
                        --this->moving_shape_mt_coords[7];
                    }
                }
                else if (this->moving_shape_mt_coords[1] == this->moving_shape_mt_coords[3] && this->moving_shape_mt_coords[2] < this->moving_shape_mt_coords[0]) 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] + 1][this->moving_shape_mt_coords[3] + 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4] + 1][this->moving_shape_mt_coords[5] - 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[6] - 1][this->moving_shape_mt_coords[7] - 1] == 0) 
                    {
                        ++this->moving_shape_mt_coords[2];
                        ++this->moving_shape_mt_coords[3];
                        ++this->moving_shape_mt_coords[4];
                        --this->moving_shape_mt_coords[5];
                        --this->moving_shape_mt_coords[6];
                        --this->moving_shape_mt_coords[7];
                    }
                }
                else if (this->moving_shape_mt_coords[0] == this->moving_shape_mt_coords[2] && this->moving_shape_mt_coords[3] > this->moving_shape_mt_coords[1]) 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] + 1][this->moving_shape_mt_coords[3] - 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4] - 1][this->moving_shape_mt_coords[5] - 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[6] - 1][this->moving_shape_mt_coords[7] + 1] == 0) 
                    {
                        ++this->moving_shape_mt_coords[2];
                        --this->moving_shape_mt_coords[3];
                        --this->moving_shape_mt_coords[4];
                        --this->moving_shape_mt_coords[5];
                        --this->moving_shape_mt_coords[6];
                        ++this->moving_shape_mt_coords[7];
                    }
                }
                else if (this->moving_shape_mt_coords[1] == this->moving_shape_mt_coords[3] && this->moving_shape_mt_coords[2] > this->moving_shape_mt_coords[0]) 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] - 1][this->moving_shape_mt_coords[3] - 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4] - 1][this->moving_shape_mt_coords[5] + 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[6] + 1][this->moving_shape_mt_coords[7] + 1] == 0) 
                    {
                        --this->moving_shape_mt_coords[2];
                        --this->moving_shape_mt_coords[3];
                        --this->moving_shape_mt_coords[4];
                        ++this->moving_shape_mt_coords[5];
                        ++this->moving_shape_mt_coords[6];
                        ++this->moving_shape_mt_coords[7];
                    }
                }
                calculate_new_shape_vert_coords(this->moving_shape_mt_coords);
                update_vert_coords_of_moving_shape();
                break;
            case 4: // L left shape
                if(this->moving_shape_mt_coords[0] == this->moving_shape_mt_coords[2] && this->moving_shape_mt_coords[3] < this->moving_shape_mt_coords[1]) 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] - 1][this->moving_shape_mt_coords[3] + 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4] - 2][this->moving_shape_mt_coords[5]] == 0 && 
                        this->mt_game_status[this->moving_shape_mt_coords[6] + 1][this->moving_shape_mt_coords[7] - 1] == 0) 
                    {
                        --this->moving_shape_mt_coords[2];
                        ++this->moving_shape_mt_coords[3];
                        this->moving_shape_mt_coords[4] -= 2;
                        ++this->moving_shape_mt_coords[6];
                        --this->moving_shape_mt_coords[7];
                    }
                }
                else if (this->moving_shape_mt_coords[1] == this->moving_shape_mt_coords[3] && this->moving_shape_mt_coords[2] < this->moving_shape_mt_coords[0]) 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] + 1][this->moving_shape_mt_coords[3] + 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4]][this->moving_shape_mt_coords[5] + 2] == 0 && 
                        this->mt_game_status[this->moving_shape_mt_coords[6] - 1][this->moving_shape_mt_coords[7] - 1] == 0) 
                    {
                        ++this->moving_shape_mt_coords[2];
                        ++this->moving_shape_mt_coords[3];
                        this->moving_shape_mt_coords[5] += 2;
                        --this->moving_shape_mt_coords[6];
                        --this->moving_shape_mt_coords[7];
                    }
                }
                else if (this->moving_shape_mt_coords[0] == this->moving_shape_mt_coords[2] && this->moving_shape_mt_coords[3] > this->moving_shape_mt_coords[1]) 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] + 1][this->moving_shape_mt_coords[3] - 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4] + 2][this->moving_shape_mt_coords[5]] == 0 && 
                        this->mt_game_status[this->moving_shape_mt_coords[6] - 1][this->moving_shape_mt_coords[7] + 1] == 0) 
                    {
                        ++this->moving_shape_mt_coords[2];
                        --this->moving_shape_mt_coords[3];
                        this->moving_shape_mt_coords[4] += 2;
                        --this->moving_shape_mt_coords[6];
                        ++this->moving_shape_mt_coords[7];
                    }
                }
                else if (this->moving_shape_mt_coords[1] == this->moving_shape_mt_coords[3] && this->moving_shape_mt_coords[2] > this->moving_shape_mt_coords[0]) 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] - 1][this->moving_shape_mt_coords[3] - 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4]][this->moving_shape_mt_coords[5] - 2] == 0 && 
                        this->mt_game_status[this->moving_shape_mt_coords[6] + 1][this->moving_shape_mt_coords[7] + 1] == 0) 
                    {
                        --this->moving_shape_mt_coords[2];
                        --this->moving_shape_mt_coords[3];
                        this->moving_shape_mt_coords[5] -= 2;
                        ++this->moving_shape_mt_coords[6];
                        ++this->moving_shape_mt_coords[7];
                    }
                }
                calculate_new_shape_vert_coords(this->moving_shape_mt_coords);
                update_vert_coords_of_moving_shape();
                break;
            case 5: // L right shape
                if(this->moving_shape_mt_coords[0] == this->moving_shape_mt_coords[2] && this->moving_shape_mt_coords[3] > this->moving_shape_mt_coords[1]) 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] + 1][this->moving_shape_mt_coords[3] - 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4]][this->moving_shape_mt_coords[5] - 2] == 0 && 
                        this->mt_game_status[this->moving_shape_mt_coords[6] - 1][this->moving_shape_mt_coords[7] + 1] == 0) 
                    {
                        ++this->moving_shape_mt_coords[2];
                        --this->moving_shape_mt_coords[3];
                        this->moving_shape_mt_coords[5] -= 2;
                        --this->moving_shape_mt_coords[6];
                        ++this->moving_shape_mt_coords[7];
                    }
                }
                else if (this->moving_shape_mt_coords[1] == this->moving_shape_mt_coords[3] && this->moving_shape_mt_coords[2] > this->moving_shape_mt_coords[0]) 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] - 1][this->moving_shape_mt_coords[3] - 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4] - 2][this->moving_shape_mt_coords[5]] == 0 && 
                        this->mt_game_status[this->moving_shape_mt_coords[6] + 1][this->moving_shape_mt_coords[7] + 1] == 0) 
                    {
                        --this->moving_shape_mt_coords[2];
                        --this->moving_shape_mt_coords[3];
                        this->moving_shape_mt_coords[4] -= 2;
                        ++this->moving_shape_mt_coords[6];
                        ++this->moving_shape_mt_coords[7];
                    }
                }
                else if (this->moving_shape_mt_coords[0] == this->moving_shape_mt_coords[2] && this->moving_shape_mt_coords[3] < this->moving_shape_mt_coords[1]) 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] - 1][this->moving_shape_mt_coords[3] + 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4]][this->moving_shape_mt_coords[5] + 2] == 0 && 
                        this->mt_game_status[this->moving_shape_mt_coords[6] + 1][this->moving_shape_mt_coords[7] - 1] == 0) 
                    {
                        --this->moving_shape_mt_coords[2];
                        ++this->moving_shape_mt_coords[3];
                        this->moving_shape_mt_coords[5] += 2;
                        ++this->moving_shape_mt_coords[6];
                        --this->moving_shape_mt_coords[7];
                    }
                }
                else if (this->moving_shape_mt_coords[1] == this->moving_shape_mt_coords[3] && this->moving_shape_mt_coords[2] < this->moving_shape_mt_coords[0]) 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] + 1][this->moving_shape_mt_coords[3] + 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4] + 2][this->moving_shape_mt_coords[5]] == 0 && 
                        this->mt_game_status[this->moving_shape_mt_coords[6] - 1][this->moving_shape_mt_coords[7] - 1] == 0) 
                    {
                        ++this->moving_shape_mt_coords[2];
                        ++this->moving_shape_mt_coords[3];
                        this->moving_shape_mt_coords[4] += 2;
                        --this->moving_shape_mt_coords[6];
                        --this->moving_shape_mt_coords[7];
                    }
                }
                calculate_new_shape_vert_coords(this->moving_shape_mt_coords);
                update_vert_coords_of_moving_shape();
                break;
            case 6: // Z left shape
                if (this->moving_shape_mt_coords[0] == this->moving_shape_mt_coords[2]) 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] - 1][this->moving_shape_mt_coords[3] + 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4] - 1][this->moving_shape_mt_coords[5] - 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[6]][this->moving_shape_mt_coords[7] - 2] == 0) 
                    {
                        --this->moving_shape_mt_coords[2];
                        ++this->moving_shape_mt_coords[3];
                        --this->moving_shape_mt_coords[4];
                        --this->moving_shape_mt_coords[5];
                        this->moving_shape_mt_coords[7] -= 2;
                    }
                } 
                else 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] + 1][this->moving_shape_mt_coords[3] - 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4] + 1][this->moving_shape_mt_coords[5] + 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[6]][this->moving_shape_mt_coords[7] + 2] == 0) 
                    {
                        ++this->moving_shape_mt_coords[2];
                        --this->moving_shape_mt_coords[3];
                        ++this->moving_shape_mt_coords[4];
                        ++this->moving_shape_mt_coords[5];
                        this->moving_shape_mt_coords[7] += 2;
                    }
                }
                calculate_new_shape_vert_coords(this->moving_shape_mt_coords);
                update_vert_coords_of_moving_shape();
                break;
            case 7: // Z right shape
                if (this->moving_shape_mt_coords[0] == this->moving_shape_mt_coords[2]) 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] - 1][this->moving_shape_mt_coords[3] - 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4] - 1][this->moving_shape_mt_coords[5] + 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[6]][this->moving_shape_mt_coords[7] + 2] == 0) 
                    {
                        --this->moving_shape_mt_coords[2];
                        --this->moving_shape_mt_coords[3];
                        --this->moving_shape_mt_coords[4];
                        ++this->moving_shape_mt_coords[5];
                        this->moving_shape_mt_coords[7] += 2;
                    }
                } 
                else 
                {
                    if (this->mt_game_status[this->moving_shape_mt_coords[2] + 1][this->moving_shape_mt_coords[3] + 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[4] + 1][this->moving_shape_mt_coords[5] - 1] == 0 &&
                        this->mt_game_status[this->moving_shape_mt_coords[6]][this->moving_shape_mt_coords[7] - 2] == 0) 
                    {
                        ++this->moving_shape_mt_coords[2];
                        ++this->moving_shape_mt_coords[3];
                        ++this->moving_shape_mt_coords[4];
                        --this->moving_shape_mt_coords[5];
                        this->moving_shape_mt_coords[7] -= 2;
                    }
                }
                calculate_new_shape_vert_coords(this->moving_shape_mt_coords);
                update_vert_coords_of_moving_shape();
                break;
            default:
                break;
        }
    }
}