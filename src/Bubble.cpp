//
//  Bubble.cpp
//  EddySurge
//
//  Created by Mitstuya.WATANABE on 2017/03/31.
//
//

#include "Bubble.hpp"

//--------------------------------------------------------------
Bubble::Bubble() {
    setting = &setting->sharedInstance();
    burstPosition = setting->getValue<int>("BurstPosition");
    loopDuration = setting->getValue<int>("LoopDuration");
    division = setting->getValue<int>("CircleDivision");
    
    
}


//--------------------------------------------------------------
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
    
    xPos.clear();
    xPos.shrink_to_fit();

}


//--------------------------------------------------------------
void Bubble::createRates(int total) {
    float a = 5.0;
    float y = 0.0;
    float sum = 0.0;
    
    vector<int> counts;
    for (int i = 1; i < division + 1; i++) {
        y = a * i * i + i + 10;
        sum += y;
        
        if (i == division) {
            if (sum < total) {
                y += total - sum;
                sum += total - sum;
            }
        }
        rates.push_back(y);
    }
    
    bool rev = setting->getBoolValue("ReverseQuantity");
    if (rev) {
        reverse(begin(rates), end(rates));
    }
}


//--------------------------------------------------------------
int Bubble::getCircleNum(int total, int index) {
    float rate = rates[index] / (float)total;
    int num = rate * total;
    return num;
}


//--------------------------------------------------------------
void Bubble::setup(ofPixels pixels, ofVec2f pos, int id) {
    int step = setting->getValue<int>("GridSpace");
    int total = (pixels.getHeight() / step) * (pixels.getWidth() / step);
    int minDispersion = setting->getValue<int>("MinDispersion");
    int maxDispersion = setting->getValue<int>("MaxDispersion");
    float initialVelocity = setting->getValue<float>("InitialVelocity");
    int num = 1;
    
    vector<int> counts;
    printf("\n***** total = %d", total);
    createRates(total);
    
    for (int i = 0; i < division; i++) {
        int s = getCircleNum(total, i);
        counts.push_back(s);
        printf("\ns = %d", s);
    }
    printf("\n*****");
    
    std::vector<int> circleNum(division, 0);
    
    for(int y = 0; y < pixels.getHeight(); y+=step) {
        for(int x = 0; x < pixels.getWidth(); x+=step) {
            ofColor c = pixels.getColor(x, y);
            
            
            // NOTE: Add circle for each block
             int r = 1;
             while(1) {
                 r = ofRandom(1, division);
                 int cn = circleNum[r - 1];
                 int size = counts[r - 1];
                 cn++;
                 
                 if (cn <= size) {
                     // NOTE: If the capacity is not full, insert a new value.
                     circleNum[r - 1] = cn;
                     break;
                 }
             }
            
            if (c == 255) {
                // NOTE: If the current block pixel is text, add parameters to draw circle.
                tigerPoints.push_back(ofVec2f(x + ofRandom(minDispersion, maxDispersion) + pos.x ,y + ofRandom(minDispersion, maxDispersion)) + pos.y);
                speeds.push_back(ofRandom(1.5, 1.6));
                radius.push_back(r);
                acceleration.push_back(ofRandom(0.01, 0.08));
                
                int w = ofRandom(0, 360);
                wave.push_back(w);

                float amp = ofRandom(0.5, 2);
                smallAmplitudes.push_back(amp);
                
                float x = sin(ofDegToRad(ofGetElapsedTimeMillis() / 5) + w) * amp;
                xPos.push_back(x);
                yPos.push_back(0);
                
                amp += ofRandom(1, 5);
                amplitude.push_back(amp);
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


//--------------------------------------------------------------
void Bubble::update() {
    
}


//--------------------------------------------------------------
void Bubble::draw() {
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
//        p.x = tigerPoints[i].x + sin(ofDegToRad(ofGetElapsedTimeMillis() / 5) + wave[i]) * amp;
        p.x = tigerPoints[i].x + xPos[i];
        p.y = tigerPoints[i].y - yPos[i] + ofGetHeight();
        
        
        
        
        
        /*
        if (bubbleId == 0) {
            ofDrawBitmapString("1", p.x, p.y);
        } else if (bubbleId == 1) {
            ofDrawBitmapString("2", p.x, p.y);
        } else if (bubbleId == 2) {
            ofDrawBitmapString(":", p.x, p.y);
        } else if (bubbleId == 3) {
            ofDrawBitmapString("3", p.x, p.y);
        } else if (bubbleId == 4) {
            ofDrawBitmapString("8", p.x, p.y);
        }
        */
        ofDrawCircle(p.x, p.y, radius[i], radius[i]);
        
        
        
        
        
        
        
        
        
        
        if (yPos[i] > burstPosition) {
            yPos[i] += speeds[i] + acceleration[i] * timeCount;
            xPos[i] = sin(ofDegToRad(ofGetElapsedTimeMillis() / 5) + wave[i]) * amp * acceleration[i] * timeCount;
        } else {
            yPos[i] += 1.5;
            xPos[i] = sin(ofDegToRad(ofGetElapsedTimeMillis() / 5) + wave[i]) * amp;
        }
        
        if (timeCount > loopDuration && !didNotify) {
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
        didDelete = true;
        
        ofNotifyEvent(onDelete, bubbleId);
    }
    
    ofPopStyle();
}
