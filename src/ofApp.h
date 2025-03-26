#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    ofEasyCam camera;
    ofVec3f cam_pos;
    ofBoxPrimitive flash_box;
    ofxPanel control_panel;
    ofxToggle rain;
	ofxToggle wind;
    ofxFloatSlider descent_speed;
	ofxFloatSlider wind_strength;
	ofxFloatSlider wind_xy_direction;
	ofxFloatSlider wind_z_direction;
	ofLight light;
	ofMaterial material;

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);

        void draw_rainfall();
};
