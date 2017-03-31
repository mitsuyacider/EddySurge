#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // フォントの設定
    // Font setting
    myFont.load("font/Arial Black.ttf",  60, true, true, true, 0.3, 0);
    
    // Text Setting
    text = "2017.03.31 12:00:00";
    // Particle radius
    radius = 2;
    
    // Type of ofTTFCharacter to insert vector
    vector<ofTTFCharacter> str = myFont.getStringAsPoints(text);
    // Center position of string
    ofPoint center = ofPoint(myFont.stringWidth(text)/2, myFont.stringHeight(text)/2);
    // Caluulate shitf
    ofPoint shift = ofPoint(ofGetWidth()/2, ofGetHeight()/2) - center;
    
    // Loop for one character
    for(int i = 0; i < str.size(); i++){
        
        //  Loop for the outline
        for(int j = 0; j < str[i].getOutline().size(); j++) {
            
            ofPoint first, prev;
            
            // Loop for the shape of outline
            for(int k = 0; k <= str[i].getOutline()[j].size(); k++) {
                
                ofVec2f pos;
                
                if(k < str[i].getOutline()[j].size()) {
                    // Set point
                    pos = ofPoint(str[i].getOutline()[j].getVertices()[k].x,
                                  str[i].getOutline()[j].getVertices()[k].y);
                } else {
                    // When the outline is ended, return to first point
                    pos = first;
                }
                
                if(k == 0) {
                    // keep the start point
                    first = pos;
                    
                } else {
                    
                    //一つ前の点(prev)と現在の点(pos)の距離を計算する
                    float length = sqrt(pow((pos.x - prev.x),2) + pow((pos.y - prev.y),2));
                    
                    //前の点と現在の点をパーティクルで繋げるときに
                    //どのくらいの間隔でパーティクルを配置してゆくかを計算する
                    float addX = (pos.x - prev.x) * (radius / length);
                    float addY = (pos.y - prev.y) * (radius / length);
                    
                    //前の点の位置にパーティクルを置く
                    gpos.push_back(prev + shift);
                    
                    //前の点と現在の点との間に一定間隔でパーティクルを置く
                    for(int n = 0; n < (length / radius) - 1; n++){
                        prev.x += addX;
                        prev.y += addY;
                        gpos.push_back(prev + shift);
                    }
                }
                //現在の点の位置座標を記憶する
                prev = pos;
            }
        }
    }
    
    //パーティクルの目標位置の数と同じ数だけ
    //color(色情報),cpos(現在位置情報),vel(現在速度)の配列に要素を格納する
    for(int i  = 0; i < gpos.size(); i++){
        //色はx軸方向にグラデーション
        color.push_back(ofColor(120+gpos[i].x/8, 0, 122));
        //現在位置は画面内にランダムに配置
        cpos.push_back(ofPoint(ofRandom(0, ofGetHeight()), ofRandom(0, ofGetHeight())));
        //現在速度は-1から1の間でランダムに設定
        vel.push_back(ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1)));        
    }
    
    isKeyPressed = false;
    
    
    fbo.allocate(1000, 100, GL_RGBA);
    
    
    string tempStr = "12:00";
    string aChar;
    int kCharBytes = 1;
    int i = 0;
    while(!tempStr.empty()) {
        
        aChar = tempStr.substr(0, kCharBytes);
        printf("\n%s", aChar.c_str());
        ofFbo f;
        f.allocate(100, 100, GL_RGBA);
        
        f.begin();
        ofClear(0);
        ofSetColor(255);
        myFont.drawString(aChar, 0, 100);
        f.end();
        
        
        ofVec2f pos = ofVec2f(i * 25, i * 50);
        
        Bubble b;
        b.setup(f, pos);
        bubbles.push_back(b);
        
        tempStr.erase(0, kCharBytes);

        i++;
    }
    

    /*
    fbo.begin();
    ofSetColor(255);
    
    
    string s = "15:16";
    char c = s[3] ;
    myFont.drawString(string(&c), 0, 100);
    fbo.end();
    
    ofPixels pixels;
    fbo.readToPixels(pixels);
    
    
    bubble.setup(fbo);
    
    for(int y = 0; y < fbo.getHeight(); y+=2){
        for(int x = 0; x < fbo.getWidth(); x+=2){
            ofColor c = pixels.getColor(x, y);
            if (c == 255) {
                tigerPoints.push_back(ofVec2f(x + ofRandom(-2, 2) ,y + ofRandom(-2, 2)));
                speeds.push_back(ofVec2f(ofRandom(0.5, 2), ofRandom(0.1, 0.5)));
                yPos.push_back(0);
            }
        }
    }
    */
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for( int i=0; i<cpos.size(); i++){
        
        if(isKeyPressed){
            if(abs(gpos[i].x - cpos[i].x) > abs(vel[i].x)){
                cpos[i].x += vel[i].x;
            }else{
                cpos[i].x = gpos[i].x;
                vel[i].x = 0;
            }
            
            if(abs(gpos[i].y - cpos[i].y) > abs(vel[i].y)){
                cpos[i].y += vel[i].y;
            }else{
                cpos[i].y = gpos[i].y;
                vel[i].y = 0;
            }
            
        }else{
            
            if(cpos[i].x > ofGetWidth()){
                cpos[i].x =ofGetWidth();
                vel[i].x *= (-1);
            }else if(cpos[i].x < 0){
                cpos[i].x = 0;
                vel[i].x *= (-1);
            }else{
                cpos[i].x += vel[i].x;
            }
            
            if(cpos[i].y > ofGetHeight()){
                cpos[i].y = ofGetHeight();
                vel[i].y *= (-1);
            }else if(cpos[i].y < 0){
                cpos[i].y = 0;
                vel[i].y *= (-1);
            }else{
                cpos[i].y += vel[i].y;
            }
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    /*
    ofTexture texture = myFont.getFontTexture();
    ofPixels pixels;
    texture.readToPixels(pixels);
    */
    
    /*
    ofNoFill();
    for(int i=0; i<cpos.size(); i++){
        ofSetColor(color[i]);
        ofDrawCircle(cpos[i].x, cpos[i].y, radius);
    }
    */
    
    /*
    // get the string as paths
    vector < ofTTFCharacter > paths = myFont.getStringAsPoints("HELLO");
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    for (int i = 0; i < paths.size(); i++){
        
        // for every character break it out to polylines
        
        vector <ofPolyline> polylines = paths[i].getOutline();
        
        // for every polyline, draw every fifth point
        
        for (int j = 0; j < polylines.size(); j++){
            for (int k = 0; k < polylines[j].size(); k+=5){         // draw every "fifth" point
                ofDrawCircle( polylines[j][k], 3);
            }
        }
    }
    
    ofPopMatrix();
     */
    
    
//    fbo.draw(0, 0);
    
    
    /*
    ofPushStyle();
    ofNoFill();
    for(int i = 0; i < tigerPoints.size(); i++){
        ofVec3f p;
        p.x = tigerPoints[i].x;
        p.y = tigerPoints[i].y - yPos[i] + ofGetHeight() / 2;
        ofDrawCircle(p.x, p.y, 2, 2);
        
        yPos[i] += speeds[i].y;
    }
    
    
    ofPopStyle();
    */
    
    
//    bubble.draw();
    
    
    for (int i = 0; i < bubbles.size(); i++) {
        bubbles[i].draw();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    const static int ftime= 50;
    
    switch(key){
        case 'f':
            ofToggleFullscreen();
            break;
        case 'a':
            isKeyPressed = !isKeyPressed;
            for(int i=0; i<vel.size(); i++){
                vel[i].x = (isKeyPressed) ? (gpos[i].x-cpos[i].x)/ftime : ofRandom(-1, 1);
                vel[i].y = (isKeyPressed) ? (gpos[i].y-cpos[i].y)/ftime : ofRandom(-1, 1);
            }
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
