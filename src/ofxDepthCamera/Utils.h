#pragma once

#include "ofMain.h"

namespace ofxDepthCam {
	class Utils {
	public:

		static void updateDepthImage(ofImage& depthImage, ofShortPixels& depthPixels, vector<char>& depthLookupTable);
		static void updateDepthLookupTable(vector<char>& depthLookupTable, int size, unsigned short nearClip, unsigned short farClip);
	};
}