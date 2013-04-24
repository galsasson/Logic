//
//  TouchPad.h
//  Logic
//
//  Created by Gal Sasson on 4/23/13.
//
//

#ifndef __Logic__TouchPad__
#define __Logic__TouchPad__

#include <iostream>
#include "ofMain.h"

enum TouchPadState {
    TPSTATE_OFF,
    TPSTATE_SHOW,
    TPSTATE_ON,
    TPSTATE_DELAYHIDE,
    TPSTATE_HIDE,
    TPSTATE_OSCILATE,
    TPSTATE_HOLD,
};

class TouchPad
{
private:
    ofVec2f pos;
    float radius;
    
    TouchPadState state;
    
    bool pressed;
    
    float alpha;
    float alphaSpeed;
    float alphaAcc;
    
    float timer;
    
public:
    bool enabled;
    bool connected;

    TouchPad();
    TouchPad(ofVec2f p, float r);
    
    bool contains(ofVec2f p);
    void press();
    void release();
    void setVisible(bool is, float t);
    void hold(bool on);
    
    void oscilate(bool on);
    
    void update();
    void draw();
};

#endif /* defined(__Logic__TouchPad__) */
