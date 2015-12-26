#include "Sender.h"

void Sender::setup(shared_ptr<Base> pointer, int port) {
	this->device = pointer;
	this->port = port;
	connect();
}

void Sender::connect() {

	if (!port) {
		ofLogError("ofxDepthCamera", "No port is set");
		return;
	}
	
	#ifdef STREAM_LWS
	sender.setup(port);
	#endif

	#ifdef STREAM_ZMQ
	string addr = "tcp://*:" + ofToString(port);
	sender.bind(addr);
	#endif
}

void Sender::disconnect() {
	#ifdef STREAM_LWS
	sender.close();
	#endif

	#ifdef STREAM_ZMQ
	// TODO disconnect/unbind/stop serving
	//sender.unbind();
	#endif
}

void Sender::update() {
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
