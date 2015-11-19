/*
*  ofxDepthCameraKFW2.cpp
*  ofxDepthCamera
*
*  Created by Jim George on 5/15/14 for ofxDepthKit
*  Copyright 2014 FlightPhase. All rights reserved.
*  Modified by Matt Felsen 10/2015
*
*/

#include "ofxDepthCameraKFW2.h"
#ifdef OFX_DEPTH_CAMERA_KFW2

ofxDepthCameraKFW2::ofxDepthCameraKFW2() {
	fr = 30;
	depthWidth = 512;
	depthHeight = 424;
	colorWidth = 1920;
	colorHeight = 1080;
}

ofxKFW2::Device& ofxDepthCameraKFW2::getSensor() {
	return kinect;
}

void ofxDepthCameraKFW2::setup(int deviceId, bool useColor) {
	ofxBaseDepthCamera::setup();

	coordsDirty = true;
	cachedCoords.resize(depthWidth * depthHeight);

	kinect.open();
	kinect.initInfraredSource();
	kinect.initDepthSource();

	if (useColor) {
		kinect.initColorSource();
	}

	kinect.getSensor()->get_CoordinateMapper(&mapper);

	//simple start
	bDeviceFound = kinect.isOpen();

}

void ofxDepthCameraKFW2::close() {
	if (kinect.isOpen()) {
		kinect.close();
	}
}

void ofxDepthCameraKFW2::update() {
	kinect.update();

	// there is a new frame and we are connected
	if (kinect.getDepthSource()->isFrameNew()) {
		coordsDirty = true;
		bNewFrame = true;
		bDepthImageDirty = true;

		depthPixels = kinect.getDepthSource()->getPixels();
		depthPixels.mirror(false, true);
		depthImage.setFromPixels(depthPixels);

		rawIRImage.setFromPixels(kinect.getInfraredSource()->getPixels());
		rawIRImage.mirror(false, true);
	}

	if (kinect.getColorSource()) {
		colorImage.setFromPixels(kinect.getColorSource()->getPixels());
	}
}

ofVec3f ofxDepthCameraKFW2::getWorldCoordinateAt(int x, int y) {
	if (coordsDirty) {
		mapper->MapDepthFrameToCameraSpace(cachedCoords.size(), (UINT16*) depthPixels.getData(), cachedCoords.size(), (CameraSpacePoint*) cachedCoords.data());
		coordsDirty = false;
	}

	return cachedCoords[int(y) * depthWidth + int(x)];
}

int ofxDepthCameraKFW2::maxDepth() {
	// Kinect for Windows 2.0 SDK says max depth is 8 meters
	// Units in the DepthFrame are in millimeters
	// https://msdn.microsoft.com/en-us/library/windowspreview.kinect.depthframe.aspx
	return 8 * 1000;
}

#endif