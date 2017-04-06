//
//  AppSetting.cpp
//  EddySurge
//
//  Created by Mitstuya.WATANABE on 2017/04/06.
//
//

#include "AppSetting.hpp"


AppSetting::AppSetting() {
    if ( XML.load("setting/setting.xml") ) {
    } else {
        printf("\nunable to load xml file. check data/ folder");
    }
}

// NOTE: If the template is not substanced, compiler will alert as non-exist template.
template int AppSetting::getValue(string param);
template float AppSetting::getValue(string param);
template <typename T>T AppSetting::getValue(string param) {
    stringstream s;
    s << "//";
    s << param;
    
    if(XML.exists(s.str())) {
        return XML.getValue<T>(s.str());
    } else {
        printf("/n*** The parameter is not found: %s", s.str().c_str());
        return 0;
    }
}

bool AppSetting::getBoolValue(string param) {
    stringstream s;
    s << "//";
    s << param;
    
    if(XML.exists(s.str())) {
        return XML.getValue<bool>(s.str());
    } else {
        printf("/n*** The parameter is not found: %s", s.str().c_str());
        return 0;
    }
}
