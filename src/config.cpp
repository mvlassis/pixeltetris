#include "config.hpp"

namespace config
{
   double resolution_scaling = 2;                                                               // Default value; Corresponds to 720p
   double available_resolution_scalings[] = {0.25, 0.5, 1, 1.5, 2, 3};                          // Resolution scalings available in the options
   bool ghost_piece_enabled = true;
}
