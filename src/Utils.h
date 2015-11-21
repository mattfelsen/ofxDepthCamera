#pragma once

#include "ofMain.h"

namespace ofxDepthCamera {
	class Utils {
	public:
		
		static void updateDepthImage(ofImage& depthImage, ofShortPixels& depthPixels, unsigned short nearClip, unsigned short farClip);
	};
}