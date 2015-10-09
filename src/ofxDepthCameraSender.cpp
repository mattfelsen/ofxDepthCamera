#include "ofxDepthCameraSender.h"

void ofxDepthCameraSender::setup(ofxBaseDepthCamera& baseCam, int port) {
	this->device = &baseCam;
	this->port = port;
	connect();
}

void ofxDepthCameraSender::connect() {

	if (!port) {
		ofLogError("ofxDepthCameraSender", "No port is set");
		return;
	}
	
	#ifdef STREAM_LWS
	sender.setup(port);
	#endif

	#ifdef STREAM_ZMQ
	string addr = "tcp://*" + ofToString(port);
	sender.bind(addr);
	#endif

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
	if (sender.getConnections().size() && device->isFrameNew()) {
		sender.sendBinary((unsigned char*) device->getRawDepth().getData(), device->getRawDepth().size() * device->getRawDepth().getBytesPerPixel());
	}
	#endif

	#ifdef STREAM_ZMQ
	if (sender.getConnected() && device->isFrameNew()) {
		sender.send((void*) device->getRawDepth(), device->getRawDepth().size() * device->getRawDepth().getBytesPerPixel());
	}
	#endif
}