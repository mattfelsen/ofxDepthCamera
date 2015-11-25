/*
*  ofxBaseDepthCamera.h
*  ofxDepthCamera
*
*  Created by Jim George on 3/13/12 for ofxDepthKit
*  Modified by Matt Felsen 10/2015
*
*/

#pragma once

#include "ofMain.h"

namespace ofxDepthCam {
	class Base {

	public:
		virtual ~Base() {}

		virtual void setup() {}
		virtual void close() {}
		virtual void update() {}

		virtual ofVec3f getWorldCoordinateAt(int x, int y) {}

		virtual bool isFrameNew();
		virtual float getFrameRate();
		virtual unsigned short getMaxDepth();

		virtual ofShortPixels& getRawDepth();
		virtual ofImage& getColorImage();

	protected:
		bool bNewFrame;

		float fr;
		unsigned short maxDepth;

		int depthWidth;
		int depthHeight;
		int colorWidth;
		int colorHeight;

		ofShortPixels depthPixels;
		ofImage colorImage;
	};
}
