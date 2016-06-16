/*
*  KinectForWindows2.h
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

#ifdef OFX_DEPTH_CAMERA_KFW2
#include "ofxKinectForWindows2.h"

namespace ofxDepthCam {
	class KinectForWindows2 : public Base {

	public:
		KinectForWindows2();
		ofxKFW2::Device& getSensor();

		void setup(int flags = OFXDEPTHCAMERA_MASK_DEPTH);
		void close();
		void update();

		ofVec3f getWorldCoordinateAt(int x, int y);

	protected:
		ofxKFW2::Device kinect;
		ICoordinateMapper* mapper;

		vector<ofVec3f> cachedCoords;
		bool coordsDirty;
	};
}

#endif
