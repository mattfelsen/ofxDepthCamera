/*
*  ofxBaseDepthCamera.h
*  ofxBaseDepthCamera
*
*  Orignally created by Jim George on 3/13/12 for ofxDepthKit
*  Modified by Matt Felsen 10/2015
*  Copyright 2012 FlightPhase. All rights reserved.
*
*/

#include "ofxBaseDepthCamera.h"

ofxBaseDepthCamera::ofxBaseDepthCamera() {
	bDepthImageDirty = false;
	bDeviceFound = false;
	bNewFrame = false;

	depthPixels.allocate(640, 480, OF_IMAGE_GRAYSCALE);
	rawIRImage.allocate(640, 480, OF_IMAGE_GRAYSCALE);
	depthImage.allocate(640, 480, OF_IMAGE_COLOR);
}

ofxBaseDepthCamera::~ofxBaseDepthCamera() {
	close();
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

ofShortPixels& ofxBaseDepthCamera::getRawDepth() {
	return depthPixels;
}

ofImage& ofxBaseDepthCamera::getDepthImage() {
	return depthImage;
}

ofImage& ofxBaseDepthCamera::getRawIRImage() {
	return rawIRImage;
}

ofImage& ofxBaseDepthCamera::getColorImage() {
	return colorImage;
}

