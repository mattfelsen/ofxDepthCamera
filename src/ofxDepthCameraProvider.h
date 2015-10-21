#pragma once

#include "ofMain.h"

#include "ofxBaseDepthCamera.h"
#include "ofxDepthCameraReceiver.h"

#include "ofxImageSequence.h"
#include "ofxImageSequencePlayback.h"
#include "ofxImageSequenceRecorder.h"

class ofxDepthCameraProvider {

public:

	ofxDepthCameraProvider();
	~ofxDepthCameraProvider();

	void setup(ofxBaseDepthCamera* baseCam);
	void update();
	void draw(int x = 0, int y = 0, int w = 0, int h = 0);

	void setName(string name);
	void setLive();
	void setLocal();
	void setRemote(string host = "", int port = 0);

	void setRecordPath(string path);
	void beginRecording(string recordPath = "");
	void endRecording();

	void setPlaybackPath(string path);
	void play(string path = "");
	void pause();
	void stop();

	string& getName() { return name; }

	ofShortPixels& getRawDepth();
	ofImage& getDepthImage();
	ofImage& getColorImage();

	ofxShortImageSequenceRecorder& getRecorder() { return recorder; }
	ofxShortImageSequencePlayback& getPlayer() { return player; }

protected:
	// Live camera input, local & remote
	ofxBaseDepthCamera* device;
	ofxDepthCameraReceiver receiver;

	// Record & playback
	ofxShortImageSequenceRecorder recorder;
	ofxShortImageSequencePlayback player;

	// Local copy of image to copy pixels into from player & receiver,
	// which only keep pixel data and can't be drawn directly to screen
	ofImage depthImage;

	bool bLive;
	bool bRemote;
	bool bRecording;
	bool bPlaying;
	bool bPlayerLoaded;

	string name;
	string recordPath;
	string playbackPath;

};