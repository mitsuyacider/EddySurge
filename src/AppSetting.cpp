//
//  AppSetting.cpp
//  EddySurge
//
//  Created by Mitstuya.WATANABE on 2017/04/06.
//
//

#include "AppSetting.hpp"


AppSetting::AppSetting() {
    printf("\n** app setting");
    
    if ( XML.load("setting/setting.xml") ) {
    } else {
        printf("\nunable to load xml file. check data/ folder");
    }
}

int AppSetting::getValue(string param) {
    stringstream s;
    s << "//";
    s << param;
    
    if(XML.exists(s.str())) {
        return XML.getValue<int>(s.str());
    } else {
        printf("/n*** The parameter is not found: %s", s.str().c_str());
        return 0;
    }
}
