#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Font setting
    myFont.load("font/Arial Black.ttf",  460, true, true, true, 0.3, 0);
    
    // Create time
//    createTime();
    
    createBubble();
//    ofRemoveListener(mySoundObject.onVolumeChange,this, &ofApp:onVolumeChange);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);

    /*
    for (int i = 0; i < bubbles.size(); i++) {
        bubbles[i].draw();
    }
    */
    
    if (!oneDigitBubbles.empty()) {
        for (int i = 0; i < oneDigitBubbles.size(); i++) {
            oneDigitBubbles[i].draw();
        }
    }
}

//--------------------------------------------------------------
void ofApp::createTime() {
    string tempStr = "12:00";
    string aChar;
    int kCharBytes = 1;
    int i = 0;
    while(!tempStr.empty()) {
        
        aChar = tempStr.substr(0, kCharBytes);
        printf("\n%s", aChar.c_str());
        ofFbo f;
        f.allocate(500, 500, GL_RGBA);
        
        f.begin();
        ofClear(0);
        ofSetColor(255);
        myFont.drawString(aChar, 0, 500);
        f.end();
        
        
        ofVec2f pos = ofVec2f(i * 260, i * 140);
        
        Bubble b;
        b.setup(f, pos, i);
        ofAddListener(b.onReach,this, &ofApp::onReach);
        ofAddListener(b.onDelete,this, &ofApp::onDelete);
        bubbles.push_back(b);
        
        tempStr.erase(0, kCharBytes);
        
        
        i++;
    }
}

//--------------------------------------------------------------
void ofApp::onReach(int &bubbleId) {
//    printf("\nof event listener");
    if (bubbleId == 0) {
        createBubble();
    }
}

//--------------------------------------------------------------
void ofApp::onDelete(int &bubbleId) {
    //    printf("\nof event listener");
    if (bubbleId == 0) {
        if (oneDigitBubbles.size() > 2) {
            Bubble b = oneDigitBubbles[0];
            oneDigitBubbles.erase(oneDigitBubbles.begin());
            delete &b;
        }
    }
}

//--------------------------------------------------------------
void ofApp::createBubble() {
    ofFbo f;
    f.allocate(500, 500, GL_RGBA);
    
    f.begin();
    ofClear(0);
    ofSetColor(255);
    myFont.drawString("1", 0, 500);
    f.end();
    
    
    ofVec2f pos = ofVec2f(0, 140);
    
    Bubble b;
    b.setup(f, pos, 0);
    ofAddListener(b.onReach,this, &ofApp::onReach);
    oneDigitBubbles.push_back(b);
    
    f.clear();
}
