#include "ofxDepthCameraUtils.h"

void ofxDepthCameraUtils::updateDepthImage(ofImage& depthImage, ofShortPixels& depthPixels, unsigned short nearClip, unsigned short farClip) {
	// TODO Use lookup table instead
	// Calculate a lookup table when clipping bounds change and use that
	// instead of calling ofMap() every time

	if (!depthImage.isAllocated()) return;
	if (!depthPixels.isAllocated()) return;

	for (int y = 0; y < depthImage.getHeight(); y++) {
		for (int x = 0; x < depthImage.getWidth(); x++) {
			int index = x + (y*depthImage.getWidth());
			float depth = depthPixels[index];
			float val = depth == 0 ? 0 : ofMap(depth, nearClip, farClip, 255, 0, true);
			depthImage.setColor(x, y, ofColor(val));
		}
	}
	depthImage.update();
}