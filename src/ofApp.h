#pragma once

#include "ofMain.h"
#include "Bubble.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void createTime();
    void onReach(int &bubbleId);
    void onDelete(int &bubbleId);
    void createBubble();
    
    ofTrueTypeFont myFont;
    vector<ofVec2f> tigerPoints;
    vector<ofVec2f> speeds;
    vector<float> yPos;
    int speed;
    
    Bubble bubble;
    vector<Bubble> bubbles;
    
    vector<Bubble> oneDigitBubbles;
};
