/*
*  Base.cpp
*  ofxDepthCamera
*
*  Created by Jim George on 3/13/12 for ofxDepthKit
*  Copyright 2012 FlightPhase. All rights reserved.
*  Modified by Matt Felsen 10/2015
*
*/

#include "Base.h"

// From old pattern
// Need to migrate some of this to ofxDepthCamera and get rid of the rest

using namespace ofxDepthCam;

/*
ofxBaseDepthCamera::ofxBaseDepthCamera() {
	bDepthImageDirty = false;
	bDeviceFound = false;
	bNewFrame = false;
}

void ofxBaseDepthCamera::setup() {
	depthPixels.allocate(depthWidth, depthHeight, OF_IMAGE_GRAYSCALE);
	depthImage.allocate(depthWidth, depthHeight, OF_IMAGE_GRAYSCALE);
	colorImage.allocate(colorWidth, colorHeight, OF_IMAGE_COLOR);
}

ofxBaseDepthCamera::~ofxBaseDepthCamera() {
//	close();
}

void ofxBaseDepthCamera::close() {

}

void ofxBaseDepthCamera::setDepthClipping(unsigned short nearClip, unsigned short farClip) {
	this->nearClip = nearClip;
	this->farClip = farClip;
}

bool ofxBaseDepthCamera::isFrameNew() {
	bool ret = bNewFrame;
	bNewFrame = false;
	return ret;
}

bool ofxBaseDepthCamera::deviceFound() {
	return bDeviceFound;
}

float ofxBaseDepthCamera::frameRate() {
	return fr;
}

int ofxBaseDepthCamera::getDepthWidth() {
	return depthWidth;
}

int ofxBaseDepthCamera::getDepthHeight() {
	return depthHeight;
}

int ofxBaseDepthCamera::getColorWidth() {
	return colorWidth;
}

int ofxBaseDepthCamera::getColorHeight() {
	return colorHeight;
}

unsigned short ofxBaseDepthCamera::getNearClip() {
	return nearClip;
}

unsigned short ofxBaseDepthCamera::getFarClip() {
	return farClip;
}
*/

ofShortPixels& Base::getRawDepth() {
	return depthPixels;
}

ofImage& Base::getDepthImage() {
//	if (bDepthImageDirty) {
//		ofxDepthCameraUtils::updateDepthImage(depthImage, depthPixels, nearClip, farClip);
//	}
	return depthImage;
}

ofImage& Base::getColorImage() {
	return colorImage;
}


