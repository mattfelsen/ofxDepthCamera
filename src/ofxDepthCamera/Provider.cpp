#include "Provider.h"

ofxDepthCameraProvider::ofxDepthCameraProvider() {
	bLive = true;
	bRemote = false;
	bRecording = false;
	bPlaying = false;
	bPlayerLoaded = false;

	name = "cam";
	recorder.setFormat("raw");

	player.setImageType(OF_IMAGE_GRAYSCALE);
	player.setShouldLoop(true);
}

void ofxDepthCameraProvider::update() {
	if (bLive) {
		if (!bRemote) {
            ofxDepthCamera::update();
			
			if (bRecording && isFrameNew()) {
				recorder.addFrame(ofxDepthCamera::getRawDepth());
			}
		} else {
			receiver.update();

			// TODO Check for new frames when recording
			if (bRecording) {
				recorder.addFrame(receiver.getDepthPixels());
			}
		}
	} else {
		player.update();
	}

	if (!bRecording && recorder.isThreadRunning() && !recorder.getQueueLength()) {
		recorder.stopThread();
	}
}

void ofxDepthCameraProvider::draw(int x, int y, int w, int h) {
	w = w ? w : getDepthWidth();
	h = h ? h : getDepthHeight();
	getDepthImage().draw(x, y, w, h);
}

void ofxDepthCameraProvider::setName(string name) {
	this->name = name;
}

void ofxDepthCameraProvider::setLive() {
	bLive = true;

	if (bPlaying) {
		pause();
	}
	if (bRecording) {
		endRecording();
	}	
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

		receiver.setup(getDepthWidth(), getDepthHeight(), host, port);
	}

	bRemote = true;
	receiver.connect();
}

void ofxDepthCameraProvider::setRecordPath(string path) {
	recordPath = ofFilePath::addTrailingSlash(path);
	recorder.setPrefix(recordPath);
}

void ofxDepthCameraProvider::beginRecording(string path) {
	if (!path.empty()) {
        setRecordPath(path);
    } else if (recordPath.empty()) {
        setRecordPath("recordings/" + ofGetTimestampString("%Y-%m-%d-%H-%M-%S"));
    }

	bLive = true;
	bRecording = true;
	recorder.resetCounter();
	recorder.startThread();
}

void ofxDepthCameraProvider::endRecording() {
	bRecording = false;
    setPlaybackPath(recordPath);
}

void ofxDepthCameraProvider::setPlaybackPath(string path) {
    player.setSize(getDepthWidth(), getDepthHeight());
	player.loadSequence(path);
	player.setFPS(getFrameRate());
	bPlayerLoaded = player.getTotalFrames() > 0;

	if (!bPlayerLoaded) {
		ofLogWarning("ofxDepthCameraProvider", "Failed to set playback path to: %s", path.c_str());
	}
}

void ofxDepthCameraProvider::play(string path) {
    if (!path.empty()) {
        setPlaybackPath(path);
    } else if (!bPlayerLoaded) {
        ofLogError("ofxDepthCameraProvider", "Call setPlaybackPath(\"path\") first");
        return;
    }

	bLive = false;
	bPlaying = true;
	player.play();
}

void ofxDepthCameraProvider::pause() {
	bPlaying = false;
	player.pause();

}
void ofxDepthCameraProvider::stop() {
	bPlaying = false;
	player.stop();
}

ofShortPixels& ofxDepthCameraProvider::getRawDepth() {
	if (bLive) {
		if (!bRemote) {
			return ofxDepthCamera::getRawDepth();
		} else {
			return receiver.getDepthPixels();
		}
	} else {
		return player.getSequence().getPixels();
	}
}

ofImage& ofxDepthCameraProvider::getDepthImage() {
	if (bLive) {
		if (!bRemote) {
            return ofxDepthCamera::getDepthImage();
		}
		else {
            // TODO Check for new frames
            updateDepthImage(receiver.getDepthPixels());
		}
	} else {
        // TODO Check for new frames
		updateDepthImage(player.getSequence().getPixels());
	}

	return depthImage;
}

ofImage& ofxDepthCameraProvider::getColorImage() {
	if (bLive) {
		if (!bRemote) {
            return ofxDepthCamera::getColorImage();
		}
		else {
			// Not supporting remote color
			return ofxDepthCamera::getColorImage();
		}
	}
	else {
		// Not supporting playback of color
		return ofxDepthCamera::getColorImage();
	}
}
