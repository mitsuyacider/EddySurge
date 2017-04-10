//
//  BubbleController.cpp
//  EddySurge
//
//  Created by Mitstuya.WATANABE on 2017/04/06.
//
//

#include "BubbleController.hpp"

//--------------------------------------------------------------
BubbleController::BubbleController() {
    cycloneMode = false;
}


//--------------------------------------------------------------
BubbleController::~BubbleController() {
    
}


//--------------------------------------------------------------
void BubbleController::setup(ofVec2f pos) {
    setting = &setting->sharedInstance();
    fontSize = setting->getValue<int>("FontSize");
    
    // Font setting
    myFont.load("font/Arial Black.ttf",  fontSize, true, true, true, 0.3, 0);
    
    // Create pixels
    createTime();

    initialPos = pos;
    
    // Create time
    int tiltDuration = setting->getValue<int>("TiltDuration");
    if (tiltDuration < 100) {
        
        for (int i = 0; i < 5; i++) {
            createBubble(i);
        }
    } else {
        timer.setup(tiltDuration, 4);
        ofAddListener(timer.onCallbackTimer, this, &BubbleController::onCallbackTimer);
        timer.fire();
        
        createBubble(0);
    }    
}


//--------------------------------------------------------------
void BubbleController::update() {
    if (timer.currentCnt < 4) {
        timer.update();
    }
}


//--------------------------------------------------------------
void BubbleController::draw() {
    if (!timeBubbles.empty()) {
        vector<vector<Bubble *>> v2;
        copy(timeBubbles.begin(), timeBubbles.end(), back_inserter(v2) );
        
        for (int i = 0; i < v2.size(); i++) {
            for (int j = 0; j < v2[i].size(); j++) {
                v2[i][j]->draw();
            }
        }
        v2.clear();
        v2.shrink_to_fit();
    }
}


//--------------------------------------------------------------
void BubbleController::onCallbackTimer(int &cnt) {
    createBubble(cnt);
}


//--------------------------------------------------------------
void BubbleController::createTime() {
    string tempStr = "0123456789:";
    string aChar;
    int kCharBytes = 1;
    int i = 0;
    while(!tempStr.empty()) {
        aChar = tempStr.substr(0, kCharBytes);
        ofFbo f;
        f.allocate(fontSize, fontSize, GL_RGBA);
        
        f.begin();
        ofClear(0);
        ofSetColor(255);
        myFont.drawString(aChar, 0, fontSize);
        f.end();
        
        ofPixels pixels;
        f.readToPixels(pixels);
        bubblePixels.push_back(pixels);
        
        tempStr.erase(0, kCharBytes);
        f.clear();
        i++;
    }
}

//--------------------------------------------------------------
void BubbleController::onReach(int &bubbleId) {
    //    printf("\nof event listener");
    createBubble(bubbleId);
}

//--------------------------------------------------------------
void BubbleController::onDelete(int &bubbleId) {
    if (timeBubbles[bubbleId].size() > 1) {
        
        Bubble *b = timeBubbles[bubbleId][0];
        ofRemoveListener(b->onReach, this, &BubbleController::onReach);
        ofRemoveListener(b->onDelete, this, &BubbleController::onDelete);
        timeBubbles[bubbleId].erase(timeBubbles[bubbleId].begin());
        delete b;
    }
}

//--------------------------------------------------------------
void BubbleController::createBubble(int bubbleId) {
    string s;
    ofPixels pixels;
    int colonMargin = setting->getValue<int>("ColonMargin");
    
    
    if (bubbleId == 0) {
        s = "1";
        pixels = bubblePixels[1];
    } else if (bubbleId == 1) {
        s = "2";
        pixels = bubblePixels[2];
    } else if (bubbleId == 2) {
        s = ":";
        pixels = bubblePixels[10];
    } else if (bubbleId == 3) {
        s = "3";
        pixels = bubblePixels[3];
    } else if (bubbleId == 4) {
        s = "8";
        pixels = bubblePixels[8];
    }
    
    int boxSize = setting->getValue<int>("TimeCharaBoundingBox");
    ofVec2f pos = ofVec2f(bubbleId * boxSize, 0);
    
    pos.x += initialPos.x;
    pos.y += initialPos.y;
    
    if (bubbleId == 2) {
        pos.x += colonMargin;
    }
    
    Bubble *b = new Bubble;
    b->setup(pixels, pos, bubbleId);
    b->cycloneMode = cycloneMode;
    int rnd = ofRandom(0, 4);
    b->burstPosition = setting->getArrayValue("BurstPositions")[rnd].asInt();
    ofAddListener(b->onReach,this, &BubbleController::onReach);
    ofAddListener(b->onDelete,this, &BubbleController::onDelete);
    
    if (timeBubbles.empty() || timeBubbles.size() < 6) {
        std::vector<Bubble *> vb{b};
        timeBubbles.push_back(vb);
    } else {
        timeBubbles[bubbleId].push_back(b);
    }
}
