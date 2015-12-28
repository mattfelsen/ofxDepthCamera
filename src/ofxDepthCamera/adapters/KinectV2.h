//
//  KinectV2.hpp
//  ofxDepthCamera
//
//  Created by Matt Felsen on 12/28/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxDepthCamera.h"

#ifdef OFX_DEPTH_CAMERA_KINECT_V2
#include "ofxKinectV2.h"

namespace ofxDepthCam {
	class KinectV2 : public Base {

	public:
		KinectV2();
		ofxKinectV2& getSensor();

		void setup(string serial);
		void setup(unsigned int deviceId = 0);
		void close();
		void update();

		ofVec3f getWorldCoordinateAt(int x, int y);

	protected:
		ofxKinectV2 kinect;
	};
}

#endif
