#include "ofxDepthCameraProvider.h"

void ofxDepthCameraProvider::setup(ofxBaseDepthCamera& device) {
	this->device = &device;
	
	recorder.setFormat("raw");

	bLive = true;
	bRemote = false;
	bRecording = false;
	bPlaying = false;
}

void ofxDepthCameraProvider::update() {
	if (bLive) {
		if (!bRemote) {
			device->update();;
			
			if (bRecording) {
				recorder.addFrame(device->getRawDepth());
			}
		} else {
			receiver.update();

			if (bRecording) {
				recorder.addFrame(receiver.getPixels());
			}
		}
	} else {
		player.update();
	}

	if (!bRecording && recorder.isThreadRunning() && !recorder.getQueueLength()) {
		recorder.stopThread();
	}
}

void ofxDepthCameraProvider::draw() {
}

void ofxDepthCameraProvider::setLive() {
	bLive = true;
	player.pause();
}

void ofxDepthCameraProvider::setLocal() {
	bRemote = false;
	receiver.disconnect();
}

void ofxDepthCameraProvider::setRemote(string host, int port) {
	if (receiver.getHost().empty() || !receiver.getPort()) {
		if (host.empty() || !port) {
			ofLogError("ofxDepthCameraProvider", "Set remote params with setRemote(\"host\", port) first");
			return;
		}

		receiver.setup(device->getDepthWidth(), device->getDepthHeight(), host, port);
	}

	bRemote = true;
	receiver.connect();
}

void ofxDepthCameraProvider::beginRecording(string path) {
	if (path.empty()) {
		recordPath = "recordings/" + ofGetTimestampString("%Y-%m-%d-%H-%M-%S");
	}
	else {
		recordPath = "recordings/" + path;
	}

	recordPath += "/" + name + "_";
	recorder.setPrefix(recordPath);
	recorder.resetCounter();
	recorder.startThread();
}

void ofxDepthCameraProvider::endRecording() {
	player.loadSequence(recordPath, "raw", 0, recorder.getFrameCount() , 4, 60);
}

void ofxDepthCameraProvider::setRecordPath(string path) {
}

void ofxDepthCameraProvider::play() {
	player.play();
}

void ofxDepthCameraProvider::pause() {
	player.pause();

}
void ofxDepthCameraProvider::stop() {
	player.stop();
}

ofShortPixels& ofxDepthCameraProvider::getRawDepth() {
	if (bLive) {
		if (!bRemote) {
			return device->getRawDepth();
		} else {
			return receiver.getPixels();
		}
	} else {
		return player.getSequence().getPixels();
	}
}

ofImage& ofxDepthCameraProvider::getDepthImage() {
	if (bLive) {
		if (!bRemote) {
			return device->getDepthImage();
		}
		else {
			// TODO Implement depthImage for DepthReceiver
			//return receiver.getPixels();
		}
	}
	else {
		// TODO Implement depthImage for SequencePlayback
		//return player.getSequence().getPixels();
	}
}

ofImage& ofxDepthCameraProvider::getRawIRImage() {
	if (bLive) {
		if (!bRemote) {
			return device->getRawIRImage();
		}
		else {
			// Not supporting remote IR
			//return receiver.getPixels();
		}
	}
	else {
		// Not supporting playback of IR
		//return player.getSequence().getPixels();
	}
}

ofImage& ofxDepthCameraProvider::getColorImage() {
	if (bLive) {
		if (!bRemote) {
			return device->getColorImage();
		}
		else {
			// Not supporting remote color
			//return receiver.getPixels();
		}
	}
	else {
		// Not supporting playback of color
		//return player.getSequence().getPixels();
	}
}