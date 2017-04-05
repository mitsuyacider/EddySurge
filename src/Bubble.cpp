//
//  Bubble.cpp
//  EddySurge
//
//  Created by Mitstuya.WATANABE on 2017/03/31.
//
//

#include "Bubble.hpp"

Bubble::Bubble() {
}

Bubble::~Bubble() {
    tigerPoints.clear();
    tigerPoints.shrink_to_fit();
    
    speeds.clear();
    speeds.shrink_to_fit();
    
    yPos.clear();
    yPos.shrink_to_fit();

    radius.clear();
    radius.shrink_to_fit();

    wave.clear();
    wave.shrink_to_fit();
    
    acceleration.clear();
    acceleration.shrink_to_fit();
    
    amplitude.clear();
    amplitude.shrink_to_fit();
    
    noFills.clear();
    noFills.shrink_to_fit();
    
    colors.clear();
    colors.shrink_to_fit();
    
    smallAmplitudes.clear();
    smallAmplitudes.shrink_to_fit();
}

void Bubble::setup(ofPixels pixels, ofVec2f pos, int id) {
    
    for(int y = 0; y < pixels.getHeight(); y+=12) {
        for(int x = 0; x < pixels.getWidth(); x+=12) {
            ofColor c = pixels.getColor(x, y);
            if (c == 255) {
                tigerPoints.push_back(ofVec2f(x + ofRandom(-2, 2) + pos.x ,y + ofRandom(-2, 2)) + pos.y);
                speeds.push_back(ofRandom(1.5, 1.6));
                yPos.push_back(0);
                radius.push_back(ofRandom(1, 5));
                acceleration.push_back(ofRandom(0.01, 0.08));
                wave.push_back(ofRandom(0, 360));

                float amp = ofRandom(1, 5);
                smallAmplitudes.push_back(amp);
                
                amp += ofRandom(1, 5);
                amplitude.push_back(amp);
                /*
                 bool bFill = ofRandom(5) < 4;
                 noFills.push_back(false);
                 */
                noFills.push_back(true);
                
                
                int alpha = ofRandom(ofRandom(200, 255));
                ofColor color(255, 255, 255, alpha);
                colors.push_back(color);
            }
        }
    }
    
    didNotify = false;
    didDelete = false;
    bubbleId = id;
    
    startTime = ofGetElapsedTimeMillis() / 1000;
    
}

void Bubble::update() {
    
}

void Bubble::draw() {
//    ofPushMatrix();
    ofPushStyle();
    
    int count = 0;
    int timeCount = (ofGetElapsedTimeMillis() / 1000) - startTime;
    
    for(int i = 0; i < tigerPoints.size(); i++){
        
        if (noFills[i]) {
            ofFill();
        } else {
            ofNoFill();
        }
        
        ofSetColor(colors[i]);
        
        ofVec3f p;
//        float amp = yPos[i] < ofGetHeight() / 2 ? smallAmplitudes[i] : amplitude[i];
        float amp = smallAmplitudes[i];
        p.x = tigerPoints[i].x + sin(ofDegToRad(ofGetElapsedTimeMillis() / 5) + wave[i]) * amp;
        p.y = tigerPoints[i].y - yPos[i] + ofGetHeight();
        
        ofDrawCircle(p.x, p.y, radius[i], radius[i]);
        
        if (yPos[i] > ofGetHeight() / 2) {
            yPos[i] += speeds[i] + acceleration[i] * timeCount;
        } else {
            yPos[i] += 1.5;
        }
        
        /*
        if (i == 0  && yPos[i] > ofGetHeight() / 2 && !didNotify) {
            didNotify = true;
            // Notify
            ofNotifyEvent(onReach, bubbleId);
        }
         */
        
        if (timeCount > kNotificateTime && !didNotify) {
            didNotify = true;
            // Notify
            ofNotifyEvent(onReach, bubbleId);
        }
        
        // Check if all bubble is out of boarder
        if (p.y < 0) {
            count++;
        }
    }
    
    if (count == tigerPoints.size() && !didDelete) {
//        printf("will delete");
        didDelete = true;
        
        ofNotifyEvent(onDelete, bubbleId);
    }
    
    ofPopStyle();
//    ofPopMatrix();
}
