/*
 *  ofxDepthCameraMultiKinectV2.cpp
 *  ofxDepthCamera
 *
 *  Created by Jim George on 5/15/14 for ofxDepthKit
 *  Copyright 2014 FlightPhase. All rights reserved.
 *  Modified by Jonas Fehr 11/2015
 *
 */

#include "ofxDepthCameraMultiKinectV2.h"
#ifdef OFX_DEPTH_CAMERA_MULTIKINECTV2

#define STRINGIFY(x) #x

static string depthFragmentShader =
STRINGIFY(
          uniform sampler2DRect tex;
          void main()
          {
              vec4 col = texture2DRect(tex, gl_TexCoord[0].xy);
              float value = col.r;
              float low1 = 50.0;//500.0
              float high1 = 5000.0;
              float low2 = 1.0;
              float high2 = 0.0;
              float d = clamp(low2 + (value - low1) * (high2 - low2) / (high1 - low1), 0.0, 1.0);
              if (d == 1.0) {
                  d = 0.0;
              }
              gl_FragColor = vec4(vec3(d), 1.0);
          }
          );

static string irFragmentShader =
STRINGIFY(
          uniform sampler2DRect tex;
          void main()
          {
              vec4 col = texture2DRect(tex, gl_TexCoord[0].xy);
              float value = col.r / 65535.0;
              gl_FragColor = vec4(vec3(value), 1.0);
          }
          );


ofxDepthCameraMultiKinectV2::ofxDepthCameraKinectV2() {
    fr = 30;
    depthWidth = 512;
    depthHeight = 424;
    colorWidth = 1920;
    colorHeight = 1080;
}

ofxMultiKinectV2& ofxDepthCameraMultiKinectV2::getSensor() {
    return kinect;
}

void ofxDepthCameraMultiKinectV2::setup(int deviceId, bool useColor) {
    ofxBaseDepthCamera::setup();
    
    depthShader.setupShaderFromSource(GL_FRAGMENT_SHADER, depthFragmentShader);
    depthShader.linkProgram();
    
    irShader.setupShaderFromSource(GL_FRAGMENT_SHADER, irFragmentShader);
    irShader.linkProgram();
    
    kinect.open(useColor,true, deviceId, 2); //MacBookPro else 1 or 0;
    
    bDeviceFound = true;
    
    kinect.start();
    
    gr.setup(kinect.getProtonect(), 1);
}

void ofxDepthCameraMultiKinectV2::close() {
    kinect.close();
}

void ofxDepthCameraMultiKinectV2::update() {
    kinect.update();
    // there is a new frame and we are connected
    if (kinect.isFrameNew()) {
        bNewFrame = true;
        bDepthImageDirty = false;
        
        bDepthCalc = true;
        bIrCalc = true;
        bRegCalc = true;
        
        process_occlusion = false; //occlusion not working jet
        
        
        
        colorTex.loadData(kinect.getColorPixelsRef(), GL_RGB);
        if(colorTex.isAllocated()){
            colorImage.setFromPixels(kinect.getColorPixelsRef());
        }
        
        if(bDepthCalc){
            depthTex.loadData(kinect.getDepthPixelsRef(), GL_LUMINANCE);
            if(depthTex.isAllocated()){
                
                depthFbo.allocate(depthWidth, depthHeight);
                depthFbo.begin();
                depthShader.begin();
                depthTex.draw(0, 0, depthWidth, depthHeight);
                depthShader.end();
                depthFbo.end();
                
                depthFbo.readToPixels(depthPixels);
                
                if(!bDepthImageDirty) depthImage.setFromPixels(depthPixels);//kinect.getDepthPixelsRef());
            }
        }
        
        if(bIrCalc){
            irTex.loadData(kinect.getIrPixelsRef(), GL_LUMINANCE);
            if(depthTex.isAllocated()){
                
                irFbo.allocate(depthWidth, depthHeight);
                irFbo.begin();
                irShader.begin();
                irTex.draw(0, 0, depthWidth, depthHeight);
                irShader.end();
                irFbo.end();
                
                ofShortPixels irPixels;
                irFbo.readToPixels(irPixels);
                irImage.setFromPixels(irPixels);
            }
        }
        
        if(bRegCalc){
            if(!bDepthCalc) depthTex.loadData(kinect.getDepthPixelsRef(), GL_LUMINANCE);
            if( colorTex.isAllocated() && depthTex.isAllocated()){
                
                depthTex.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
                gr.update(depthTex, colorTex, process_occlusion);
                regFbo.allocate(depthWidth, depthHeight);
                regFbo.begin();
                gr.getRegisteredTexture(process_occlusion).draw(0, 0, depthWidth, depthHeight);
                regFbo.end();
                
                ofShortPixels regPixels;
                regFbo.readToPixels(regPixels);
                regImage.setFromPixels(regPixels);
            }
        }
        
        
        
        
        
    }
}

ofVec3f ofxDepthCameraMultiKinectV2::getWorldCoordinateAt(int x, int y) {
    return kinect.getWorldCoordinateAt(x, y);
}

int ofxDepthCameraMultiKinectV2::maxDepth() {
    return 10000; //taken from looking into how ofxKinect calculates it's look up tables.
}

ofImage& ofxDepthCameraMultiKinectV2::getIrImage() {
    return irImage;
}

ofImage& ofxDepthCameraMultiKinectV2::getRegImage() {
    return regImage;
}

#endif