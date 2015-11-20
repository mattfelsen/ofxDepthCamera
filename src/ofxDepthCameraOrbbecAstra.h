/*
*  ofxDepthCameraOrbbecAstra.h
*  ofxDepthCamera
*
*  Created by Matt Felsen on 11/3/15
*
*/

#pragma once

#define OFX_DEPTH_CAMERA_ORBBEC_ASTRA

#include "ofMain.h"
#include "ofxBaseDepthCamera.h"

#ifdef OFX_DEPTH_CAMERA_ORBBEC_ASTRA
#include "ofxOrbbecAstra.h"

class ofxDepthCameraOrbbecAstra : public ofxBaseDepthCamera {
public:
	ofxDepthCameraOrbbecAstra();
	~ofxDepthCameraOrbbecAstra();

	void setup();
	void close();
	void update();

	int maxDepth();
	ofVec3f getWorldCoordinateAt(int x, int y);

protected:
    ofxOrbbecAstra astra;
    
};

#else

class ofxDepthCameraOrbbecAstra: public ofxBaseDepthCamera {
};

#endif