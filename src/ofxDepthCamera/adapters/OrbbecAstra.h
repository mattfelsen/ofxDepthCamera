/*
*  OrbbecAstra.h
*  ofxDepthCamera
*
*  Created by Matt Felsen on 11/3/15
*
*/

#pragma once

#include "ofMain.h"
#include "ofxDepthCamera.h"

#ifdef OFX_DEPTH_CAMERA_ORBBEC_ASTRA
#include "ofxOrbbecAstra.h"

namespace ofxDepthCam {
	class OrbbecAstra : public Base {

	public:
		OrbbecAstra();
		~OrbbecAstra();

		void setup();
		void close();
		void update();

		int maxDepth();
		ofVec3f getWorldCoordinateAt(int x, int y);

	protected:
		ofxOrbbecAstra astra;
	};
}

#else

namespace ofxDepthCam {
	class OrbbecAstra : public Base {
	public:
	};
}

#endif
