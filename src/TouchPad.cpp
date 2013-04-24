//
//  TouchPad.cpp
//  Logic
//
//  Created by Gal Sasson on 4/23/13.
//
//

#include "TouchPad.h"
#include "ColorScheme.h"

TouchPad::TouchPad()
{
    pos = ofVec2f(0, 0);
    radius = 0;
    
    state = TPSTATE_OFF;
    
    pressed = false;
    enabled = false;
    
    alpha = 0;
    alphaSpeed = 0;
    alphaAcc = 0;
    
    timer = 0;
}

TouchPad::TouchPad(ofVec2f p, float r)
{
    pos = p;
    radius = r;
    
    state = TPSTATE_OFF;
    
    pressed = false;
    enabled = false;

    alpha = 0;
    alphaSpeed = 0;
    alphaAcc = 0;
    
    timer = 0;
}

bool TouchPad::contains(ofVec2f p)
{
    return (p.distance(pos) < radius);
}

void TouchPad::press()
{
    cout<<"touch pad pressed"<<endl;
    pressed = true;
    state = TPSTATE_ON;
}

void TouchPad::release()
{
    cout<<"touch pad released"<<endl;
    pressed = false;
}

void TouchPad::hold(bool on)
{
    if (on) {
        alpha = 100;
        alphaSpeed = 0;
        alphaAcc = 0;
        state = TPSTATE_HOLD;
    }
    else
        state = TPSTATE_HIDE;
}

void TouchPad::setVisible(bool is, float t)
{
    if (is) {
        state = TPSTATE_SHOW;
        enabled = true;
    }
    else {
        if (state == TPSTATE_SHOW)
            alpha = 100;
        alphaSpeed = 0;
        state = TPSTATE_DELAYHIDE;
        timer = t;
    }
}

void TouchPad::oscilate(bool on)
{
    enabled = true;
    timer = 0;
    if (on)
        state = TPSTATE_OSCILATE;
    else
        state = TPSTATE_HIDE;
}

void TouchPad::update()
{
    switch(state)
    {
        case TPSTATE_SHOW:
            alphaSpeed += 2;
            alpha += alphaSpeed;
            
            if (alpha>100)
            {
                alpha = 100;
                alphaAcc = 0;
                alphaSpeed = 0;
                state = TPSTATE_ON;
            }
            break;
            
        case TPSTATE_DELAYHIDE:
            if (timer==0)
                state = TPSTATE_HIDE;
            else
                timer--;
            break;
            
        case TPSTATE_HIDE:
            alphaSpeed += -2;
            alpha += alphaSpeed;
            
            if (alpha<0)
            {
                enabled = false;
                alpha = 0;
                alphaAcc = 0;
                alphaSpeed = 0;
                state = TPSTATE_OFF;
            }
            break;
        case TPSTATE_OSCILATE:
            alpha = abs(sin(timer)) * 100;
            timer+=0.3;
            break;
    }
}

void TouchPad::draw()
{
    if (alpha<1)
        return;
    
    float actualRad = radius;
    if (pressed)
    {
        actualRad *= 3;
    }

    ofPushMatrix();
    ofTranslate(pos);
    
    ofFill();
    
    ofSetColor(ColorScheme::getColor(0), alpha);
    
    ofEllipse(0, 0, actualRad, actualRad);
    
    if (state == TPSTATE_HOLD)
    {
        ofNoFill();
        ofSetLineWidth(2);
        ofSetColor(255);
        ofEllipse(0, 0, actualRad, actualRad);
        
        if (connected)
        {
            // draw X so that the user can remove the connection
            ofSetLineWidth(8);
            ofSetColor(ColorScheme::getColor(4), 100);
            ofLine(-actualRad/4, -actualRad/4, actualRad/4, actualRad/4);
            ofLine(actualRad/4, -actualRad/4, -actualRad/4, actualRad/4);
        }
    }
    
    ofPopMatrix();
}

