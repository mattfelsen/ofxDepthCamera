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
#include "ofxBaseDepthCamera.h"
#include "ofxDepthCameraUtils.h"

#include "ofxDepthCameraKinect.h"
#include "ofxDepthCameraKinectV2.h"
#include "ofxDepthCameraOrbbecAstra.h"

class ofxDepthCamera {
public:

	enum Type {
		Kinect,
		KinectV2,
		OrbbecAstra
	};

	ofxDepthCamera();
	~ofxDepthCamera();

	void setup();
	void setType(Type type);
	void setPointer(shared_ptr<ofxBaseDepthCamera> pointer);

	void update();

	ofShortPixels& getRawDepth();
	ofImage& getDepthImage();
	ofImage& getColorImage();

protected:
	shared_ptr<ofxBaseDepthCamera> camera;
};