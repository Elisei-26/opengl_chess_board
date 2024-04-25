#pragma once
#include <vector>
#include "Shapes.hpp"

namespace opengles_workspace 
{
    class Bar : public Shapes {
        private:
            std::vector<short> _mt_coords_of_shape = {2, 10, 2, 9, 2, 11, 2, 12};

        public:
            Bar(short moving_shape_mt_coords[]);
            std::vector<short> get_mt_coords_of_shape() const;
            virtual void rotate_shape(short mt[22][22], short moving_shape_mt_coords[8]);
    };
}