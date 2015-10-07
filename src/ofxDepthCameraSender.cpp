#include "ofxDepthCameraSender.h"

void ofxDepthCameraSender::setup(ofxBaseDepthCamera& baseCam, string host, int port) {
	this->device = &baseCam;
	this->host = host;
	this->port = port;
	connect();
}

void ofxDepthCameraSender::connect() {

	if (host.empty()) {
		ofLogError("ofxDepthCameraSender", "No host is set");
		return;
	}
	if (!port) {
		ofLogError("ofxDepthCameraSender", "No port is set");
		return;
	}

	stringstream ss;
	
	#ifdef STREAM_LWS
	ss << "ws://" + host;
	#endif

	#ifdef STREAM_ZMQ
	ss << "tcp://*";
	#endif

	// TODO Figure out why ZMQ will only bind to * and not localhost
	//ss << host << ":" << port;
	ss << ":" << port;
	sender.bind(ss.str());
}

void ofxDepthCameraSender::disconnect() {
	#ifdef STREAM_LWS
	sender.close();
	#endif

	#ifdef STREAM_ZMQ
	// TODO disconnect/unbind/stop serving
	//sender.unbind();
	#endif
}

void ofxDepthCameraSender::update() {
	device->update();

	#ifdef STREAM_LWS
	// TODO Sending with LWS
	//if (sender.getConnected() && device->isFrameNew()) {
	//	sender.sendBinary((unsigned char*) device->getRawDepth(), device->getRawDepth().size() * device->getRawDepth().getBytesPerPixel());
	//}
	#endif

	#ifdef STREAM_ZMQ
	if (sender.getConnected() && device->isFrameNew()) {
		sender.send((void*) device->getRawDepth(), device->getRawDepth().size() * device->getRawDepth().getBytesPerPixel());
	}
	#endif
}