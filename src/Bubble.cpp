//
//  Bubble.cpp
//  EddySurge
//
//  Created by Mitstuya.WATANABE on 2017/03/31.
//
//

#include "Bubble.hpp"

void Bubble::setup(ofFbo f, ofVec2f pos, int id) {

    ofPixels pixels;
    f.readToPixels(pixels);
    
    for(int y = 0; y < f.getHeight(); y+=12){
        for(int x = 0; x < f.getWidth(); x+=12){
            ofColor c = pixels.getColor(x, y);
            if (c == 255) {
                tigerPoints.push_back(ofVec2f(x + ofRandom(-2, 2) + pos.x ,y + ofRandom(-2, 2)) + pos.y);
                speeds.push_back(ofRandom(1.5, 1.6));
                yPos.push_back(0);
                radius.push_back(ofRandom(1, 3));
                acceleration.push_back(ofRandom(0.01, 0.08));
                wave.push_back(ofRandom(0, 360));
                amplitude.push_back(ofRandom(2, 10));
            }
        }
    }
    
    didNotify = false;
    didDelete = false;
    bubbleId = id;
    
    if (bubbleId == 0) {
        printf("\nnum = %f", f.getWidth());
    }
    
    startTime = ofGetElapsedTimeMillis() / 1000;
}

void Bubble::update() {
    
}

void Bubble::draw() {
    ofPushMatrix();
    ofPushStyle();
    ofNoFill();
    int count = 0;
    int timeCount = (ofGetElapsedTimeMillis() / 1000) - startTime;
    
    for(int i = 0; i < tigerPoints.size(); i++){
        ofVec3f p;
        p.x = tigerPoints[i].x + sin(ofDegToRad(ofGetElapsedTimeMillis() / 5) + wave[i]) * amplitude[i];
        p.y = tigerPoints[i].y - yPos[i] + ofGetHeight();
        
        ofDrawCircle(p.x, p.y, radius[i], radius[i]);
        
        if (yPos[i] > ofGetHeight() / 2) {
            yPos[i] += speeds[i] + acceleration[i] * timeCount;
        } else {
            yPos[i] += 1.5;
        }
        
        if (i == 0  && yPos[i] > ofGetHeight() / 2 && !didNotify) {
            didNotify = true;
            // Notify
            ofNotifyEvent(onReach, bubbleId);
        }
        
        // Check if all bubble is out of boarder
        if (yPos[i] > ofGetHeight()) {
            count++;
        }
    }
    
    if (count == tigerPoints.size() && !didDelete) {
        printf("will delete");
        didDelete = true;
        
        ofNotifyEvent(onDelete, bubbleId);
    }
    ofPopStyle();
    ofPopMatrix();
}
