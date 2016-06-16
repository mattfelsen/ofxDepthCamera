#pragma once

#pragma once

#include "ofMain.h"
#include "ofxDepthCamera.h"

#ifdef OFX_DEPTH_CAMERA_RSSDK
#include "ofxRSSDKv2.h"

namespace ofxDepthCam 
{
	class RSSDK : public Base 
	{
	public:
		RSSDK();
		ofxRSSDK::RSDevicePtr& getSensor();

		void setup(int flags = OFXDEPTHCAMERA_MASK_DEPTH);
		void close() override;
		void update() override;

		ofVec3f getWorldCoordinateAt(int x, int y) override;

	protected:
		ofxRSSDK::RSDevicePtr mRSSDK;
	};
}

#endif