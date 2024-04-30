#pragma once

namespace opengles_workspace 
{
    class Shapes
    {
        public:
            virtual void rotate_shape(short mt[22][22], short moving_shape_mt_coords[8]) = 0;
    };
}