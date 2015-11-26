/*
*  ofxDepthCamera.h
*  ofxDepthCamera
*
*  Created by Jim George on 3/13/12 for ofxDepthKit
*  Modified by Matt Felsen 10/2015
*
*/

#pragma once

// Comment any of these in to enable the devices you want
//#define OFX_DEPTH_CAMERA_KINECT
//#define OFX_DEPTH_CAMERA_KINECT_V2
#define OFX_DEPTH_CAMERA_ORBBEC_ASTRA

#include "ofMain.h"
#include "Base.h"
#include "Utils.h"

#include "adapters/Kinect.h"
#include "adapters/KinectV2.h"
#include "adapters/OrbbecAstra.h"

using namespace ofxDepthCam;

class ofxDepthCamera {
public:

	ofxDepthCamera();
	~ofxDepthCamera();

	// Create a pointer and forward any arguments to the constructor
	// of the camera implementation being used
	template<typename CameraType, typename... Args>
	void setup(Args... args) {
		camera = make_shared<CameraType>();
		dynamic_pointer_cast<CameraType>(camera)->setup(args...);

		Utils::updateDepthLookupTable(depthLookupTable, camera->getMaxDepth(), nearClip, farClip);
	}

	void update();

    bool isFrameNew();
    float getFrameRate();
    unsigned short getMaxDepth();
    ofVec3f getWorldCoordinateAt(int x, int y);

    unsigned short getNearClip();
    unsigned short getFarClip();
    void setDepthClipping(unsigned short nearClip, unsigned short farClip);

	ofShortPixels& getRawDepth();
	ofImage& getDepthImage();
	ofImage& getColorImage();

	int getDepthWidth();
	int getDepthHeight();
	int getColorWidth();
	int getColorHeight();

protected:
	shared_ptr<Base> camera;

	unsigned short nearClip;
	unsigned short farClip;

	ofImage depthImage;

	bool bDepthImageDirty;
	vector<char> depthLookupTable;

};
