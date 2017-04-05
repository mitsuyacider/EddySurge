#pragma once

#include "ofMain.h"
#include "Bubble.hpp"
#include "Timer.hpp"

// Settings
static int kTimeCharaSpace = 0;
static int kTimeBoundingBox = 380;
static int kFontSize = 420;
static int kDuration = 6500;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void createTime();
        void createBubble(int bubbleId);
    
    // EventListener
    void onCallbackTimer(int &cnt);
    void onReach(int &bubbleId);
    void onDelete(int &bubbleId);
    
    ofTrueTypeFont myFont;
    vector<ofVec2f> tigerPoints;
    vector<ofVec2f> speeds;
    vector<float> yPos;
    vector<Bubble> oneDigitBubbles;
    vector<vector<Bubble *>> timeBubbles;
    vector<Bubble> bubbles;
    vector<ofPixels> bubblePixels;
    
    int speed;
    Bubble bubble;
    Timer timer;
    
};
