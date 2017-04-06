//
//  Bubble.cpp
//  EddySurge
//
//  Created by Mitstuya.WATANABE on 2017/03/31.
//
//

#include "Bubble.hpp"

Bubble::Bubble() {
    setting = &setting->sharedInstance();
    burstPosition = setting->getValue("BurstPosition");
    loopDuration = setting->getValue("loopDuration");
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

int Bubble::getCircleNum(int total, int index) {
    /*
    vector<int> counts;
    for (int i = 0; i < 10; i++) {
        int num = getRate(i) * total;
        counts.push_back(num);
    }
    */
    
    int num = getRate(index) * total;
    return num;
}

float Bubble::getRate(int index) {
    float a = 1;
    int x = index;
    
    float y = a * x * x + x + 2;
    float sum = 0.0;
    vector<int> counts;
    for (int i = 0; i < 10; i++) {
        y = a * i * i + i + 2;
        sum += y;
        counts.push_back(y);
    }
    
    float rate = counts[x] / sum;
//    printf("\nrate %f", rate);
    return rate;
}

void Bubble::setup(ofPixels pixels, ofVec2f pos, int id) {
    
    int divide = 10;
    int step = 12;
    int total = (pixels.getHeight() / step) * (pixels.getWidth() / step);
    int distance = total / divide;
    
    vector<int> counts;
    int num = 1;
    printf("\n***** total = %d", total);
    for (int i = 0; i < divide; i++) {
        int s = getCircleNum(total, i);
        counts.push_back(s);
    printf("\ns = %d", s);
        num += distance;
    }
    printf("\n*****");
    
    std::vector<int> circleNum(divide, 0);
    
    for(int y = 0; y < pixels.getHeight(); y+=step) {
        for(int x = 0; x < pixels.getWidth(); x+=step) {
            ofColor c = pixels.getColor(x, y);
            if (c == 255) {
                tigerPoints.push_back(ofVec2f(x + ofRandom(-2, 2) + pos.x ,y + ofRandom(-2, 2)) + pos.y);
                speeds.push_back(ofRandom(1.5, 1.6));
                yPos.push_back(0);
                
                /*
                int r = 1;
                while(1) {
                    r = ofRandom(1, divide);
                    int cn = circleNum[r - 1];
                    int size = counts[r - 1];
                    cn++;
                    
                    if (cn <= size) {
                        circleNum[r - 1] = cn;
                        break;
                    }
                }
                */
                
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
        
//        ofDrawCircle(p.x, p.y, radius[i], radius[i]);
        
        
        
        
        
        
        
        
        
        
        if (yPos[i] > burstPosition) {
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
//        printf("will delete");
        didDelete = true;
        
        ofNotifyEvent(onDelete, bubbleId);
    }
    
    ofPopStyle();
//    ofPopMatrix();
}
