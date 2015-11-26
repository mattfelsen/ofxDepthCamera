/*
*  Kinect.h
*  ofxDepthCamera
*
*  Created by Jim George on 3/13/12 for ofxDepthKit
*  Copyright 2012 FlightPhase. All rights reserved.
*  Modified by Matt Felsen 10/2015
*
*/

#pragma once

#include "ofMain.h"
#include "ofxDepthCamera.h"

#ifdef OFX_DEPTH_CAMERA_KINECT
#include "ofxKinect.h"

namespace ofxDepthCam {
	class Kinect : public Base {

	public:
		Kinect();
		ofxKinect& getSensor();

		void setup(int deviceId = 0, bool useColor = false);
		void close();
		void update();

		int maxDepth();
		ofVec3f getWorldCoordinateAt(int x, int y);

	protected:
		ofxKinect kinect;

	};
}

#endif
