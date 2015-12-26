#pragma once

#include "ofMain.h"
#include "ofxDepthCamera.h"
#include "ofxDepthCamera/Sender.h"

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	ofxDepthCamera device;
	ofxDepthCam::Sender sender;
	
};
