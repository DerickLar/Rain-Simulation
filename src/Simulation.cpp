#include "Simulation.hpp"


float descent = 20.0; // Default Decent Speed
bool is_raining = true; // Raining is by default true
bool is_windy = false; // Windy is must be toggeld on 
Particles particle_system[MAX_PARTICLES]; // MAX number of particles in the simulation

//Spawn a rain particle
void initialize_particle(int i) {
    particle_system[i].x_coordinate = ofRandom(0, ofGetWidth());
    particle_system[i].y_coordinate = -30.0;
    particle_system[i].z_coordinate = ofRandom(-100.0, 100.0);
}

// Spawn all particles in the simulation
void initialize() {
    // Initialize particles
    for (int i = 0; i < MAX_PARTICLES; i++) {
        initialize_particle(i);
    }
}

