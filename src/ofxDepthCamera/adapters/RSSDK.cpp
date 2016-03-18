#include "RSSDK.h"

using namespace ofxDepthCam;

RSSDK::RSSDK()
{
	// R200_SD
	depthWidth = 480;
	depthHeight = 360;

	colorWidth = 1920;
	colorHeight = 1080;

	frameRate = 30;

	availableFlags = OFXDEPTHCAMERA_MASK_DEPTH | OFXDEPTHCAMERA_MASK_COLOR | OFXDEPTHCAMERA_MASK_BODYINDEX | OFXDEPTHCAMERA_MASK_MESH;

	// https://software.intel.com/en-us/articles/intel-realsense-data-ranges
	maxDepth = 4000.0f;
}

ofxRSSDK::RSDevicePtr& RSSDK::getSensor()
{
	return mRSSDK;
}

void RSSDK::setup(int flags)
{
	mRSSDK = ofxRSSDK::RSDevice::createUniquePtr();
	if (!mRSSDK->init()) {
		ofLogError("RSSDK::setup") << "Unable to create ofxRSSDK object";
		return;
	}

	enabledFlags = 0;
	if ((flags & OFXDEPTHCAMERA_MASK_DEPTH) && isDepthAvailable()) {
		mRSSDK->initDepth(ofxRSSDK::DepthRes::R200_SD, frameRate, false);
		enabledFlags |= OFXDEPTHCAMERA_MASK_DEPTH;
	}
	if ((flags & OFXDEPTHCAMERA_MASK_COLOR) && isColorAvailable()) {
		mRSSDK->initRgb(ofxRSSDK::RGBRes::HD1080, frameRate);
		enabledFlags |= OFXDEPTHCAMERA_MASK_COLOR;
	}
	if ((flags & OFXDEPTHCAMERA_MASK_MESH) && isMeshAvailable()) {
		mRSSDK->enablePointCloud(ofxRSSDK::CloudRes::FULL_RES, 0.0f, maxDepth);
		enabledFlags |= OFXDEPTHCAMERA_MASK_MESH;
	}

	mRSSDK->start();
}

void RSSDK::close()
{
	mRSSDK->stop();
}

void RSSDK::update()
{
	mRSSDK->update();
	bNewFrame = true;  // TODO: Check this, maybe we need to switch to the stream frames method

	if (bNewFrame) {
		if (isDepthEnabled()) {
			depthPixels = mRSSDK->getDepthFrame();
		}
		if (isColorEnabled()) {
			colorPixels = mRSSDK->getRgbFrame();
		}
		if (isMeshEnabled()) {
			mesh.clear();
			mesh.setMode(OF_PRIMITIVE_POINTS);
			mesh.enableColors();

			//TODO: Figure out a better way to work with BGRA pixels
			vector<ofVec3f> pointCloud = mRSSDK->getPointCloud();
			for (auto& p : pointCloud) {
				mesh.addVertex(p);
				ofColor c = mRSSDK->getColorFromDepthSpace(p);
				mesh.addColor(ofColor(c.b, c.g, c.r));
			}
		}
	}
}

ofVec3f RSSDK::getWorldCoordinateAt(int x, int y)
{
	return mRSSDK->getDepthSpacePoint(x, y, 0);
}
