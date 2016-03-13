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

using namespace ofxDepthCam;

bool Base::isFrameNew() {
    return bNewFrame;
}

unsigned short Base::getMaxDepth() {
	return maxDepth;
}

float Base::getFrameRate() {
	return frameRate;
}

ofShortPixels& Base::getRawDepth() {
	return depthPixels;
}

ofPixels& Base::getRawColor() {
	return colorPixels;
}

ofPixels& Base::getRawBodyIndex() {
	return bodyIndexPixels;
}

ofMesh& Base::getMesh() {
	return mesh;
}

bool Base::isDepthAvailable() const {
	return (availableFlags & OFXDEPTHCAMERA_MASK_DEPTH);
}

bool Base::isColorAvailable() const {
	return (availableFlags & OFXDEPTHCAMERA_MASK_COLOR);
}

bool Base::isBodyIndexAvailable() const {
	return (availableFlags & OFXDEPTHCAMERA_MASK_BODYINDEX);
}

bool Base::isMeshAvailable() const {
	return (availableFlags & OFXDEPTHCAMERA_MASK_MESH);
}

bool Base::isDepthEnabled() const {
	return (enabledFlags & OFXDEPTHCAMERA_MASK_DEPTH);
}

bool Base::isColorEnabled() const {
	return (enabledFlags & OFXDEPTHCAMERA_MASK_COLOR);
}

bool Base::isBodyIndexEnabled() const {
	return (enabledFlags & OFXDEPTHCAMERA_MASK_BODYINDEX);
}

bool Base::isMeshEnabled() const {
	return (enabledFlags & OFXDEPTHCAMERA_MASK_MESH);
}
