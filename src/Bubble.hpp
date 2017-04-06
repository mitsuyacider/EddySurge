//
//  Bubble.hpp
//  EddySurge
//
//  Created by Mitstuya.WATANABE on 2017/03/31.
//
//

#pragma once

#ifndef Bubble_hpp
#define Bubble_hpp

#include <stdio.h>
#include "ofMain.h"
#include "AppSetting.hpp"

#endif /* Bubble_hpp */

// Settings

class Bubble {

public:
    Bubble();
    ~Bubble();

    void setup(ofPixels pixels, ofVec2f pos, int id);
    void update();
    void draw();
    int getCircleNum(int total, int index);
    float getRate(int index);
    
    vector<ofVec2f> tigerPoints;
    vector<float> speeds;
    vector<float> yPos;
    vector<float> radius;
    vector<float> acceleration;
    vector<float> wave;
    vector<float> amplitude;
    vector<float> smallAmplitudes;
    vector<bool> noFills;
    vector<ofColor> colors;
    
    
    ofTrueTypeFont myFont;

    ofEvent<int> onReach;
    ofEvent<int> onDelete;
    bool didNotify;
    bool didDelete;
    int bubbleId;
    int startTime;
    int burstPosition;
    int loopDuration;
    AppSetting *setting;
};
