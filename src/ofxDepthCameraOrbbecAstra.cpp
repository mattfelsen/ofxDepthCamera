/*
*  ofxDepthCameraOrbbecAstra.cpp
*  ofxDepthCamera
*
*  Created by Matt Felsen on 11/3/15
*
*/

#include "ofxDepthCameraOrbbecAstra.h"

ofxDepthCameraOrbbecAstra::ofxDepthCameraOrbbecAstra() {
	fr = 30;
	depthWidth = 640;
	depthHeight = 480;
	colorWidth = 640;
	colorHeight = 480;

	streamset = nullptr;
	reader = nullptr;
}

ofxDepthCameraOrbbecAstra::~ofxDepthCameraOrbbecAstra() {
	astra::Astra::terminate();
}

void ofxDepthCameraOrbbecAstra::setup(int deviceId, bool useColor) {
	ofxBaseDepthCamera::setup();

	cachedCoords.resize(depthWidth * depthHeight);

	astra::Astra::initialize();

	streamset = make_unique<astra::StreamSet>();
	reader = make_unique<astra::StreamReader>(streamset->create_reader());

	// set up color stream
	astra::ImageStreamMode colorMode;
	auto colorStream = reader->stream<astra::ColorStream>();

	colorMode.set_width(colorWidth);
	colorMode.set_height(colorHeight);
	colorMode.set_pixelFormat(astra_pixel_formats::ASTRA_PIXEL_FORMAT_RGB888);
	colorMode.set_fps(fr);

	colorStream.set_mode(colorMode);
	colorStream.start();

	// set up depth stream
	astra::ImageStreamMode depthMode;
	auto depthStream = reader->stream<astra::DepthStream>();

	depthMode.set_width(depthWidth);
	depthMode.set_height(depthHeight);
	depthMode.set_pixelFormat(astra_pixel_formats::ASTRA_PIXEL_FORMAT_DEPTH_MM);
	depthMode.set_fps(fr);

	depthStream.set_mode(depthMode);
	depthStream.enable_registration(true);
	depthStream.start();

	// set up point stream
	reader->stream<astra::PointStream>().start();

	reader->addListener(*this);

	bDeviceFound = true; // TODO: Better initialization status
}

void ofxDepthCameraOrbbecAstra::close() {
	astra::Astra::terminate();
}

void ofxDepthCameraOrbbecAstra::update() {
	bNewFrame = false;
	astra_temp_update();
}

ofVec3f ofxDepthCameraOrbbecAstra::getWorldCoordinateAt(int x, int y) {
	return cachedCoords[int(y) * depthWidth + int(x)];
}

int ofxDepthCameraOrbbecAstra::maxDepth() {
	return 10000; //taken from looking into how ofxKinect calculates it's look up tables.
}

void ofxDepthCameraOrbbecAstra::on_frame_ready(astra::StreamReader& reader, astra::Frame& frame) {
	bNewFrame = true;

	astra::ColorFrame colorFrame = frame.get<astra::ColorFrame>();
	astra::DepthFrame depthFrame = frame.get<astra::DepthFrame>();
	astra::PointFrame pointFrame = frame.get<astra::PointFrame>();

	if (colorFrame.is_valid()) {
		const astra::RGBPixel* colorData = colorFrame.data();
		colorFrame.copy_to((astra::RGBPixel*) colorImage.getPixels().getData());
		colorImage.update();
	}

	if (depthFrame.is_valid()) {
		bDepthImageDirty = true;
		const short* depthData = depthFrame.data();
		depthFrame.copy_to((short*) depthPixels.getData());
	}

	if (pointFrame.is_valid()) {
		const astra::Vector3f* pointData = pointFrame.data();
		pointFrame.copy_to((astra::Vector3f*) cachedCoords.data());
	}
}