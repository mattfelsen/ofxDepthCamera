/*
*  ofxDepthCameraOrbbecAstra.h
*  ofxDepthCamera
*
*  Created by Matt Felsen on 11/3/15
*
*/

#pragma once

#include "ofMain.h"
#include "ofxBaseDepthCamera.h"

#include <Astra/Astra.h>
#include <AstraUL/AstraUL.h>

class ofxDepthCameraOrbbecAstra : public ofxBaseDepthCamera,
								  public astra::FrameReadyListener {
public:
	ofxDepthCameraOrbbecAstra();
	~ofxDepthCameraOrbbecAstra();

	void setup(int deviceId = 0, bool useColor = false);
	void close();
	void update();

	int maxDepth();
	ofVec3f getWorldCoordinateAt(int x, int y);

	virtual void on_frame_ready(astra::StreamReader& reader,
								astra::Frame& frame) override;

protected:
	unique_ptr<astra::StreamSet> streamset;
	unique_ptr<astra::StreamReader> reader;

	vector<ofVec3f> cachedCoords;
	bool coordsDirty;
};