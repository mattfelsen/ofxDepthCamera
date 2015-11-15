/*
*  ofxDepthCameraOrbbecAstra.h
*  ofxDepthCamera
*
*  Created by Matt Felsen on 11/3/15
*
*/

#pragma once

#include "ofMain.h"
#include "ofxBaseDepthCamera.h"
#include "ofxOrbbecAstra.h"

class ofxDepthCameraOrbbecAstra : public ofxBaseDepthCamera {
public:
	ofxDepthCameraOrbbecAstra();
	~ofxDepthCameraOrbbecAstra();

	void setup(int deviceId = 0, bool useColor = false);
	void close();
	void update();

	int maxDepth();
	ofVec3f getWorldCoordinateAt(int x, int y);

protected:
    ofxOrbbecAstra astra;
    
};