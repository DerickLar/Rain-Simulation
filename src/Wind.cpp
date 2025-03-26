#include "Wind.hpp"

float wind_power = 0.1; // Strength of wind on water particles
float wind_dir_xy = 1;  // Direction wind is coming from in the xy plane
float wind_dir_z = 1;   // Direction wind is coming from the z plane (Horizontal or Verticle Wind)

// Draw rain effected by the current wind
void draw_windy_rain() {
    float x_pos, y_pos, z_pos, radius = 1.0;
    ofMesh sphere = ofMesh::sphere(radius, 16, OF_PRIMITIVE_TRIANGLES); // Create a sphere mesh

    // Wind effect on each x,y,z coordinate
    float wind_x = wind_power * cos(wind_dir_xy) * cos(wind_dir_z);
    float wind_y = wind_power * sin(wind_dir_z);
    float wind_z = wind_power * sin(wind_dir_xy) * cos(wind_dir_z);

    // Draw Each Particle effected by wind
    for (int i = 0; i < MAX_PARTICLES; i += 1) {
        x_pos = particle_system[i].x_coordinate;
        y_pos = particle_system[i].y_coordinate;
        z_pos = particle_system[i].z_coordinate - 40;

        // Push and pop matrix to isolate transformations for each particle
        ofPushMatrix();
        {
            // Translate to the particle's position
            ofTranslate(x_pos + wind_x * 3.1f - 1.5f, y_pos + wind_y + 7.8, z_pos + 3.1f - 1.5f);

            // Calculate rotation angle based on wind direction
            float angle = atan2(wind_y, wind_x) * RAD_TO_DEG;  // Angle in degrees for xy plane rotation
            float tilt = atan2(wind_z, sqrt(wind_x * wind_x + wind_y * wind_y)) * RAD_TO_DEG;  // Angle for z tilt

            // Apply rotation to the particle to align it with the wind direction
            ofRotateDeg(angle, 0, 0, 1); // Rotate in the xy plane
            ofRotateDeg(tilt, 1, 0, 0);  // Apply tilt based on the z component of the wind

            // Stretch the particle vertically to give it a raindrop-like appearance
            float stretch_factor = ofMap(wind_power, 0.1, 3.0, 1.5, 3.5); // Stretch increases with wind power
            if (abs(wind_dir_z) > 1.0) {
                stretch_factor *= 1.5; // Increase stretch more for vertical winds
            }

            // Apply the scaling factor
            ofScale(1.0, stretch_factor, 1.0); // Scale along the y-axis (vertical)

            sphere.draw();
        }
        ofPopMatrix();

        // Update position with random descent and wind influence
        if (descent > 0) {
            particle_system[i].y_coordinate += (fmod(rand(), descent));
            particle_system[i].x_coordinate += (fmod(rand(), descent)) * wind_x;
            particle_system[i].z_coordinate += (fmod(rand(), descent)) * wind_z;
        }

        // Re-initilize particle when it reaches the ground
        if (particle_system[i].y_coordinate >= rand() % (ofGetHeight() * 10)){
            initialize_particle(i);
        }
    }
}