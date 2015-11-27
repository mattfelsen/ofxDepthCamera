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
	depthWidth = 640;
	depthHeight = 480;
	colorWidth = 640;
	colorHeight = 480;

	frameRate = 30;

	// 8m range as documented here:
	// https://orbbec3d.com/product-persee/
	// https://orbbec3d.com/product-astra/
	// https://orbbec3d.com/product-astra-pro/
	maxDepth = 8000;
}

OrbbecAstra::~OrbbecAstra() {

}

void OrbbecAstra::setup() {
    astra.setup();
    astra.enableRegistration(true);
    astra.enableDepthImage(false);
    astra.initColorStream();
    astra.initDepthStream();
    astra.initPointStream();
}

void OrbbecAstra::close() {
	astra::Astra::terminate();
}

void OrbbecAstra::update() {
    astra.update();
    bNewFrame = astra.isFrameNew();

    if (bNewFrame) {
        depthPixels = astra.getRawDepth();
        colorImage = astra.getColorImage();
    }
}

ofVec3f OrbbecAstra::getWorldCoordinateAt(int x, int y) {
    return astra.getWorldCoordinateAt(x, y);
}

#endif
