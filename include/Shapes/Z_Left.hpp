#pragma once
#include <vector>
#include "Shapes.hpp"

namespace opengles_workspace 
{
    class Z_Left : public Shapes {
        private:
            std::vector<short> _mt_coords_of_shape = {2, 10, 2, 9, 3, 10, 3, 11};
            
        public:
            Z_Left(short moving_shape_mt_coords[]);
            std::vector<short> get_mt_coords_of_shape() const;
            virtual void rotate_shape(short mt[22][22], short moving_shape_mt_coords[8]);
    };
}