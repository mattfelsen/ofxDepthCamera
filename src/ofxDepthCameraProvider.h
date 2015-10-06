#pragma once

#include "ofMain.h"

#include "ofxBaseDepthCamera.h"
#include "ofxDepthCameraReceiver.h"

#include "ofxImageSequence.h"
#include "ofxImageSequencePlayback.h"
#include "ofxImageSequenceRecorder.h"

class ofxDepthCameraProvider : ofxBaseDepthCamera {

public:
	void setup();
	void update();
	void draw();

	void setLive();
	void setLocal();
	void setRemote();

	void beginRecording();
	void endRecording();
	void setRecordPath(string path);

	void play();
	void pause();
	void stop();

protected:
	ofxBaseDepthCamera* camera;
	ofxShortImageSequencePlayback player;
	ofxImageSequenceRecorder recorder;

	bool bLive;
	bool bRemote;
	bool bRecording;
	bool bPlaying;

	string recordPath;

};