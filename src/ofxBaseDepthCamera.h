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

/*
class ofxBaseDepthCamera {
public:
	ofxBaseDepthCamera();
	~ofxBaseDepthCamera();

	virtual void setup();
	virtual void close() {}
	virtual void update() {}
	
	float frameRate();
	virtual int maxDepth() {}
	virtual ofVec3f getWorldCoordinateAt(int x, int y) {}

	void setDepthClipping(unsigned short nearClip, unsigned short farClip);
	bool isFrameNew();
	bool deviceFound();

	int getDepthWidth();
	int getDepthHeight();
	int getColorWidth();
	int getColorHeight();

	unsigned short getNearClip();
	unsigned short getFarClip();

	ofShortPixels& getRawDepth();
	ofImage& getDepthImage();
	ofImage& getColorImage();

protected:
	bool bDeviceFound;

	bool bDepthImageDirty;
	bool bNewFrame;

	unsigned short nearClip;
	unsigned short farClip;

	float fr;

	int depthWidth;
	int depthHeight;
	int colorWidth;
	int colorHeight;

	ofShortPixels depthPixels;
	ofImage depthImage;
	ofImage colorImage;

};
*/

class ofxBaseDepthCamera {
	friend class ofxDepthCamera;

public:
	virtual ~ofxBaseDepthCamera() {}

	virtual void setup() {}
	virtual void close() {}
	virtual void update() {}

	virtual int maxDepth() {}
	virtual ofVec3f getWorldCoordinateAt(int x, int y) {}

protected:
	bool bDeviceFound;

	bool bDepthImageDirty;
	bool bNewFrame;

	unsigned short nearClip;
	unsigned short farClip;

	float fr;

	int depthWidth;
	int depthHeight;
	int colorWidth;
	int colorHeight;

	ofShortPixels depthPixels;
	ofImage depthImage;
	ofImage colorImage;
};
