/*
*  OrbbecAstra.cpp
*  ofxDepthCamera
*
*  Created by Matt Felsen on 11/3/15
*
*/

#include "OrbbecAstra.h"

#ifdef OFX_DEPTH_CAMERA_ORBBEC_ASTRA

using namespace ofxDepthCam;

OrbbecAstra::OrbbecAstra() {
	fr = 30;
	depthWidth = 640;
	depthHeight = 480;
	colorWidth = 640;
	colorHeight = 480;
}

OrbbecAstra::~OrbbecAstra() {

}

void OrbbecAstra::setup() {
//	ofxBaseDepthCamera::setup();

    astra.setup();
    astra.setRegistration(true);
    astra.initColorStream();
    astra.initDepthStream();
    astra.initPointStream();

	bDeviceFound = true; // TODO: Better initialization status
}

void OrbbecAstra::close() {
	astra::Astra::terminate();
}

void OrbbecAstra::update() {
    astra.update();

    if (astra.isFrameNew()) {
        bNewFrame = true;
        depthPixels = astra.getRawDepth();
        depthImage = astra.getDepthImage();
        colorImage = astra.getColorImage();
    }
}

ofVec3f OrbbecAstra::getWorldCoordinateAt(int x, int y) {
    return astra.getWorldCoordinateAt(x, y);
}

int OrbbecAstra::maxDepth() {
    // 8m range as documented here:
    // https://orbbec3d.com/product-persee/
    // https://orbbec3d.com/product-astra/
    // https://orbbec3d.com/product-astra-pro/
	return 8000;
}

#endif
