#ifndef Simulation_hpp
#define Simulation_hpp

#include "ofMain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int MAX_PARTICLES = 10000; //For best performance keep under  15,000

extern float descent; // Speed of each particle
extern bool is_raining; // Determine if rain simulation is on
extern bool is_windy;  // Determine if rain is effected by wind

struct Particles {
    float x_coordinate;
    float y_coordinate;
    float z_coordinate;
};

// Particle System
extern Particles particle_system[MAX_PARTICLES];

void initialize_particle(int i); // Initialize a particle
void initialize(); // Initialize the particles

#endif