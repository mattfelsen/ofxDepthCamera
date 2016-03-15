#include "Player.h"

using namespace ofxDepthCam;

Player::Player()
{
	close();
}

void Player::setup(const string& path, int flags, float fps)
{
	setFolderPath(path);

	enabledFlags = 0;
	masterPlayback = 0;

	if ((flags & OFXDEPTHCAMERA_MASK_DEPTH) && isDepthAvailable()) {
		if (!depthPlayback) {
			depthPlayback = make_unique<ofxShortImageSequencePlayback>();
			depthPlayback->setImageType(OF_IMAGE_GRAYSCALE);
			depthPlayback->setSize(512, 424);
			depthPlayback->setShouldLoop(true);
		}
		depthPlayback->loadSequence(depthPath);

		enabledFlags |= OFXDEPTHCAMERA_MASK_DEPTH;
		if (!masterPlayback) {
			masterPlayback = OFXDEPTHCAMERA_MASK_DEPTH;
			depthPlayback->setFPS(fps);
		}
	}

	if ((flags & OFXDEPTHCAMERA_MASK_COLOR) && isColorAvailable()) {
		if (!colorPlayback) {
			colorPlayback = make_unique<ofxImageSequencePlayback>();
			//colorPlayback->setImageType(OF_IMAGE_COLOR_ALPHA);
			colorPlayback->setSize(1920, 1080);
			colorPlayback->setShouldLoop(true);
		}
		colorPlayback->loadSequence(colorPath);

		enabledFlags |= OFXDEPTHCAMERA_MASK_COLOR;
		if (!masterPlayback) {
			masterPlayback = OFXDEPTHCAMERA_MASK_COLOR;
			colorPlayback->setFPS(fps);
		}
	}

	if ((flags & OFXDEPTHCAMERA_MASK_BODYINDEX) && isBodyIndexAvailable()) {
		if (!bodyIndexPlayback) {
			bodyIndexPlayback = make_unique<ofxImageSequencePlayback>();
			//bodyIndexPlayback->setImageType(OF_IMAGE_COLOR);
			bodyIndexPlayback->setSize(512, 424);
			bodyIndexPlayback->setShouldLoop(true);
		}
		bodyIndexPlayback->loadSequence(bodyIndexPath);

		enabledFlags |= OFXDEPTHCAMERA_MASK_BODYINDEX;
		if (!masterPlayback) {
			masterPlayback = OFXDEPTHCAMERA_MASK_BODYINDEX;
			bodyIndexPlayback->setFPS(fps);
		}
	}

	if (!enabledFlags) {
		ofLogWarning("Player", "Failed to set playback flags: %d", flags);
		return;
	}

	play();
}

void Player::close()
{
	folderPath = "";
	depthPath = "";
	colorPath = "";
	bodyIndexPath = "";

	depthPlayback.release();
	colorPlayback.release();
	bodyIndexPlayback.release();

	masterPlayback = 0;
	lastFrame = -1;

	bPlaying = false;
	bTimeBased = true;
}

void Player::update()
{
	bNewFrame = false;

	if (bPlaying) {
		int currFrame = 0;
		if (masterPlayback == OFXDEPTHCAMERA_MASK_DEPTH) {
			depthPlayback->update();
			currFrame = depthPlayback->getCurrentFrameIndex();
		}
		else if (masterPlayback == OFXDEPTHCAMERA_MASK_COLOR) {
			colorPlayback->update();
			currFrame = colorPlayback->getCurrentFrameIndex();
		}
		else if (masterPlayback == OFXDEPTHCAMERA_MASK_BODYINDEX) {
			bodyIndexPlayback->update();
			currFrame = bodyIndexPlayback->getCurrentFrameIndex();
		}

		if (lastFrame != currFrame) {
			if (isDepthEnabled()) {
				depthPlayback->setCurrentFrameIndex(currFrame);
				depthPixels = depthPlayback->getSequence().getPixels();
			}
			if (isColorEnabled()) {
				colorPlayback->setCurrentFrameIndex(currFrame);
				colorPixels = colorPlayback->getSequence().getPixels();
			}
			if (isBodyIndexEnabled()) {
				bodyIndexPlayback->setCurrentFrameIndex(currFrame);
				bodyIndexPixels = bodyIndexPlayback->getSequence().getPixels();
			}

			bNewFrame = true;
			lastFrame = currFrame;
		}
	}
}

void Player::setFolderPath(const string& path)
{
	folderPath = ofFilePath::addTrailingSlash(path);
	availableFlags = 0;

	depthPath = folderPath + "depth/";
	if (ofDirectory::doesDirectoryExist(depthPath)) {
		availableFlags |= OFXDEPTHCAMERA_MASK_DEPTH;
	}

	colorPath = folderPath + "color/";
	if (ofDirectory::doesDirectoryExist(colorPath)) {
		availableFlags |= OFXDEPTHCAMERA_MASK_COLOR;
	}

	bodyIndexPath = folderPath + "bodyIndex/";
	if (ofDirectory::doesDirectoryExist(bodyIndexPath)) {
		availableFlags |= OFXDEPTHCAMERA_MASK_BODYINDEX;
	}

    if (!availableFlags) {
        ofLogWarning("Player", "Failed to set playback path to: %s", path.c_str());
    }
}

void Player::play() 
{
    if (!enabledFlags) {
        ofLogError("Player", "Call setup(\"path\") first!");
        return;
    }

	if (masterPlayback == OFXDEPTHCAMERA_MASK_DEPTH) {
		depthPlayback->play();
	}
	else if (masterPlayback == OFXDEPTHCAMERA_MASK_COLOR) {
		colorPlayback->play();
	}
	else if (masterPlayback == OFXDEPTHCAMERA_MASK_BODYINDEX) {
		bodyIndexPlayback->play();
	}

    bPlaying = true;
}

void Player::pause() 
{
	if (masterPlayback == OFXDEPTHCAMERA_MASK_DEPTH) {
		depthPlayback->pause();
	}
	else if (masterPlayback == OFXDEPTHCAMERA_MASK_COLOR) {
		colorPlayback->pause();
	}
	else if (masterPlayback == OFXDEPTHCAMERA_MASK_BODYINDEX) {
		bodyIndexPlayback->pause();
	}
	
	bPlaying = false;
}

void Player::stop() 
{
	if (masterPlayback == OFXDEPTHCAMERA_MASK_DEPTH) {
		depthPlayback->stop();
	}
	else if (masterPlayback == OFXDEPTHCAMERA_MASK_COLOR) {
		colorPlayback->stop();
	}
	else if (masterPlayback == OFXDEPTHCAMERA_MASK_BODYINDEX) {
		bodyIndexPlayback->stop();
	}
	
	bPlaying = false;
}

bool Player::isPlaying() const
{
	return bPlaying;
}

ofVec3f Player::getWorldCoordinateAt(int x, int y)
{
	return ofVec3f::zero();
}

ofxShortImageSequencePlayback& Player::getDepthPlayback()
{
	return *depthPlayback.get();
}

ofxImageSequencePlayback& Player::getColorPlayback()
{
	return *colorPlayback.get();
}

ofxImageSequencePlayback& Player::getBodyIndexPlayback()
{
	return *bodyIndexPlayback.get();
}
