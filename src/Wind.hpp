#ifndef Wind_hpp
#define Wind_hpp

#include "ofMain.h"
#include "Simulation.hpp"
#include <stdio.h>

extern float wind_power; // Strength of wind on water particles
extern float wind_dir_xy; // Direction wind is coming from in the xy plane
extern float wind_dir_z; // Direction wind is coming from the z plane (Horizontal or Verticle Wind)

void draw_windy_rain();     // Function to draw windy rain

#endif