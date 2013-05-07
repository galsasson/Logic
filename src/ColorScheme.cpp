//
//  ColorScheme.cpp
//  Logic
//
//  Created by Gal Sasson on 4/22/13.
//
//

#include "ColorScheme.h"

ofColor ColorScheme::getColor(int index)
{
    switch (index) {
        case 0:
            return ofColor(0, 255, 255);
        case 1:
            return ofColor(0, 255, 0);
        case 2:
            return ofColor(255, 255, 0);
        case 3:
            return ofColor(255, 81, 0);
        case 4:
            return ofColor(255, 0, 124);
            
        default:
            return ofColor(255);
    }
}

ofColor ColorScheme::getWireOn()
{
//    return ofColor(191, 255, 0);
    return ofColor(230, 230, 255);
}

ofColor ColorScheme::getWireOff()
{
    return ofColor(80);
}

ofColor ColorScheme::getInventoryBackground()
{
    return ofColor(76, 0, 124);    // deep purple :)
}

ofColor ColorScheme::getShadowColor()
{
    return ofColor(0, 0, 0, 100);
}

ofColor ColorScheme::getGateBorder()
{
    return ofColor(76, 0, 124);    // deep purple :)
}

ofColor ColorScheme::getGateText()
{
    return ofColor(153, 0, 255);    // glowy purple
}
