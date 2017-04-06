#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    setting = &setting->sharedInstance();
    fontSize = setting->getValue("FontSize");
    
    // Framerate
    ofSetFrameRate(30);
    
    // Font setting
    myFont.load("font/Arial Black.ttf",  fontSize, true, true, true, 0.3, 0);
    
    // Create pixels
    createTime();
    
    // Create time
    int tiltDuration = setting->getValue("TiltDuration");
    timer.setup(tiltDuration, 4);
    ofAddListener(timer.onCallbackTimer, this, &ofApp::onCallbackTimer);
    timer.fire();
    
    createBubble(0);
    
    bgImage.load("background/display_A_watch_00030.png");
    counter = 30;
}

void ofApp::onCallbackTimer(int &cnt) {
    createBubble(cnt);
}


//--------------------------------------------------------------
void ofApp::update(){
    if (timer.currentCnt < 4) {
        timer.update();
    }
    
    stringstream fileName;
    fileName << "background/display_A_watch_00";
    
    if (counter < 100) {
        fileName << "0" << counter;
    } else {
        fileName << counter;
    }
    
    fileName << ".png";
    
    bgImage.load(fileName.str());
    
    counter++;
    
    if (counter > 360) {
        counter = 30;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    
    bgImage.draw(0, 0, 1920, 1080);
//    images[counter].draw(0, 0, 1920, 1080);
    
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
    
    // Draw frame rate for debug
    stringstream ss;
    ss << "framerate: " << ofToString(ofGetFrameRate(), 0);
    ofDrawBitmapString(ss.str(), ofGetWidth() / 2, ofGetHeight() / 2);
    
}


//--------------------------------------------------------------
void ofApp::createTime() {
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
void ofApp::onReach(int &bubbleId) {
//    printf("\nof event listener");
    createBubble(bubbleId);
}

//--------------------------------------------------------------
void ofApp::onDelete(int &bubbleId) {
        printf("\n**** delete");
    if (timeBubbles[bubbleId].size() > 1) {
        
        Bubble *b = timeBubbles[bubbleId][0];
        ofRemoveListener(b->onReach, this, &ofApp::onReach);
        ofRemoveListener(b->onDelete, this, &ofApp::onDelete);
        timeBubbles[bubbleId].erase(timeBubbles[bubbleId].begin());
        delete b;
    }
}

//--------------------------------------------------------------
void ofApp::createBubble(int bubbleId) {
    string s;
    ofPixels pixels;
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

    int boxSize = setting->getValue("TimeCharaBoundingBox");
    ofVec2f pos = ofVec2f(bubbleId * boxSize, 0);
    
    if (bubbleId == 2) {
        pos.x += 100;
    }
    
    Bubble *b = new Bubble;
    b->setup(pixels, pos, bubbleId);
    ofAddListener(b->onReach,this, &ofApp::onReach);
    ofAddListener(b->onDelete,this, &ofApp::onDelete);

    if (timeBubbles.empty() || timeBubbles.size() < 6) {
        std::vector<Bubble *> vb{b};
        timeBubbles.push_back(vb);
    } else {
        timeBubbles[bubbleId].push_back(b);
    }
}
