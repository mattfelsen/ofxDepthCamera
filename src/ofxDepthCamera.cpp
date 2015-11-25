/*
*  ofxDepthCamera.h
*  ofxDepthCamera
*
*  Created by Jim George on 3/13/12 for ofxDepthKit
*  Copyright 2012 FlightPhase. All rights reserved.
*  Modified by Matt Felsen 10/2015
*
*/

#include "ofxDepthCamera.h"

using namespace ofxDepthCam;

ofxDepthCamera::ofxDepthCamera() {
	camera = nullptr;
}

ofxDepthCamera::~ofxDepthCamera() {

}

void ofxDepthCamera::update() {
	if (!camera) return;
	camera->update();
}

ofShortPixels& ofxDepthCamera::getRawDepth() {
	if (!camera) return;
	return camera->getRawDepth();
}

ofImage& ofxDepthCamera::getDepthImage() {
	if (!camera) return;
	return camera->getDepthImage();
}

ofImage& ofxDepthCamera::getColorImage() {
	if (!camera) return;
	return camera->getColorImage();
}
