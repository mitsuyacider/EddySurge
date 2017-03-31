//
//  Bubble.cpp
//  EddySurge
//
//  Created by Mitstuya.WATANABE on 2017/03/31.
//
//

#include "Bubble.hpp"

void Bubble::setup(ofFbo f, ofVec2f pos) {

    ofPixels pixels;
    f.readToPixels(pixels);
    
    for(int y = 0; y < f.getHeight(); y+=2){
        for(int x = 0; x < f.getWidth(); x+=2){
            ofColor c = pixels.getColor(x, y);
            if (c == 255) {
                tigerPoints.push_back(ofVec2f(x + ofRandom(-2, 2) + pos.x ,y + ofRandom(-2, 2)) + pos.y);
                speeds.push_back(ofVec2f(ofRandom(0.5, 2), ofRandom(0.05, 0.2)));
                yPos.push_back(0);
                radius.push_back(ofRandom(1, 3));
            }
        }
    }
}

void Bubble::update() {
    
}

void Bubble::draw() {
    ofPushMatrix();
    ofPushStyle();
    ofNoFill();
    for(int i = 0; i < tigerPoints.size(); i++){
        ofVec3f p;
        p.x = tigerPoints[i].x;
        p.y = tigerPoints[i].y - yPos[i] + ofGetHeight() / 2;
        
        ofDrawCircle(p.x, p.y, radius[i], radius[i]);
        
        yPos[i] += speeds[i].y;
    }
    ofPopStyle();
    ofPopMatrix();
}
