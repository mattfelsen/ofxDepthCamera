/*
*  ofxDepthCameraOrbbecAstra.cpp
*  ofxDepthCamera
*
*  Created by Matt Felsen on 11/3/15
*
*/

//#ifdef OFX_DEPTH_CAMERA_ORBBEC_ASTRA

#include "ofxDepthCameraOrbbecAstra.h"

ofxDepthCameraOrbbecAstra::ofxDepthCameraOrbbecAstra() {
	fr = 30;
	depthWidth = 640;
	depthHeight = 480;
	colorWidth = 640;
	colorHeight = 480;
}

ofxDepthCameraOrbbecAstra::~ofxDepthCameraOrbbecAstra() {

}

void ofxDepthCameraOrbbecAstra::setup() {
//	ofxBaseDepthCamera::setup();

    astra.setup();
    astra.setRegistration(true);
    astra.initColorStream();
    astra.initDepthStream();
    astra.initPointStream();

	bDeviceFound = true; // TODO: Better initialization status
}

void ofxDepthCameraOrbbecAstra::close() {
	astra::Astra::terminate();
}

void ofxDepthCameraOrbbecAstra::update() {
    astra.update();

    if (astra.isFrameNew()) {
        bNewFrame = true;
        depthPixels = astra.getRawDepth();
        depthImage = astra.getDepthImage();
        colorImage = astra.getColorImage();
    }
}

ofVec3f ofxDepthCameraOrbbecAstra::getWorldCoordinateAt(int x, int y) {
    return astra.getWorldCoordinateAt(x, y);
}

int ofxDepthCameraOrbbecAstra::maxDepth() {
    // 8m range as documented here:
    // https://orbbec3d.com/product-persee/
    // https://orbbec3d.com/product-astra/
    // https://orbbec3d.com/product-astra-pro/
	return 8000;
}

//#endif