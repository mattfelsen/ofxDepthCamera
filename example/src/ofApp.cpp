#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	device.setup(0, true);
	cam.setup(device);

	// Provider defaults to live, directly connected device. You can manually set with:
	//cam.setLive();

	// Use this to specify a remote device running a sender
	//cam.setRemote("192.168.0.1", 7687);

	// Use this for playback of recorded data
	//cam.setPlaybackPath("recordings/2015-09-15-15-45-32");
	//cam.play();
}

//--------------------------------------------------------------
void ofApp::update(){
	cam.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.getDepthImage().draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

}
