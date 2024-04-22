#pragma once
#include <vector>
#include <iostream>
#include "RotateShapes.hpp"
#include "Shapes.hpp"

namespace opengles_workspace 
{
    class Table
    {
        protected:
            std::vector<float> _vertices = { //0.0f
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

            float _vert_coords_generated_shape[72] = { //0.0f
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
            float _move_shape_y_status = 0.0f;
            float _axis_y_speed = 0.0f;

            short _mt_lines = 22;
            short _leng_shape_mt_coords = 8;
            short _moving_shape_mt_coords[8] = {2, 10, 2, 11, 3, 10, 3, 11};
            short _mt_game_status[22][22] = {};
            short _which_shape = 1;
            short _score = 0;
            short _nr_frames = 0;
            short _one_shape_nr_vertices = 72;
            short _vertices_length = this->_one_shape_nr_vertices;
            Shapes _shapes;
            RotateShapes _rotate_shapes = RotateShapes();
            
        public:
            Table();
            void set_nr_frames(int nr_fps);
            void set_axis_y_speed();
            std::vector<float> get_vertices_array() const;
            float get_axis_y_speed() const;
            short get_vertices_length() const;
            short get_score() const;
            bool game_over() const;
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
            bool sth_under_falling_shape() const;
            void generate_the_new_shape();
            void move_shape_down(float axis_y_speed);
            void move_shape_to_right();
            void move_shape_to_left();
            void rotate_shape();
    };
}