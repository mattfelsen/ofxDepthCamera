meta:
	ADDON_NAME = ofxDepthCamera
	ADDON_DESCRIPTION = Device-independent library for working with multiple depth cameras, recording, playback, and streaming remotely
	ADDON_AUTHOR = Matt Felsen
	ADDON_TAGS = "kinect" "depth camera" "middleware"
	ADDON_URL = http://github.com/mattfelsen/ofxDepthCamera

common:
	ADDON_INCLUDES += addons/ofxImageSequence/src
	ADDON_INCLUDES += addons/ofxImageSequencePlayback/src
	ADDON_INCLUDES += addons/ofxImageSequenceRecorder/src
	
	ADDON_SOURCES += addons/ofxImageSequence/src/ofxImageSequence.h
	ADDON_SOURCES += addons/ofxImageSequence/src/ofxImageSequence.cpp
	ADDON_SOURCES += addons/ofxImageSequencePlayback/src/ofxImageSequencePlayback.h
	ADDON_SOURCES += addons/ofxImageSequencePlayback/src/ofxImageSequencePlayback.cpp
	ADDON_SOURCES += addons/ofxImageSequenceRecorder/src/ofxImageSequenceRecorder.h

	ADDON_SOURCES_EXCLUDE  = src/ofxDepthCamera/Sender.h
	ADDON_SOURCES_EXCLUDE += src/ofxDepthCamera/Sender.cpp

