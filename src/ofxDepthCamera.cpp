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

ofxDepthCamera::ofxDepthCamera() {
	camera = nullptr;
}

ofxDepthCamera::~ofxDepthCamera() {
}

void ofxDepthCamera::setType(Type type) {
	if (type == Kinect)
		camera = make_shared<ofxDepthCameraKinect>();
	if (type == KinectV2)
		camera = make_shared<ofxDepthCameraKinectV2>();
	if (type == OrbbecAstra) {
		camera = make_shared<ofxDepthCameraOrbbecAstra>();
	}
}

void ofxDepthCamera::setPointer(shared_ptr<ofxBaseDepthCamera> pointer) {
	camera = pointer;
}

void ofxDepthCamera::setup() {
	if (!camera) return;
	camera->setup();
}

void ofxDepthCamera::update() {
	if (!camera) return;
	camera->update();
}

ofShortPixels& ofxDepthCamera::getRawDepth() {
	if (!camera) return;
	return camera->depthPixels;
}

ofImage& ofxDepthCamera::getDepthImage() {
	if (!camera) return;
	return camera->depthImage;
}

ofImage& ofxDepthCamera::getColorImage() {
	if (!camera) return;
	return camera->colorImage;
}
