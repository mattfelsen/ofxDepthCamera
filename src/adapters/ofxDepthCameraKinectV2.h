/*
*  ofxDepthCameraKinectV2.h
*  ofxDepthCamera
*
*  Created by Jim George on 3/13/12 for ofxDepthKit
*  Copyright 2012 FlightPhase. All rights reserved.
*  Modified by Matt Felsen 10/2015
*
*/

#pragma once

#include "ofMain.h"
#include "ofxBaseDepthCamera.h"

#ifdef OFX_DEPTH_CAMERA_KINECTV2
#include "ofxKinectForWindows2.h"

class ofxDepthCameraKinectV2: public ofxBaseDepthCamera {
public:
	ofxDepthCameraKinectV2();
	ofxKFW2::Device& getSensor();

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

#endif