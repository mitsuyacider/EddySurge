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
class Bubble {
    
public:
    void setup(ofFbo f, ofVec2f pos, int id);
    void update();
    void draw();
    
    ofFbo fbo;
    vector<ofVec2f> tigerPoints;
    vector<float> speeds;
    vector<float> yPos;
    vector<float> radius;
    vector<float> acceleration;
    vector<float> wave;
    vector<float> amplitude;
    ofTrueTypeFont myFont;

    ofEvent<int> onReach;
    ofEvent<int> onDelete;
    bool didNotify;
    bool didDelete;
    int bubbleId;
    int startTime;
};
