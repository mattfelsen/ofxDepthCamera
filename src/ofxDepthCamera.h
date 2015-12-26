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
#include "Receiver.h"

#include "adapters/Kinect.h"
#include "adapters/KinectV2.h"
#include "adapters/OrbbecAstra.h"

#include "ofxImageSequence.h"
#include "ofxImageSequencePlayback.h"
#include "ofxImageSequenceRecorder.h"

using namespace ofxDepthCam;

class ofxDepthCamera {
public:

	ofxDepthCamera();
	~ofxDepthCamera();

	// Create a camera pointer and forward any arguments to the constructor
	// of the camera implementation being used
	template<typename CameraType, typename... Args>
	void setup(Args... args) {
		camera = make_shared<CameraType>();
		dynamic_pointer_cast<CameraType>(camera)->setup(args...);

        updateDepthLookupTable(camera->getMaxDepth());
	}

	void update();

    // Frame data
    bool isFrameNew();
    float getFrameRate();

    // Depth data & coordinate mapping
    ofVec3f getWorldCoordinateAt(int x, int y);
    unsigned short getMaxDepth();
    unsigned short getNearClip();
    unsigned short getFarClip();
    void setDepthClipping(unsigned short nearClip, unsigned short farClip);
    void updateDepthLookupTable(int size);
    void updateDepthImage(ofShortPixels& depthPixels);

	ofShortPixels& getRawDepth();
	ofImage& getDepthImage();
	ofImage& getColorImage();

	int getDepthWidth();
	int getDepthHeight();
	int getColorWidth();
	int getColorHeight();

    // Settings & modes
    void setName(string name);
    void setLive();
    void setLocal();
    void setRemote(string host = "", int port = 0);

    // Recording
    void setRecordPath(string path);
    void beginRecording(string recordPath = "");
    void endRecording();

    // Playback
    void setPlaybackPath(string path);
    void play(string path = "");
    void pause();
    void stop();

    // Misc
    string getName();
    shared_ptr<Base> getPointer();
    ofxShortImageSequenceRecorder& getRecorder();
    ofxShortImageSequencePlayback& getPlayer();

protected:
	shared_ptr<Base> camera;

	unsigned short nearClip;
	unsigned short farClip;

	ofImage depthImage;

	bool bDepthImageDirty;
	vector<char> depthLookupTable;

    // Streaming, recording, playback
    void createReceiver();
    void createRecorder();
    void createPlayer();
    unique_ptr<Receiver> receiver;
    unique_ptr<ofxShortImageSequenceRecorder> recorder;
    unique_ptr<ofxShortImageSequencePlayback> player;

    bool bLive;
    bool bRemote;
    bool bRecording;
    bool bCheckRecordingQueue;
    bool bPlaying;
    bool bPlayerLoaded;
    
    string name;
    string recordPath;

};
