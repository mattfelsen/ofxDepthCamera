//
//  KinectV2.cpp
//  ofxDepthCamera
//
//  Created by Matt Felsen on 12/28/15.
//
//

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
	maxDepth = 8 * 1000;
}

ofxKinectV2& KinectV2::getSensor() {
	return kinect;
}

void KinectV2::setup(string serial) {
	kinect.open(serial);
}

void KinectV2::setup(unsigned int deviceId) {
	kinect.open(deviceId);
}

void KinectV2::close() {
	kinect.close();
}

void KinectV2::update() {
	kinect.update();
	bNewFrame = kinect.isFrameNew();

	// there is a new frame and we are connected
	if (bNewFrame) {
		depthPixels = kinect.getDepthPixels();
		colorImage.setFromPixels(kinect.getRgbPixels());
	}
}

ofVec3f KinectV2::getWorldCoordinateAt(int x, int y) {
	// TODO Add support for depth -> world mapping once ofxKinectV2 supports it
	return ofVec3f::zero();
}

#endif
