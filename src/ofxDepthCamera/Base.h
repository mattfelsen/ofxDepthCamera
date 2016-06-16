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

#define OFXDEPTHCAMERA_MASK_DEPTH       0x0001
#define OFXDEPTHCAMERA_MASK_COLOR       0x0010
#define OFXDEPTHCAMERA_MASK_BODYINDEX   0x0100
#define OFXDEPTHCAMERA_MASK_MESH	    0x1000

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
		virtual ofPixels& getRawColor();
		virtual ofPixels& getRawBodyIndex();
		virtual ofMesh& getMesh();

		bool isDepthAvailable() const;
		bool isColorAvailable() const;
		bool isBodyIndexAvailable() const;
		bool isMeshAvailable() const;

		bool isDepthEnabled() const;
		bool isColorEnabled() const;
		bool isBodyIndexEnabled() const;
		bool isMeshEnabled() const;

	protected:
		bool bNewFrame;

		float frameRate;
		unsigned short maxDepth;

		int availableFlags;
		int enabledFlags;

		int depthWidth;
		int depthHeight;
		ofShortPixels depthPixels;

		int colorWidth;
		int colorHeight;
		ofPixels colorPixels;

		int bodyIndexWidth;
		int bodyIndexHeight;
		ofPixels bodyIndexPixels;

		ofMesh mesh;
	};
}
