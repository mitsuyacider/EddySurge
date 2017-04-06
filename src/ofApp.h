#pragma once

#include "ofMain.h"
#include "Bubble.hpp"
#include "Timer.hpp"
#include "AppSetting.hpp"

class ofApp : public ofBaseApp {

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
    
    vector<ofVec2f> tigerPoints;
    vector<ofVec2f> speeds;
    vector<float> yPos;
    vector<Bubble> oneDigitBubbles;
    vector<vector<Bubble *>> timeBubbles;
    vector<Bubble> bubbles;
    vector<ofPixels> bubblePixels;
    vector<ofImage>images;
    
    int speed;
    int counter;
    int fontSize;
    ofTrueTypeFont myFont;
    Bubble bubble;
    Timer timer;
    ofImage bgImage;

    AppSetting *setting;
};
