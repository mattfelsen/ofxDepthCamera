#pragma once

#include "ofMain.h"
#include "ofxBaseDepthCamera.h"

class ofxDepthCameraUtils {
public:
	static void updateDepthImage(ofImage& depthImage, ofShortPixels& depthPixels, unsigned short nearClip, unsigned short farClip);
};