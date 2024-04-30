#pragma once
#include <vector>
#include "Shapes.hpp"

namespace opengles_workspace 
{
    class L_Right : public Shapes {
        private:
            std::vector<short> _mt_coords_of_shape = {2, 10, 2, 11, 3, 11, 2, 9};
            
        public:
            L_Right(short moving_shape_mt_coords[]);
            std::vector<short> get_mt_coords_of_shape() const;
            virtual void rotate_shape(short mt[22][22], short moving_shape_mt_coords[8]);
    };
}