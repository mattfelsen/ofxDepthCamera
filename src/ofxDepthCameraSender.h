#pragma once

#include "ofMain.h"
#include "ofxBaseDepthCamera.h"

//#define STREAM_LWS
#define STREAM_ZMQ

#ifdef STREAM_LWS
#include "ofxLibwebsockets.h"
#endif

#ifdef STREAM_ZMQ
#include "ofxZmq.h"
#endif

class ofxDepthCameraSender {
public:
	void setup(ofxBaseDepthCamera& baseCam, string host = "", int port = 0);
	void update();
	
	void connect();
	void disconnect();

	string& getHost() { return host; }
	int getPort() { return port; }

protected:
	ofxBaseDepthCamera* device;

	string host;
	int port;

	#ifdef STREAM_LWS
	ofxLibwebsockets::Server sender;
	#endif

	#ifdef STREAM_ZMQ
	ofxZmqPublisher sender;
	#endif
};