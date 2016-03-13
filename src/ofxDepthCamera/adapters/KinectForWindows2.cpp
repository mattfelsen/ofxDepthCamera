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

	bodyIndexWidth = 512;
	bodyIndexHeight = 424;

	frameRate = 30;

	availableFlags = OFXDEPTHCAMERA_MASK_DEPTH | OFXDEPTHCAMERA_MASK_COLOR | OFXDEPTHCAMERA_MASK_BODYINDEX | OFXDEPTHCAMERA_MASK_MESH;

    // Kinect for Windows 2.0 SDK says max depth is 8 meters
    // Units in the DepthFrame are in millimeters
    // https://msdn.microsoft.com/en-us/library/windowspreview.kinect.depthframe.aspx
    maxDepth = 8 * 1000;
}

ofxKFW2::Device& KinectForWindows2::getSensor() {
	return kinect;
}

void KinectForWindows2::setup(int flags) {
	coordsDirty = true;
	cachedCoords.resize(depthWidth * depthHeight);

	kinect.open();
	kinect.initInfraredSource();

	enabledFlags = 0;
	if ((flags & OFXDEPTHCAMERA_MASK_DEPTH) && isDepthAvailable()) {
		kinect.initDepthSource();
		enabledFlags |= OFXDEPTHCAMERA_MASK_DEPTH;
	}
	if ((flags & OFXDEPTHCAMERA_MASK_COLOR) && isColorAvailable()) {
		kinect.initColorSource();
		enabledFlags |= OFXDEPTHCAMERA_MASK_COLOR;
	}
	if ((flags & OFXDEPTHCAMERA_MASK_BODYINDEX) && isBodyIndexAvailable()) {
		kinect.initBodyIndexSource();
		enabledFlags |= OFXDEPTHCAMERA_MASK_BODYINDEX;
	}
	if ((flags & OFXDEPTHCAMERA_MASK_MESH) && isMeshAvailable()) {
		enabledFlags |= OFXDEPTHCAMERA_MASK_MESH;
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

		if (isDepthEnabled()) {
			depthPixels = kinect.getDepthSource()->getPixels();
		}
		if (isColorEnabled()) {
			colorPixels = kinect.getColorSource()->getPixels();
		}
		if (isBodyIndexEnabled()) {
			bodyIndexPixels = kinect.getBodyIndexSource()->getPixels();
		}
		if (isMeshEnabled()) {
			mesh = kinect.getDepthSource()->getMesh(true, ofxKFW2::Source::Depth::PointCloudOptions::ColorCamera);
		}
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
