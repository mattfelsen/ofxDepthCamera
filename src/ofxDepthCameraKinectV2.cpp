/*
*  ofxDepthCameraKinectV2.cpp
*  ofxDepthCamera
*
*  Originally created by Jim George on 5/15/14 for ofxDepthKit
*  Modified by Matt Felsen 10/2015
*  Copyright 2014 FlightPhase. All rights reserved.
*
*/

#include "ofxDepthCameraKinectV2.h"

void ofxDepthCameraKinectV2::setup(int deviceId, bool useColor) {

	coordsDirty = true;

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

void ofxDepthCameraKinectV2::close() {
	if (kinect.isOpen()) {
		kinect.close();
	}
}

void ofxDepthCameraKinectV2::update() {
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

ofVec3f ofxDepthCameraKinectV2::getWorldCoordinateAt(int x, int y) {
	if (coordsDirty) {
		int w = 512;
		int h = 424;
		vector<ofPoint> pts;
		pts.resize(w * h);
		mapper->MapDepthFrameToCameraSpace(w*h, (UINT16*)depthPixels.getData(), w*h, (CameraSpacePoint*)pts.data());
		cachedCoords = pts;
		coordsDirty = false;
	}

	return cachedCoords[int(y) * 640 + int(x)]; //kinect.mapDepthToSkeleton(ofPoint(x, y) );
}

int ofxDepthCameraKinectV2::maxDepth() {
	// Kinect for Windows 2.0 SDK says max depth is 8 meters
	// Units in the DepthFrame are in millimeters
	// https://msdn.microsoft.com/en-us/library/windowspreview.kinect.depthframe.aspx
	return 8 * 1000;
}