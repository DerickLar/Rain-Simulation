#include "ofApp.h"
#include "Simulation.hpp"
#include "Rain.hpp"
#include "Wind.hpp"
#include "ofMath.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableDepthTest();
    ofEnableLighting();
    ofSetVerticalSync(true);

    // Initialize the light
    light.setDiffuseColor(ofFloatColor(1.0, 1.0, 1.0));   // White diffuse light
    light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));  // White specular highlights
    light.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 500); // Place light above the scene

    // Initialize material properties
    material.setDiffuseColor(ofFloatColor(0.2, 0.5, 1.0, 0.3));  // Slightly blue diffuse color
    material.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0, 0.3));  // White specular highlights
    material.setShininess(64);

    // Set up the control panel
    control_panel.setup("Parameters");
    control_panel.add(rain.setup("Rain", true, 20, 20));
    control_panel.add(descent_speed.setup("Descent Speed", 20, 0.1, 100));
    control_panel.add(wind.setup("Wind", false, 20, 20));
    control_panel.add(wind_strength.setup("Wind Strength", 0.1, 0.01, 3));
    control_panel.add(wind_xy_direction.setup("Wind XY Direction", 1, 0.1, 2*PI));
    control_panel.add(wind_z_direction.setup("Wind Z Direction", 1, 0.1, PI/2));

    // Initialize all particles
    initialize();
    ofBackground(ofColor::gray);

    // Setup the camera
    cam_pos = ofVec3f(-12, -0.2, 0);
    camera.lookAt(cam_pos);
    camera.rotate(180, camera.getXAxis());
}

//--------------------------------------------------------------
void ofApp::update(){
    is_raining = rain;
    is_windy = wind;
    descent = descent_speed;
    wind_power = wind_strength;
    wind_dir_xy = wind_xy_direction;
    wind_dir_z = wind_z_direction;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    float cameraSpeed = 50.0;
    float cameraRotate = 1.0;
    switch (key) {
        case 'w':
            camera.move(cameraSpeed, 0, 0);
            break;
        case 's':
            camera.move(-cameraSpeed, 0, 0);
            break;
        case 'a':
            camera.move(0, 0, cameraSpeed);
            break;
        case 'd':
            camera.move(0, 0, -cameraSpeed);
            break;
        case 'q':
            camera.move(0, cameraSpeed, 0);
            break;
        case 'e':
            camera.move(0, -cameraSpeed, 0);
            break;
        case OF_KEY_UP:
            camera.rotate(cameraRotate, camera.getSideDir());
            break;
        case OF_KEY_DOWN:
            camera.rotate(-cameraRotate, camera.getSideDir());
            break;
        case OF_KEY_LEFT:
            camera.rotate(cameraRotate, camera.getUpDir());
            break;
        case OF_KEY_RIGHT:
            camera.rotate(-cameraRotate, camera.getUpDir());
            break;
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    camera.begin();
    light.enable();
    material.begin();
    ofSetHexColor(0xff0000);
    draw_rainfall();
    material.end();
    light.disable();
    ofDisableLighting();
    camera.end();
    ofDisableDepthTest();
    control_panel.draw();
    ofSetHexColor(0x32cd32);
    ofDrawBitmapString("Camera Translation: WASD", ofGetWidth() - 300, 17);
    ofDrawBitmapString("Camera Elevation: Q - down and E - up", ofGetWidth() - 300, 28);
    ofDrawBitmapString("Camera Rotation: Arrow Keys", ofGetWidth() - 300, 39);
    ofDrawBitmapString("OR use mouse to move around", ofGetWidth() - 300, 52);
}

//--------------------------------------------------------------
void ofApp::draw_rainfall() {
    //Determine which rain to draw, windy or not
    if (is_raining) {
        if (is_windy) 
            draw_windy_rain();
        else
            draw_rain();
    }
}
