//
//  MultiKinectV2.hpp
//  ofxDepthCamera
//
//  Created by Matt Felsen on 12/28/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxDepthCamera.h"

#ifdef OFX_DEPTH_CAMERA_MULTI_KINECT_V2
#include "ofxMultiKinectV2.h"

namespace ofxDepthCam {
	class MultiKinectV2 : public Base {

	public:
		MultiKinectV2();
		ofxMultiKinectV2& getSensor();

		void setup(bool useColor = false, int deviceIndex = 0, int oclDeviceIndex = -1);
		void close();
		void update();

		ofVec3f getWorldCoordinateAt(int x, int y);

	protected:
		ofxMultiKinectV2 kinect;
	};
}

#endif
