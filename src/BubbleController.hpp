//
//  BubbleController.hpp
//  EddySurge
//
//  Created by Mitstuya.WATANABE on 2017/04/06.
//
//

#pragma once
#ifndef BubbleController_hpp
#define BubbleController_hpp

#include <stdio.h>
#include "ofMain.h"
#include "AppSetting.hpp"
#include "Bubble.hpp"
#include "Timer.hpp"

#endif /* BubbleController_hpp */

class BubbleController {
public:
    BubbleController();
    ~BubbleController();
    
    void setup(ofVec2f pos);
    void update();
    void draw();
    void createTime();
    void createBubble(int bubbleId);
    
    // EventListener
    void onCallbackTimer(int &cnt);
    void onReach(int &bubbleId);
    void onDelete(int &bubbleId);
    
    vector<ofVec2f> particlePositions;
    vector<ofVec2f> speeds;
    vector<float> yPos;
    vector<Bubble> oneDigitBubbles;
    vector<vector<Bubble *>> timeBubbles;
    vector<Bubble> bubbles;
    vector<ofPixels> bubblePixels;
    vector<ofImage>images;
    
    ofVec2f initialPos;
    
    int speed;
    int counter;
    int fontSize;
    ofTrueTypeFont myFont;
    Bubble bubble;
    Timer timer;
    ofImage bgImage;
    
    AppSetting *setting;
    
    bool cycloneMode;
};
