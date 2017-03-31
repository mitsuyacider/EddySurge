#pragma once

#include "ofMain.h"
#include "Bubble.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    
    ofTrueTypeFont myFont;        // font
    string text;                  // text
    vector<ofColor> color; // Particle color
    vector<ofPoint> cpos;  // Particle start position
    vector<ofPoint> gpos;  // Particle goal position
    vector<ofVec2f> vel;   // Particle speed
    
    bool isKeyPressed;           // PressKey frag
    int radius;                  // Particle radius
    
    ofFbo fbo;
    vector<ofVec2f> tigerPoints;
    vector<ofVec2f> speeds;
    vector<float> yPos;
    int speed;
    
    Bubble bubble;
    vector<Bubble> bubbles;
};
