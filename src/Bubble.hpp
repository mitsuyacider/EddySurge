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
    void setup(ofFbo f, ofVec2f pos);
    void update();
    void draw();
    
    ofFbo fbo;
    vector<ofVec2f> tigerPoints;
    vector<ofVec2f> speeds;
    vector<float> yPos;
    vector<float> radius;
    ofTrueTypeFont myFont;        // font

};
