//
//  Timer.hpp
//  EddySurge
//
//  Created by Mitstuya.WATANABE on 2017/04/03.
//
//

#ifndef Timer_hpp
#define Timer_hpp

#include <stdio.h>
#include "ofMain.h"
#endif /* Timer_hpp */

class Timer {
public:
    void setup(int d, int c);
    void update();
    void draw();
    void fire();
    ofEvent<int> onCallbackTimer;
    ofEvent<int> onCompletedTimer;
    
    int duration;
    int cnt;
    int startTime;
    int currentCnt;
    bool isRunning;
};
