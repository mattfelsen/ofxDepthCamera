#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// Set the type of camera for this specific instance

	// If using a Kinect v1 with ofxKinect, uncomment the next line, and
	// uncomment `#define OFX_DEPTH_CAMERA_KINECT` in ofxDepthCamera.h
//	device.setup<Kinect>();

	// If using a Kinect v2 with ofxKinectV2, uncomment the next line, and
	// uncomment `#define OFX_DEPTH_CAMERA_KINECT_V2` in ofxDepthCamera.h
//	device.setup<KinectV2>();

	// If using a Kinect v2 with ofxMultiKinectV2, uncomment the next line, and
	// uncomment `#define OFX_DEPTH_CAMERA_MULTI_KINECT_V2` in ofxDepthCamera.h
//	device.setup<MultiKinectV2>(true);

	// If using a Kinect v2 with ofxKinectForWindows2, uncomment the next line, and
	// uncomment `#define OFX_DEPTH_CAMERA_KFW2` in ofxDepthCamera.h
//	device.setup<KinectForWindows2>();

	// If using an Orbbec Astra with ofxOrbbecAstra, uncomment the next line, and
	// uncomment `#define OFX_DEPTH_CAMERA_ORBBEC_ASTRA` in ofxDepthCamera.h
//	device.setup<OrbbecAstra>(true);

	// If you have an Orbbec Astra Pro and are seeing a blank screen, try changing
	// true in setup above to false and uncommenting the following lines
//	auto ptr = static_pointer_cast<OrbbecAstra>(device.getPointer());
//	ptr->getSensor().initVideoGrabber();

	// Set the near/far depth values in millimeters
	device.setDepthClipping(400, 4500);

	// Defaults to live, directly connected device. You can manually set with:
	//device.setLive();

	// Use this to specify a remote device running a sender
	//device.setRemote("192.168.0.1", 9200);

	// Use this for playback of recorded data
	//device.setPlaybackPath("recordings/2015-09-15-15-45-32");
	//device.play();

}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
	device.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	device.getDepthImage().draw(0, 0);
    device.getColorImage().draw(0, device.getDepthHeight(), device.getDepthWidth(), device.getDepthHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'r') {
		device.beginRecording();
	}
	if (key == 'R') {
		device.endRecording();
	}
	if (key == ' ') {
		if (!ofGetKeyPressed(OF_KEY_SHIFT)) {
			device.play();
		}
		else {
			device.pause();
		}
	}
	if (key == 'l') {
		ofFileDialogResult result = ofSystemLoadDialog("Choose a folder of recorded data", true, ofToDataPath(""));
		if (result.getPath() != "") {
			device.setPlaybackPath(result.getPath());
		}
	}
	if (key == 'L') {
		device.setLive();
	}
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	for (auto& file : dragInfo.files) {
		if (ofFile(file).isDirectory()) {
			device.setPlaybackPath(file);
			return;
		}
	}
}
