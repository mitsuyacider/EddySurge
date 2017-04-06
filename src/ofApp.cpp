#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Framerate
    ofSetFrameRate(30);

    
    setting = &setting->sharedInstance();
    bgImage.load("background/display_A_watch_00030.png");
    counter = 30;
    
    bubbleController = new BubbleController();
    bubbleController->setup(ofVec2f(0, ofGetHeight()));
}

//--------------------------------------------------------------
void ofApp::update(){
    bubbleController->update();
    loadImage();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    bgImage.draw(0, 0, 1920, 1080);
    bubbleController->draw();
    
    // Draw frame rate for debug
    stringstream ss;
    ss << "framerate: " << ofToString(ofGetFrameRate(), 0);
    ofDrawBitmapString(ss.str(), ofGetWidth() / 2, ofGetHeight() / 2);
}

//--------------------------------------------------------------
void ofApp::loadImage() {
    stringstream fileName;
    fileName << "background/display_A_watch_00";
    
    if (counter < 100) {
        fileName << "0" << counter;
    } else {
        fileName << counter;
    }
    
    fileName << ".png";
    
    bgImage.load(fileName.str());
    
    counter++;
    
    if (counter > 360) {
        counter = 30;
    }
}
