//
//  MultiKinectV2.cpp
//  ofxDepthCamera
//
//  Created by Matt Felsen on 12/28/15.
//
//

#include "MultiKinectV2.h"

#ifdef OFX_DEPTH_CAMERA_MULTI_KINECT_V2

using namespace ofxDepthCam;

MultiKinectV2::MultiKinectV2() {
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

ofxMultiKinectV2& MultiKinectV2::getSensor() {
	return kinect;
}

void MultiKinectV2::setup(bool enableColor, int deviceIndex, int oclDeviceIndex) {
	kinect.open(enableColor, false, deviceIndex, oclDeviceIndex);
	kinect.start();
}

void MultiKinectV2::close() {
	kinect.close();
}

void MultiKinectV2::update() {
	kinect.update();
	bNewFrame = kinect.isFrameNew();

	// there is a new frame and we are connected
	if (bNewFrame) {
		depthPixels = kinect.getDepthPixelsRef();
		colorImage.setFromPixels(kinect.getColorPixelsRef());
	}
}

ofVec3f MultiKinectV2::getWorldCoordinateAt(int x, int y) {
	return kinect.getWorldCoordinateAt(x, y);
}

#endif
