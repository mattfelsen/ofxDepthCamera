#pragma once

#include "ofMain.h"

namespace ofxDepthCam {
	class Utils {
	public:
		
		static void updateDepthImage(ofImage& depthImage, ofShortPixels& depthPixels, unsigned short nearClip, unsigned short farClip);
	};
}