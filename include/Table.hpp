#pragma once
#include "../include/Shapes.hpp"

namespace opengles_workspace 
{
    class Table : Shapes
    {
        protected:
            std::vector<float> vertices = { //0.0f
                -0.1f, 0.8f, 0.0f, // square top left
                0.0f, 0.8f, 0.0f,
                -0.1f,  0.9f, 0.0f,
                -0.1f,  0.9f, 0.0f,
                0.0f, 0.8f, 0.0f,
                0.0f, 0.9f, 0.0f,

                0.0f, 0.8f, 0.0f, // square top right
                0.1f, 0.8f, 0.0f,
                0.0f,  0.9f, 0.0f,
                0.0f,  0.9f, 0.0f,
                0.1f, 0.8f, 0.0f,
                0.1f, 0.9f, 0.0f,

                -0.1f, 0.7f, 0.0f, // square down left
                0.0f, 0.7f, 0.0f,
                -0.1f,  0.8f, 0.0f,
                -0.1f,  0.8f, 0.0f,
                0.0f, 0.7f, 0.0f,
                0.0f, 0.8f, 0.0f,

                0.0f, 0.7f, 0.0f, // square down right
                0.1f, 0.7f, 0.0f,
                0.0f,  0.8f, 0.0f,
                0.0f,  0.8f, 0.0f,
                0.1f, 0.7f, 0.0f,
                0.1f, 0.8f, 0.0f
            };

            float vert_coords_generated_shape[72] = { //0.0f
                -0.1f, 0.8f, 0.0f, // square top left
                0.0f, 0.8f, 0.0f,
                -0.1f,  0.9f, 0.0f,
                -0.1f,  0.9f, 0.0f,
                0.0f, 0.8f, 0.0f,
                0.0f, 0.9f, 0.0f,

                0.0f, 0.8f, 0.0f, // square top right
                0.1f, 0.8f, 0.0f,
                0.0f,  0.9f, 0.0f,
                0.0f,  0.9f, 0.0f,
                0.1f, 0.8f, 0.0f,
                0.1f, 0.9f, 0.0f,

                -0.1f, 0.7f, 0.0f, // square down left
                0.0f, 0.7f, 0.0f,
                -0.1f,  0.8f, 0.0f,
                -0.1f,  0.8f, 0.0f,
                0.0f, 0.7f, 0.0f,
                0.0f, 0.8f, 0.0f,

                0.0f, 0.7f, 0.0f, // square down right
                0.1f, 0.7f, 0.0f,
                0.0f,  0.8f, 0.0f,
                0.0f,  0.8f, 0.0f,
                0.1f, 0.7f, 0.0f,
                0.1f, 0.8f, 0.0f
            };
            float move_shape_y_status;
            float axis_y_speed;

            short moving_shape_mt_coords[8] = {2, 10, 2, 11, 3, 10, 3, 11};
            short mt_game_status[22][22] = {};
            short which_shape;
            short score;
            short nr_frames;
            short one_shape_nr_vertices;
            short vertices_length;
            
        public:
            Table();
            std::vector<float> get_vertices_array();
            void set_nr_frames(int nr_fps);
            void set_axis_y_speed();
            float get_axis_y_speed();
            short get_vertices_length();
            bool game_over();
            short get_score();
            void delete_line_from_mt(short line);
            void move_mt_upper_lines_down(short line);
            void check_mt_lines_completed();
            void delete_excess_of_vertices(short new_vert_length);
            void calculate_vert_coords_using_mt();
            void update_moving_shape_mt_coords(short new_coords[]);
            void update_mt_game_status(short coords_of_landed_shape[]);
            void calculate_new_shape_vert_coords(short mt_coords[]);
            void update_vert_coords_of_moving_shape();
            void add_new_shape_vert_coords_in_vertices_vect();
            bool sth_under_falling_shape();
            void move_shape_down(float axis_y_speed);
            void move_shape_to_right();
            void move_shape_to_left();
            void rotate_shape();
    };
}