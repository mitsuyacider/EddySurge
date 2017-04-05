//
//  Bubble.hpp
//  EddySurge
//
//  Created by Mitstuya.WATANABE on 2017/03/31.
//
//

#ifndef Bubble_hpp
#define Bubble_hpp

#include <stdio.h>
#include "ofMain.h"

#endif /* Bubble_hpp */

// Settings
static int kNotificateTime = 20;

class Bubble {
    
public:
    Bubble();
    ~Bubble();

    void setup(ofPixels pixels, ofVec2f pos, int id);
    void update();
    void draw();
    
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
};
