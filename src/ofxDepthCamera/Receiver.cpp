#include "Receiver.h"

using namespace ofxDepthCam;

void Receiver::setup(int depthWidth, int depthHeight, string host, int port) {
	this->depthWidth = depthWidth;
	this->depthHeight = depthHeight;
	this->host = host;
	this->port = port;
	connect();

	depthImage.allocate(depthWidth, depthHeight, OF_IMAGE_GRAYSCALE);
	depthPixels.allocate(depthWidth, depthHeight, OF_IMAGE_GRAYSCALE);
}

void Receiver::connect() {

	if (host.empty()) {
		ofLogError("ofxDepthCameraReceiver", "No host is set");
		return;
	}
	if (!port) {
		ofLogError("ofxDepthCameraReceiver", "No port is set");
		return;
	}

	#ifdef STREAM_LWS
	receiver.connect(host, port);
	receiver.addListener(this);
	#endif

	#ifdef STREAM_ZMQ
	string addr = "tcp://" + host + ":" + ofToString(port);
	receiver.connect(addr);
	#endif
}

void Receiver::disconnect() {
	#ifdef STREAM_LWS
	receiver.close();
	#endif

	#ifdef STREAM_ZMQ
	receiver.disconnect();
	#endif
}

void Receiver::update() {
	#ifdef STREAM_LWS
	if (bNeedToLoad) {
		depthPixels.setFromPixels((unsigned short*) buffer.getData(), depthWidth, depthHeight, OF_IMAGE_GRAYSCALE);
		depthImage.setFromPixels(depthPixels);
		bLocked = false;
		bNeedToLoad = false;
	}
	#endif

	#ifdef STREAM_ZMQ
	while (receiver.hasWaitingMessage()) {
		receiver.getNextMessage(buffer);
		depthPixels.setFromPixels((unsigned short*) buffer.getData(), depthWidth, depthHeight, OF_IMAGE_GRAYSCALE);
		depthImage.setFromPixels(depthPixels);
	}
	#endif
}

#ifdef STREAM_LWS
void Receiver::onConnect(ofxLibwebsockets::Event& args) {
	ofLogVerbose() << "on connected";
}

void Receiver::onOpen(ofxLibwebsockets::Event& args) {
	ofLogVerbose() << "on open";
}

void Receiver::onClose(ofxLibwebsockets::Event& args) {
	ofLogVerbose() << "on close";
}

void Receiver::onIdle(ofxLibwebsockets::Event& args) {
	ofLogVerbose() << "on idle";
}

void Receiver::onMessage(ofxLibwebsockets::Event& args) {
	if (bLocked) return;

	// need to load this next frame!
	if (args.isBinary) {
		buffer.clear();
		buffer.set(args.data.getData(), args.data.size());
		bLocked = true;
		bNeedToLoad = true;
	}
	else {
		// got a string message
	}
}

void Receiver::onBroadcast(ofxLibwebsockets::Event& args) {
	cout << "got broadcast " << args.message << endl;
}
#endif