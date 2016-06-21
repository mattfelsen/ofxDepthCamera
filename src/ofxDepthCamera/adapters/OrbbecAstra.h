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
		ofxOrbbecAstra& getSensor();

		void setup(bool useColor = false);
		void close();
		void update();

		ofVec3f getWorldCoordinateAt(int x, int y);

	protected:
		ofxOrbbecAstra astra;
	};
}

#endif
