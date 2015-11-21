/*
*  ofxDepthCamera.h
*  ofxDepthCamera
*
*  Created by Jim George on 3/13/12 for ofxDepthKit
*  Modified by Matt Felsen 10/2015
*
*/

#pragma once

// Comment any of these in to enable the devices you want
//#define OFX_DEPTH_CAMERA_KINECT
//#define OFX_DEPTH_CAMERA_KINECT_V2
//#define OFX_DEPTH_CAMERA_ORBBEC_ASTRA

#include "ofMain.h"
#include "Base.h"
#include "Utils.h"

#include "adapters/Kinect.h"
#include "adapters/KinectV2.h"
#include "adapters/OrbbecAstra.h"

namespace ofxDepthCamera {

	enum class Type {
		Kinect,
		KinectV2,
		OrbbecAstra
	};

	class Device {
	public:

		Device();
		~Device();

		void setup();
		void setType(Type type);
		void setPointer(shared_ptr<Base> pointer);

		void update();

		ofShortPixels& getRawDepth();
		ofImage& getDepthImage();
		ofImage& getColorImage();

	protected:
		shared_ptr<Base> camera;
	};
	
}