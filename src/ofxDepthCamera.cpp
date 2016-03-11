/*
*  ofxDepthCamera.h
*  ofxDepthCamera
*
*  Created by Jim George on 3/13/12 for ofxDepthKit
*  Copyright 2012 FlightPhase. All rights reserved.
*  Modified by Matt Felsen 10/2015
*
*/

#include "ofxDepthCamera.h"

using namespace ofxDepthCam;

ofxDepthCamera::ofxDepthCamera() {
	nearClip = 300;
	farClip = 1800;

    bLive = true;
    bRemote = false;
    bRecording = false;
    bCheckRecordingQueue = false;
    bPlaying = false;
    bPlayerLoaded = false;

    name = "cam";

    camera = nullptr;
    receiver = nullptr;
    recorder = nullptr;
    player = nullptr;
}

ofxDepthCamera::~ofxDepthCamera() {
    if (!camera) return;
    camera->close();
}

void ofxDepthCamera::update() {
    if (bLive) {
        if (!bRemote) {
            if (!camera) return;
            camera->update();

            if (camera->isFrameNew()) {
                bDepthImageDirty = true;
                bColorImageDirty = true;
                bBodyIndexImageDirty = true;

                if (bRecording) {
                    recorder->addFrame(camera->getRawDepth());
                }
            }
        } else {
            receiver->update();

            // TODO Check for new frames when recording
            if (bRecording) {
                recorder->addFrame(receiver->getDepthPixels());
            }
        }
    } else {
        player->update();
    }

    if (bCheckRecordingQueue && recorder->isThreadRunning() && !recorder->getQueueLength()) {
        recorder->stopThread();
        bCheckRecordingQueue = false;
    }
}

bool ofxDepthCamera::isFrameNew() {
    // TODO report new frame from recorder/receiver/player/etc
    if (!camera) return false;
    return camera->isFrameNew();
}

float ofxDepthCamera::getFrameRate() {
    if (!camera) return 0.0;
    return camera->getFrameRate();
}

ofVec3f ofxDepthCamera::getWorldCoordinateAt(int x, int y) {
    if (!camera) return ofVec3f::zero();
    return camera->getWorldCoordinateAt(x, y);
}

unsigned short ofxDepthCamera::getMaxDepth() {
    if (!camera) return SHRT_MAX;
    return camera->getMaxDepth();
}

unsigned short ofxDepthCamera::getNearClip() {
    return nearClip;
}

unsigned short ofxDepthCamera::getFarClip() {
    return farClip;
}

void ofxDepthCamera::setDepthClipping(unsigned short nearClip, unsigned short farClip) {
	this->nearClip = nearClip;
	this->farClip = farClip;

	updateDepthLookupTable(getMaxDepth());
}

void ofxDepthCamera::updateDepthLookupTable(int size) {
    depthLookupTable.resize(size);

    // Depth values of 0 should be discarded, so set the LUT value to 0 as well
    depthLookupTable[0] = 0;

    // Set the rest
    for (int i = 1; i < size; i++) {
        depthLookupTable[i] = ofMap(i, nearClip, farClip, 255, 0, true);
    }
}

void ofxDepthCamera::updateDepthImage(ofShortPixels& depthPixels) {
    if (!depthPixels.isAllocated()) return;
    if (!depthImage.isAllocated()) {
        depthImage.allocate(depthPixels.getWidth(), depthPixels.getHeight(), OF_IMAGE_GRAYSCALE);
    }

    for (int y = 0; y < depthPixels.getHeight(); y++) {
        for (int x = 0; x < depthPixels.getWidth(); x++) {
            int index = (y * depthPixels.getWidth()) + x;
            float depth = depthPixels[index];
            float val = depthLookupTable[depth];
            depthImage.setColor(x, y, ofColor(val));
        }
    }
    
    depthImage.update();
    bDepthImageDirty = false;
}

void ofxDepthCamera::updateBodyIndexImage(ofPixels& bodyIndexPixels) {
    if (!bodyIndexPixels.isAllocated()) return;
    bodyIndexImage.setFromPixels(bodyIndexPixels);

    bBodyIndexImageDirty = false;
}

void ofxDepthCamera::updateColorImage(ofPixels& colorPixels) {
    if (!colorPixels.isAllocated()) return;
    colorImage.setFromPixels(colorPixels);

    bColorImageDirty = false;
}

ofShortPixels& ofxDepthCamera::getRawDepth() {
    if (bLive) {
        if (!bRemote) {
            if (!camera) {
                static ofShortPixels dummyPixels;
                return dummyPixels;
            }
            return camera->getRawDepth();
        } else {
            return receiver->getDepthPixels();
        }
    } else {
        return player->getSequence().getPixels();
    }
}

ofImage& ofxDepthCamera::getDepthImage() {
    if (bLive) {
        if (!bRemote) {
            if (!camera) {
                static ofImage dummyImage;
                return dummyImage;
            }
            if (bDepthImageDirty) {
                updateDepthImage(camera->getRawDepth());
            }
        } else {
            // TODO Check for new frames
            updateDepthImage(receiver->getDepthPixels());
        }
    } else {
        // TODO Check for new frames
        updateDepthImage(player->getSequence().getPixels());
    }

	return depthImage;
}

int ofxDepthCamera::getDepthWidth() {
    if (!camera) return 0;
    return camera->getRawDepth().getWidth();
}

int ofxDepthCamera::getDepthHeight() {
    if (!camera) return 0;
    return camera->getRawDepth().getHeight();
}

ofPixels& ofxDepthCamera::getRawColor() {
    if (bLive) {
        if (!bRemote) {
            if (!camera) {
                static ofPixels dummyPixels;
                return dummyPixels;
            }
            return camera->getRawColor();
        }
        else {
            // TODO Add Color to receiver
            //return receiver->getDepthPixels();
            static ofPixels dummyPixels;
            return dummyPixels;
        }
    }
    else {
        // TODO Add Color to player
        //return player->getSequence().getPixels();
        static ofPixels dummyPixels;
        return dummyPixels;
    }
}

ofImage& ofxDepthCamera::getColorImage() {
    if (bLive) {
        if (!bRemote) {
            if (!camera) {
                static ofImage dummyImage;
                return dummyImage;
            }
            if (bColorImageDirty) {
                updateColorImage(camera->getRawColor());
            }
        }
        else {
            // TODO Add Color to receiver
            //updateColorImage(receiver->getDepthPixels());
        }
    }
    else {
        // TODO Add Color to player
        //updateColorImage(player->getSequence().getPixels());
    }

    return colorImage;
}

int ofxDepthCamera::getColorWidth() {
	if (!camera) return 0;
	return camera->getRawColor().getWidth();
}

int ofxDepthCamera::getColorHeight() {
	if (!camera) return 0;
	return camera->getRawColor().getHeight();
}

ofPixels& ofxDepthCamera::getRawBodyIndex() {
    if (bLive) {
        if (!bRemote) {
            if (!camera) {
                static ofPixels dummyPixels;
                return dummyPixels;
            }
            return camera->getRawBodyIndex();
        }
        else {
            // TODO Add BodyIndex to receiver
            //return receiver->getDepthPixels();
            static ofPixels dummyPixels;
            return dummyPixels;
        }
    }
    else {
        // TODO Add BodyIndex to player
        //return player->getSequence().getPixels();
        static ofPixels dummyPixels;
        return dummyPixels;
    }
}

ofImage& ofxDepthCamera::getBodyIndexImage() {
    if (bLive) {
        if (!bRemote) {
            if (!camera) {
                static ofImage dummyImage;
                return dummyImage;
            }
            if (bBodyIndexImageDirty) {
                updateBodyIndexImage(camera->getRawBodyIndex());
            }
        }
        else {
            // TODO Add BodyIndex to receiver
            //updateBodyIndexImage(receiver->getDepthPixels());
        }
    }
    else {
        // TODO Add BodyIndex to player
        //updateBodyIndexImage(player->getSequence().getPixels());
    }

    return colorImage;
}

int ofxDepthCamera::getBodyIndexWidth() {
    if (!camera) return 0;
    return camera->getRawBodyIndex().getWidth();
}

int ofxDepthCamera::getBodyIndexHeight() {
    if (!camera) return 0;
    return camera->getRawBodyIndex().getHeight();
}

void ofxDepthCamera::setName(string name) {
    this->name = name;
}

void ofxDepthCamera::setLive() {
    bLive = true;

    if (bPlaying) {
        pause();
    }
    if (bRecording) {
        endRecording();
    }
}

void ofxDepthCamera::setLocal() {
    bRemote = false;
    if (receiver) receiver->disconnect();
}

void ofxDepthCamera::setRemote(string host, int port) {
    if (!receiver) createReceiver();

    if (receiver->getHost().empty() || !receiver->getPort()) {
        if (host.empty() || !port) {
            ofLogError("ofxDepthCamera", "Set remote params with setRemote(\"host\", port) first");
            return;
        }

        receiver->setup(getDepthWidth(), getDepthHeight(), host, port);
    }

    bRemote = true;
    receiver->connect();
}

void ofxDepthCamera::setRecordPath(string path) {
    if (!recorder) createRecorder();

    recordPath = ofFilePath::addTrailingSlash(path);
    recorder->setPrefix(recordPath);
}

void ofxDepthCamera::beginRecording(string path) {
    if (!path.empty()) {
        setRecordPath(path);
    } else if (recordPath.empty()) {
        setRecordPath("recordings/" + ofGetTimestampString("%Y-%m-%d-%H-%M-%S"));
    }

    bLive = true;
    bRecording = true;
    recorder->resetCounter();
    recorder->startThread();
}

void ofxDepthCamera::endRecording() {
    bRecording = false;
    bCheckRecordingQueue = true;
    setPlaybackPath(recordPath);
}

void ofxDepthCamera::setPlaybackPath(string path) {
    if (!player) createPlayer();

    player->setSize(getDepthWidth(), getDepthHeight());
    player->loadSequence(path);
    player->setFPS(getFrameRate());
    bPlayerLoaded = player->getTotalFrames() > 0;

    if (!bPlayerLoaded) {
        ofLogWarning("ofxDepthCamera", "Failed to set playback path to: %s", path.c_str());
    }
}

void ofxDepthCamera::play(string path) {
    if (!path.empty()) {
        setPlaybackPath(path);
    } else if (!bPlayerLoaded) {
        ofLogError("ofxDepthCamera", "Call setPlaybackPath(\"path\") first");
        return;
    }

    bLive = false;
    bPlaying = true;
    player->play();
}

void ofxDepthCamera::pause() {
    bPlaying = false;
    player->pause();

}
void ofxDepthCamera::stop() {
    bPlaying = false;
    player->stop();
}

string ofxDepthCamera::getName() {
    return name;
}

shared_ptr<Base> ofxDepthCamera::getPointer() {
    return camera;
}

ofxShortImageSequenceRecorder& ofxDepthCamera::getRecorder() {
    return *recorder.get();
}

ofxShortImageSequencePlayback& ofxDepthCamera::getPlayer() {
    return *player.get();
}

void ofxDepthCamera::createReceiver() {
    if (receiver) {
        ofLogWarning() << "Receiver already created!";
        return;
    }

    receiver = make_unique<Receiver>();
}

void ofxDepthCamera::createRecorder() {
    if (recorder) {
        ofLogWarning() << "Recorder already created!";
        return;
    }

    recorder = make_unique<ofxShortImageSequenceRecorder>();
    recorder->setFormat("raw");
}

void ofxDepthCamera::createPlayer() {
    if (player) {
        ofLogWarning() << "Player already created!";
        return;
    }

    player = make_unique<ofxShortImageSequencePlayback>();
    player->setImageType(OF_IMAGE_GRAYSCALE);
    player->setShouldLoop(true);
}