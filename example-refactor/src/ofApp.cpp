#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// Set the type of camera for this specific instance
	device.setType(ofxDepthCam::Type::OrbbecAstra);

	device.setup();
//	device.setup(0, true);
//	device.setDepthClipping(1000, 2500);
//	cam.setup(&device);

	// Provider defaults to live, directly connected device. You can manually set with:
	//cam.setLive();

	// Use this to specify a remote device running a sender
	//cam.setRemote("192.168.0.1", 9200);

	// Use this for playback of recorded data
	//cam.setPlaybackPath("recordings/2015-09-15-15-45-32");
	//cam.play();

}

//--------------------------------------------------------------
void ofApp::update(){
	device.update();
//	cam.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	device.getDepthImage().draw(0, 0);
	device.getColorImage().draw(0, device.getDepthImage().getHeight());
//	cam.getDepthImage().draw(0, 0);
//	cam.getColorImage().draw(0, cam.getDepthImage().getHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'r') {
//		cam.beginRecording();
	}
	if (key == 'R') {
//		cam.endRecording();
	}
	if (key == ' ') {
		if (!ofGetKeyPressed(OF_KEY_SHIFT)) {
//			cam.play();
		}
		else {
//			cam.pause();
		}
	}
	if (key == 'l') {
		ofFileDialogResult result = ofSystemLoadDialog("Choose a folder of recorded data", true, ofToDataPath(""));
		if (result.getPath() != "") {
//			cam.setPlaybackPath(result.getPath());
		}
	}
	if (key == 'L') {
//		cam.setLive();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	for (auto& file : dragInfo.files) {
		if (ofFile(file).isDirectory()) {
//			cam.setPlaybackPath(file);
			return;
		}
	}
}
