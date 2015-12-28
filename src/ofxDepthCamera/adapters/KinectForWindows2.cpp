/*
*  KinectForWindows2.cpp
*  ofxDepthCamera
*
*  Created by Jim George on 5/15/14 for ofxDepthKit
*  Copyright 2014 FlightPhase. All rights reserved.
*  Modified by Matt Felsen 10/2015
*
*/

#include "KinectForWindows2.h"

#ifdef OFX_DEPTH_CAMERA_KFW2

using namespace ofxDepthCam;

KinectForWindows2::KinectForWindows2() {
	depthWidth = 512;
	depthHeight = 424;
	colorWidth = 1920;
	colorHeight = 1080;

    frameRate = 30;

    // Kinect for Windows 2.0 SDK says max depth is 8 meters
    // Units in the DepthFrame are in millimeters
    // https://msdn.microsoft.com/en-us/library/windowspreview.kinect.depthframe.aspx
    maxDepth = 8 * 1000;
}

ofxKFW2::Device& KinectForWindows2::getSensor() {
	return kinect;
}

void KinectForWindows2::setup(bool useColor) {
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
	kinect.isOpen();
}

void KinectForWindows2::close() {
	if (kinect.isOpen()) {
		kinect.close();
	}
}

void KinectForWindows2::update() {
	kinect.update();
	bNewFrame = kinect.isFrameNew();

	if (bNewFrame) {
		coordsDirty = true;
		depthPixels = kinect.getDepthSource()->getPixels();
	}

	if (kinect.getColorSource()) {
		colorImage.setFromPixels(kinect.getColorSource()->getPixels());
	}
}

ofVec3f KinectForWindows2::getWorldCoordinateAt(int x, int y) {
	if (coordsDirty) {
		mapper->MapDepthFrameToCameraSpace(cachedCoords.size(), (UINT16*) depthPixels.getData(), cachedCoords.size(), (CameraSpacePoint*) cachedCoords.data());
		coordsDirty = false;
	}

	return cachedCoords[int(y) * depthWidth + int(x)];
}

#endif
