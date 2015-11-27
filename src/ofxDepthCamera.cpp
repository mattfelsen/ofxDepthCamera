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
	nearClip = 300;
	farClip = 1800;
}

ofxDepthCamera::~ofxDepthCamera() {
    if (!camera) return;
    camera->close();
}

void ofxDepthCamera::update() {
	if (!camera) return;

	bDepthImageDirty = false;
	camera->update();

	if (camera->isFrameNew()) {
		bDepthImageDirty = true;
	}
}

bool ofxDepthCamera::isFrameNew() {
    if (!camera) return;
    return camera->isFrameNew();
}

float ofxDepthCamera::getFrameRate() {
    if (!camera) return;
    return camera->getFrameRate();
}

unsigned short ofxDepthCamera::getMaxDepth() {
	if (!camera) return;
    return camera->getMaxDepth();
}

ofVec3f ofxDepthCamera::getWorldCoordinateAt(int x, int y) {
    if (!camera) return;
    return camera->getWorldCoordinateAt(x, y);
}

unsigned short ofxDepthCamera::getNearClip() {
    return nearClip;
}

unsigned short ofxDepthCamera::getFarClip() {
    return farClip;
}

void ofxDepthCamera::setDepthClipping(unsigned short nearClip, unsigned short farClip) {
	this->nearClip = nearClip;
	this->farClip = farClip;

	updateDepthLookupTable(getMaxDepth());
}

void ofxDepthCamera::updateDepthLookupTable(int size) {
    depthLookupTable.resize(size);

    // Depth values of 0 should be discarded, so set the LUT value to 0 as well
    depthLookupTable[0] = 0;

    // Set the rest
    for (int i = 1; i < size; i++) {
        depthLookupTable[i] = ofMap(i, nearClip, farClip, 255, 0, true);
    }
    
}

void ofxDepthCamera::updateDepthImage(ofShortPixels& depthPixels) {
    if (!depthPixels.isAllocated()) return;
    if (!depthImage.isAllocated()) {
        depthImage.allocate(depthPixels.getWidth(), depthPixels.getHeight(), OF_IMAGE_GRAYSCALE);
    }

    for (int y = 0; y < depthPixels.getHeight(); y++) {
        for (int x = 0; x < depthPixels.getWidth(); x++) {
            int index = x + (y*depthPixels.getWidth());
            float depth = depthPixels[index];
            float val = depthLookupTable[depth];
            depthImage.setColor(x, y, ofColor(val));
        }
    }
    depthImage.update();
}

ofShortPixels& ofxDepthCamera::getRawDepth() {
	if (!camera) return;
	return camera->getRawDepth();
}

ofImage& ofxDepthCamera::getDepthImage() {
	if (!camera) return;

	if (bDepthImageDirty) {
        updateDepthImage(camera->getRawDepth());
		bDepthImageDirty = false;
	}

	return depthImage;
}

ofImage& ofxDepthCamera::getColorImage() {
	if (!camera) return;
	return camera->getColorImage();
}

int ofxDepthCamera::getDepthWidth() {
	if (!camera) return;
	return camera->getRawDepth().getWidth();
}

int ofxDepthCamera::getDepthHeight() {
	if (!camera) return;
	return camera->getRawDepth().getHeight();
}

int ofxDepthCamera::getColorWidth() {
	if (!camera) return;
	return camera->getColorImage().getWidth();
}

int ofxDepthCamera::getColorHeight() {
	if (!camera) return;
	return camera->getColorImage().getHeight();
}