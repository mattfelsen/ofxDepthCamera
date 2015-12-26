#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	device.setup<OrbbecAstra>();
	sender.setup(device.getPointer(), 9200);
}

//--------------------------------------------------------------
void ofApp::update(){
	device.update();
	sender.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	device.getDepthImage().draw(0, 0);
}
