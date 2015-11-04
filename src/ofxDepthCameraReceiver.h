#pragma once

#include "ofMain.h"

//#define STREAM_LWS
//#define STREAM_ZMQ

#ifdef STREAM_LWS
#include "ofxLibwebsockets.h"
#endif

#ifdef STREAM_ZMQ
#include "ofxZmq.h"
#endif

class ofxDepthCameraReceiver {
public:
	void setup(int depthWidth, int depthHeight, string host = "", int port = 0);
	void update();
	
	void connect();
	void disconnect();

	string& getHost() { return host; }
	int getPort() { return port; }

	ofImage& getDepthImage() { return depthImage; }
	ofShortPixels& getDepthPixels() { return depthPixels; }

	ofBuffer buffer;

	#ifdef STREAM_LWS
	void onConnect(ofxLibwebsockets::Event& args);
	void onOpen(ofxLibwebsockets::Event& args);
	void onClose(ofxLibwebsockets::Event& args);
	void onIdle(ofxLibwebsockets::Event& args);
	void onMessage(ofxLibwebsockets::Event& args);
	void onBroadcast(ofxLibwebsockets::Event& args);

	bool bNeedToLoad, bLocked;
	#endif

protected:
	string host;
	int port;

	int depthWidth, depthHeight;

	ofImage depthImage;
	ofShortPixels depthPixels;

	#ifdef STREAM_LWS
	ofxLibwebsockets::Client receiver;
	#endif

	#ifdef STREAM_ZMQ
	ofxZmqSubscriber receiver;
	#endif
};