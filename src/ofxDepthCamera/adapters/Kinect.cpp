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
	fr = 30;
	depthWidth = 640;
	depthHeight = 480;
	colorWidth = 640;
	colorHeight = 480;
}

ofxKinect& Kinect::getSensor() {
	return kinect;
}

void Kinect::setup(int deviceId, bool useColor) {
	ofxBaseDepthCamera::setup();

	bDeviceFound = kinect.init(!useColor, true); // shows infrared instead of RGB video image
	bDeviceFound &= kinect.open();
}

void Kinect::close() {
	kinect.close();
}

void Kinect::update() {
	kinect.update();
	// there is a new frame and we are connected
	if (kinect.isFrameNewDepth()) {
		bNewFrame = true;
		bDepthImageDirty = true;
		depthPixels.setFromPixels(kinect.getRawDepthPixels(), kinect.getWidth(), kinect.getHeight(), OF_IMAGE_GRAYSCALE);
	}

	if (kinect.isFrameNewVideo()) {
		colorImage.setFromPixels(kinect.getPixels());
	}
}

ofVec3f Kinect::getWorldCoordinateAt(int x, int y) {
	return kinect.getWorldCoordinateAt(x, y);
}

int Kinect::maxDepth() {
	return 10000; //taken from looking into how ofxKinect calculates it's look up tables.
}

#endif
