/*
*  Kinect.cpp
*  ofxDepthCamera
*
*  Created by Jim George on 3/13/12 for ofxDepthKit
*  Copyright 2014 FlightPhase. All rights reserved.
*  Modified by Matt Felsen 10/2015
*
*/

#include "Kinect.h"

#ifdef OFX_DEPTH_CAMERA_KINECT

using namespace ofxDepthCam;

Kinect::Kinect() {
	depthWidth = 640;
	depthHeight = 480;
	colorWidth = 640;
	colorHeight = 480;

	frameRate = 30;

	// Max range is sorted of hinted to be 8m in these docs, so give a bit
	// of extra padding..
	// https://msdn.microsoft.com/en-us/library/hh973078.aspx#Depth_Ranges
	maxDepth = 9 * 1000;
}

ofxKinect& Kinect::getSensor() {
	return kinect;
}

void Kinect::setup(int deviceId, bool useColor) {
	// If useColor == true, we need to...
	// - tell ofxKinect to use color intead of IR (1st arg)
	// - enable the video stream (2nd arg)
	// If useColor == false...
	// - first arg doesn't matter
	// - second arg == false disables the video stream
	// Third arg disables ofxKinect textures since we use our own
	kinect.init(!useColor, useColor, false);
	kinect.open();
}

void Kinect::close() {
	kinect.close();
}

void Kinect::update() {
	kinect.update();
	bNewFrame = kinect.isFrameNew();

	if (kinect.isFrameNewDepth()) {
		depthPixels = kinect.getRawDepthPixels();
	}

	if (kinect.isFrameNewVideo()) {
		colorImage.setFromPixels(kinect.getPixels());
	}
}

ofVec3f Kinect::getWorldCoordinateAt(int x, int y) {
	return kinect.getWorldCoordinateAt(x, y);
}

#endif
