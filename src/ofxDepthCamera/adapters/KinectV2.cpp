/*
*  KinectV2.cpp
*  ofxDepthCamera
*
*  Created by Jim George on 5/15/14 for ofxDepthKit
*  Copyright 2014 FlightPhase. All rights reserved.
*  Modified by Matt Felsen 10/2015
*
*/

#include "KinectV2.h"

#ifdef OFX_DEPTH_CAMERA_KINECT_V2

using namespace ofxDepthCam;

KinectV2::KinectV2() {
	depthWidth = 512;
	depthHeight = 424;
	colorWidth = 1920;
	colorHeight = 1080;

    frameRate = 30;

    // Kinect for Windows 2.0 SDK says max depth is 8 meters
    // Units in the DepthFrame are in millimeters
    // https://msdn.microsoft.com/en-us/library/windowspreview.kinect.depthframe.aspx
    return 8 * 1000;
}

ofxKFW2::Device& KinectV2::getSensor() {
	return kinect;
}

void KinectV2::setup(int deviceId, bool useColor) {
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

void KinectV2::close() {
	if (kinect.isOpen()) {
		kinect.close();
	}
}

void KinectV2::update() {
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

ofVec3f KinectV2::getWorldCoordinateAt(int x, int y) {
	if (coordsDirty) {
		mapper->MapDepthFrameToCameraSpace(cachedCoords.size(), (UINT16*) depthPixels.getData(), cachedCoords.size(), (CameraSpacePoint*) cachedCoords.data());
		coordsDirty = false;
	}

	return cachedCoords[int(y) * depthWidth + int(x)];
}

#endif
