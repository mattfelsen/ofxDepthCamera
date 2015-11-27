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

        virtual void close() = 0;
        virtual void update() = 0;

        virtual ofVec3f getWorldCoordinateAt(int x, int y) = 0;

		virtual bool isFrameNew();
		virtual float getFrameRate();
		virtual unsigned short getMaxDepth();

		virtual ofShortPixels& getRawDepth();
		virtual ofImage& getColorImage();

	protected:
		bool bNewFrame;

		float frameRate;
		unsigned short maxDepth;

		int depthWidth;
		int depthHeight;
		int colorWidth;
		int colorHeight;

		ofShortPixels depthPixels;
		ofImage colorImage;
	};
}
