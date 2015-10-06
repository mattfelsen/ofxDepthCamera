#include "ofxDepthCameraReceiver.h"

void ofxDepthCameraReceiver::setup(int depthWidth, int depthHeight, string host, int port) {
	this->depthWidth = depthWidth;
	this->depthHeight = depthHeight;
	this->host = host;
	this->port = port;
	connect();

	depthPixels.allocate(depthWidth, depthHeight, OF_IMAGE_GRAYSCALE);
}

void ofxDepthCameraReceiver::connect() {
	stringstream ss;
	
	#ifdef STREAM_LWS
	ss << "ws://";
	#endif

	#ifdef STREAM_ZMQ
	ss << "tcp://";
	#endif

	ss << host << ":" << port;
	receiver.connect(ss.str());
}

void ofxDepthCameraReceiver::disconnect() {
	#ifdef STREAM_LWS
	receiver.close();
	#endif

	#ifdef STREAM_ZMQ
	receiver.disconnect();
	#endif
}

void ofxDepthCameraReceiver::update() {
	#ifdef STREAM_LWS
	
	#endif

	#ifdef STREAM_ZMQ
	while (receiver.hasWaitingMessage()) {
		ofBuffer data;
		receiver.getNextMessage(data);
		depthPixels.setFromPixels((unsigned short*) data.getData(), depthWidth, depthHeight, OF_IMAGE_GRAYSCALE);
	}
	#endif
}