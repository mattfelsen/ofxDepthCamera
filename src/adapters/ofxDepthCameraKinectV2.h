/*
*  ofxDepthCameraKinectV2.h
*  ofxDepthCamera
*
*  Created by Jim George on 3/13/12 for ofxDepthKit
*  Copyright 2012 FlightPhase. All rights reserved.
*  Modified by Matt Felsen 10/2015
*
*/

#pragma once

#include "ofMain.h"
#include "ofxBaseDepthCamera.h"

#define OFX_DEPTH_CAMERA_KINECTV2


#ifdef OFX_DEPTH_CAMERA_KINECTV2

#if defined(_MSC_VER) || defined(_WIN32) || defined(WIN32) || defined(__MINGW32__)

// WINDOWS

#include "ofxKinectForWindows2.h"

class ofxDepthCameraKinectV2: public ofxBaseDepthCamera {
public:
    ofxDepthCameraKinectV2();
    ofxKFW2::Device& getSensor();
    
    void setup(int deviceId = 0, bool useColor = false);
    void close();
    void update();
    
    int maxDepth();
    ofVec3f getWorldCoordinateAt(int x, int y);
    
protected:
    ofxKFW2::Device kinect;
    ICoordinateMapper* mapper;
    
    vector<ofVec3f> cachedCoords;
    bool coordsDirty;
};

#else

// OSX & LINUX

#include "ofxMultiKinectV2.h"
#include "GpuRegistration.h"


class ofxDepthCameraKinectV2: public ofxBaseDepthCamera {
public:
    ofxDepthCameraKinectV2();
    ofxMultiKinectV2& getSensor();
    
    void setup(int deviceId = 0, bool useColor = false);
    void close();
    void update();
    
    int maxDepth();
    ofVec3f getWorldCoordinateAt(int x, int y);
    
    ofImage& getIrImage();
    ofImage& getRegImage();
    
    
protected:
    ofxMultiKinectV2 kinect;
    GpuRegistration gr;
    bool process_occlusion;
    
    bool bIrCalc;
    bool bDepthCalc;
    bool bRegCalc;
    
    ofShader depthShader;
    ofShader irShader;
    ofTexture colorTex;
    ofTexture depthTex;
    ofTexture irTex;
    ofFbo   depthFbo;
    ofFbo   irFbo;
    ofFbo   regFbo;
    ofImage regImage;
    ofImage irImage;
    
    
};

#endif
#endif