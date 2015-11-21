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

void ofxDepthCamera::setType(Type type) {
	if (type == Type::Kinect)
		camera = make_shared<Kinect>();
	if (type == Type::KinectV2)
		camera = make_shared<KinectV2>();
	if (type == Type::OrbbecAstra) {
		camera = make_shared<OrbbecAstra>();
	}
}

void ofxDepthCamera::setPointer(shared_ptr<Base> pointer) {
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
