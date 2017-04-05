//
//  Timer.cpp
//  EddySurge
//
//  Created by Mitstuya.WATANABE on 2017/04/03.
//
//

#include "Timer.hpp"

void Timer::setup(int d, int c) {
    duration = d;
    cnt = c;
    currentCnt = 0;
    isRunning = false;
}

void Timer::fire() {
    startTime = ofGetElapsedTimeMillis();
    isRunning = true;
}

void Timer::update(){
    
    if (isRunning) {
        int tmp = currentCnt;
        
        int t = ofGetElapsedTimeMillis() - startTime;
        currentCnt = floor(t / duration);
        
        if (tmp != currentCnt) {
            // Notify
            ofNotifyEvent(onCallbackTimer, currentCnt);
        }
        
        if (currentCnt == cnt) {
            isRunning = false;
            // Notify
        }
    }
}

