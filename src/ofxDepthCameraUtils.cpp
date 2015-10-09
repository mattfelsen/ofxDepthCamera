#include "ofxDepthCameraUtils.h"

void ofxDepthCameraUtils::updateDepthImage(ofImage& depthImage, ofShortPixels& depthPixels, unsigned short nearClip, unsigned short farClip) {
	// TODO Use lookup table instead
	// Calculate a lookup table when clipping bounds change and use that
	// instead of calling ofMap() every time

	if (!depthPixels.isAllocated()) return;
	if (!depthImage.isAllocated()) {
		depthImage.allocate(depthPixels.getWidth(), depthPixels.getHeight(), OF_IMAGE_GRAYSCALE);
	}

	for (int y = 0; y < depthPixels.getHeight(); y++) {
		for (int x = 0; x < depthPixels.getWidth(); x++) {
			int index = x + (y*depthPixels.getWidth());
			float depth = depthPixels[index];
			float val = depth == 0 ? 0 : ofMap(depth, nearClip, farClip, 255, 0, true);
			depthImage.setColor(x, y, ofColor(val));
		}
	}
	depthImage.update();
}