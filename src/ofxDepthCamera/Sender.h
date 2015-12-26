#pragma once

#include "ofMain.h"
#include "ofxDepthCamera.h"

#define STREAM_LWS
//#define STREAM_ZMQ

#ifdef STREAM_LWS
#include "ofxLibwebsockets.h"
#endif

#ifdef STREAM_ZMQ
#include "ofxZmq.h"
#endif

namespace ofxDepthCam {
	class Sender {
	public:
		void setup(shared_ptr<Base> pointer, int port = 0);
		void update();

		void connect();
		void disconnect();

		int getPort() { return port; }

	protected:
		shared_ptr<Base> device;

		int port;

		#ifdef STREAM_LWS
		ofxLibwebsockets::Server sender;
		#endif

		#ifdef STREAM_ZMQ
		ofxZmqPublisher sender;
		#endif
	};
}