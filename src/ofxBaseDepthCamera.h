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

class ofxBaseDepthCamera {
public:
	ofxBaseDepthCamera();
	~ofxBaseDepthCamera();

	virtual void setup(int deviceID = 0, bool useColor = false) = 0;
	virtual void close() = 0;
	virtual void update() = 0;
	
	virtual int maxDepth() = 0;
	virtual ofVec3f getWorldCoordinateAt(int x, int y) = 0;

	void setDepthClipping(unsigned short nearClip, unsigned short farClip);
	bool isFrameNew();
	bool deviceFound();

	int getDepthWidth();
	int getDepthHeight();
	int getColorWidth();
	int getColorHeight();

	ofShortPixels& getRawDepth();
	ofImage& getDepthImage();
	ofImage& getRawIRImage();
	ofImage& getColorImage();

protected:
	bool bDeviceFound;

	bool bDepthImageDirty;
	bool bNewFrame;

	unsigned short nearClip;
	unsigned short farClip;

	int depthWidth;
	int depthHeight;
	int colorWidth;
	int colorHeight;

	ofShortPixels depthPixels;
	ofImage rawIRImage;
	ofImage depthImage;
	ofImage colorImage;

};