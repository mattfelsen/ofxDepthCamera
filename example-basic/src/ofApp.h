#pragma once

#include "ofMain.h"
#include "ofxDepthCamera.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void dragEvent(ofDragInfo dragInfo);

	ofxDepthCamera device;

};
