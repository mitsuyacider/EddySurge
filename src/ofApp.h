#pragma once

#include "ofMain.h"
#include "Bubble.hpp"
#include "Timer.hpp"
#include "AppSetting.hpp"
#include "BubbleController.hpp"
#include "SimplifiedImageDrawer.hpp"

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();
    void loadImage();
    
    int counter;
    ofImage bgImage;

    AppSetting *setting;
    BubbleController *bubbleController;
    SimplifiedImageDrawer SID;
};
