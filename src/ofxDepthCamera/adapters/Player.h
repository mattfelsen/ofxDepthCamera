#pragma once

#include "ofMain.h"
#include "ofxDepthCamera.h"
#include "ofxImageSequencePlayback.h"

namespace ofxDepthCam
{
	class Player 
		: public Base 
	{
	public:
		Player();

		void setup(const string& path, int flags = OFXDEPTHCAMERA_MASK_DEPTH, float fps = 30.0f);
		void close() override;
		void update() override;

		void setFolderPath(const string& path);

		void play();
		void pause();
		void stop();

		bool isPlaying() const;

		ofVec3f getWorldCoordinateAt(int x, int y) override;

		ofxShortImageSequencePlayback& getDepthPlayback();
		ofxImageSequencePlayback& getColorPlayback();
		ofxImageSequencePlayback& getBodyIndexPlayback();

	protected:
		unique_ptr<ofxShortImageSequencePlayback> depthPlayback;
		unique_ptr<ofxImageSequencePlayback> colorPlayback;
		unique_ptr<ofxImageSequencePlayback> bodyIndexPlayback;

		int masterPlayback;

		string folderPath;
		string depthPath;
		string colorPath;
		string bodyIndexPath;

		int lastFrame;

		bool bPlaying;
		bool bTimeBased;
	};
}