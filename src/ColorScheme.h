//
//  ColorScheme.h
//  Logic
//
//  Created by Gal Sasson on 4/22/13.
//
//

#ifndef __Logic__ColorScheme__
#define __Logic__ColorScheme__

#include <iostream>
#include "ofMain.h"

class ColorScheme
{
public:
    
    static ofColor getColor(int index);
    static ofColor getWireOn();
    static ofColor getWireOff();
    static ofColor getInventoryBackground();
    static ofColor getShadowColor();
    static ofColor getGateBorder();
    static ofColor getGateText();

};

#endif /* defined(__Logic__ColorScheme__) */
