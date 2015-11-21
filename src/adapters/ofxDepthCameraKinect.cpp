/*
*  ofxDepthCameraKinect.cpp
*  ofxDepthCamera
*
*  Created by Jim George on 3/13/12 for ofxDepthKit
*  Copyright 2014 FlightPhase. All rights reserved.
*  Modified by Matt Felsen 10/2015
*
*/

#include "ofxDepthCameraKinect.h"

#ifdef OFX_DEPTH_CAMERA_KINECT

ofxDepthCameraKinect::ofxDepthCameraKinect() {
	fr = 30;
	depthWidth = 640;
	depthHeight = 480;
	colorWidth = 640;
	colorHeight = 480;
}

ofxKinect& ofxDepthCameraKinect::getSensor() {
	return kinect;
}

void ofxDepthCameraKinect::setup(int deviceId, bool useColor) {
	ofxBaseDepthCamera::setup();

	bDeviceFound = kinect.init(!useColor, true); // shows infrared instead of RGB video image
	bDeviceFound &= kinect.open();
}

void ofxDepthCameraKinect::close() {
	kinect.close();
}

void ofxDepthCameraKinect::update() {
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

ofVec3f ofxDepthCameraKinect::getWorldCoordinateAt(int x, int y) {
	return kinect.getWorldCoordinateAt(x, y);
}

int ofxDepthCameraKinect::maxDepth() {
	return 10000; //taken from looking into how ofxKinect calculates it's look up tables.
}

#endif
