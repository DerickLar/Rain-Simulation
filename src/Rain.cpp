#include "ofMain.h"
#include "Rain.hpp"

void draw_rain() {
    float x_pos, y_pos, z_pos, radius = 1.0;
    ofMesh sphere = ofMesh::sphere(radius, 16, OF_PRIMITIVE_TRIANGLES); // Create a sphere mesh

    // Draw rain particles
    for (int i = 0; i < MAX_PARTICLES; i += 1) {
        x_pos = particle_system[i].x_coordinate;
        y_pos = particle_system[i].y_coordinate;
        z_pos = particle_system[i].z_coordinate - 40.0;

        // Draw Rain Drops
        ofPushMatrix();
        {
            // Translate to the particle's position
            ofTranslate(x_pos, y_pos + 7.8, z_pos);

            // Stretch the particle vertically to give it a raindrop-like appearance
            float stretch_factor = ofRandom(1.0, 2.5); // Stretch factor
            ofScale(1.0, stretch_factor, 1.0); // Scale along the y-axis (vertical)

            ofRotateDeg(ofRandom(360), 0, 1, 0);

            // Draw the sphere
            sphere.draw();
        }
        ofPopMatrix();


        //Adjust particle speed
        if (descent < 0) {
            particle_system[i].y_coordinate += 1;
            particle_system[i].x_coordinate += 1;
        }
        else {
            particle_system[i].y_coordinate += (fmod(rand(), descent));
        }

        // Re-initilize particle when it reaches the ground
        if (particle_system[i].y_coordinate >= (rand() % (ofGetHeight() * 10))) {
            initialize_particle(i);
        }
    }
}