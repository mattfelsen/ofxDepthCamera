#pragma once

#include "ofMain.h"

#include "ofxBaseDepthCamera.h"
#include "ofxDepthCameraReceiver.h"

#include "ofxImageSequence.h"
#include "ofxImageSequencePlayback.h"
#include "ofxImageSequenceRecorder.h"

class ofxDepthCameraProvider {

public:
	void setup(ofxBaseDepthCamera& device);
	void update();
	void draw();

	void setLive();
	void setLocal();
	void setRemote(string host = "", int port = 0);

	void beginRecording(string recordPath = "");
	void endRecording();
	void setRecordPath(string path);

	void play();
	void pause();
	void stop();

	ofShortPixels& getRawDepth();
	ofImage& getDepthImage();
	ofImage& getRawIRImage();
	ofImage& getColorImage();

	string& getName() { return name; }

protected:
	// Live camaera input, local & remote
	ofxBaseDepthCamera* device;
	ofxDepthCameraReceiver receiver;

	// Record & playback
	ofxShortImageSequenceRecorder recorder;
	ofxShortImageSequencePlayback player;

	bool bLive;
	bool bRemote;
	bool bRecording;
	bool bPlaying;

	string name;
	string recordPath;

};