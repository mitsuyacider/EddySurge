//
//  AppSetting.cpp
//  EddySurge
//
//  Created by Mitstuya.WATANABE on 2017/04/06.
//
//

#include "AppSetting.hpp"


AppSetting::AppSetting() {
    std::string file = "setting/setting.json";
    
    // Now parse the JSON
    bool parsingSuccessful = result.open(file);
    
    if (parsingSuccessful) {
    } else {
        printf("\nunable to load json file. check data/ folder");
    }
}

// NOTE: If the template is not substanced, compiler will alert as non-exist template.

template int AppSetting::getValue(string param);
template float AppSetting::getValue(string param);
template bool AppSetting::getValue(string param);
template <typename T>T AppSetting::getValue(string param) {
    
    if (typeid(T).name() == typeid(int).name()) {
        return result[param].asInt();
    } else if (typeid(T).name() == typeid(float).name()) {
        return result[param].asFloat();
    } else if (typeid(T).name() == typeid(bool).name()) {
        return result[param].asBool();
    }
}

Json::Value AppSetting::getArrayValue(string param) {
    return result[param];
}
