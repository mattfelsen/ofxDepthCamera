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

using namespace ofxDepthCamera;

Device::Device() {
	camera = nullptr;
}

Device::~Device() {
}

void Device::setType(Type type) {
	if (type == Type::Kinect)
		camera = make_shared<Kinect>();
	if (type == Type::KinectV2)
		camera = make_shared<KinectV2>();
	if (type == Type::OrbbecAstra) {
		camera = make_shared<OrbbecAstra>();
	}
}

void Device::setPointer(shared_ptr<Base> pointer) {
	camera = pointer;
}

void Device::setup() {
	if (!camera) return;
	camera->setup();
}

void Device::update() {
	if (!camera) return;
	camera->update();
}

ofShortPixels& Device::getRawDepth() {
	if (!camera) return;
	return camera->depthPixels;
}

ofImage& Device::getDepthImage() {
	if (!camera) return;
	return camera->depthImage;
}

ofImage& Device::getColorImage() {
	if (!camera) return;
	return camera->colorImage;
}
