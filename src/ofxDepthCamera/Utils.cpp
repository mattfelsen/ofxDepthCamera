#include "Utils.h"

using namespace ofxDepthCam;

void Utils::updateDepthImage(ofImage& depthImage, ofShortPixels& depthPixels, vector<char>& depthLookupTable) {

	if (!depthPixels.isAllocated()) return;
	if (!depthImage.isAllocated()) {
		depthImage.allocate(depthPixels.getWidth(), depthPixels.getHeight(), OF_IMAGE_GRAYSCALE);
	}

	for (int y = 0; y < depthPixels.getHeight(); y++) {
		for (int x = 0; x < depthPixels.getWidth(); x++) {
			int index = x + (y*depthPixels.getWidth());
			float depth = depthPixels[index];
			float val = depthLookupTable[depth];
			depthImage.setColor(x, y, ofColor(val));
		}
	}
	depthImage.update();
}

void Utils::updateDepthLookupTable(vector<char>& depthLookupTable, int size, unsigned short nearClip, unsigned short farClip) {
	depthLookupTable.resize(size);

	// Depth values of 0 should be discarded, so set the LUT value to 0 as well
	depthLookupTable[0] = 0;

	// Set the rest
	for (int i = 1; i < size; i++) {
		depthLookupTable[i] = ofMap(i, nearClip, farClip, 255, 0, true);
	}

}