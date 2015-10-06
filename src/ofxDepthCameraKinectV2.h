/*
*  ofxDepthCameraKinectV2.h
*  ofxDepthCamera
*
*  Originally created by Jim George on 3/13/12 for ofxDepthKit
*  Modified by Matt Felsen 10/2015
*  Copyright 2012 FlightPhase. All rights reserved.
*
*/

#pragma once

#include "ofMain.h"
#include "ofxBaseDepthCamera.h"
#include "ofxKinectForWindows2.h"

class ofxDepthCameraKinectV2: public ofxBaseDepthCamera {
public:
	void setup(int deviceId = 0, bool useColor = false);
	void close();
	void update();

	int maxDepth();
	ofVec3f getWorldCoordinateAt(int x, int y);
	

protected:
	ofxKFW2::Device kinect;
	ICoordinateMapper* mapper;

	vector<ofVec3f> cachedCoords;
	bool coordsDirty;
};