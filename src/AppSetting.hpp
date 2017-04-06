//
//  AppSetting.hpp
//  EddySurge
//
//  Created by Mitstuya.WATANABE on 2017/04/06.
//
//

#pragma once

#ifndef AppSetting_hpp
#define AppSetting_hpp

#include <stdio.h>
#include "ofMain.h"

#endif /* AppSetting_hpp */

/* 
 NOTE: This class is singletone class for reading xml file
 */

class AppSetting {
private:
    AppSetting();
    ~AppSetting() = default;
public:
    AppSetting(const AppSetting&) = delete;
    AppSetting& operator=(const AppSetting&) = delete;
    AppSetting(AppSetting&&) = delete;
    AppSetting& operator=(AppSetting&&) = delete;
    
    static AppSetting& sharedInstance() {
        static AppSetting inst;
        return inst;
    }
    
    template <typename T> T getValue(string param);
    bool getBoolValue(string param);
    ofXml XML;
};
