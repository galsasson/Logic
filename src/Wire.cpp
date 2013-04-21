//
//  Wire.cpp
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//

#include "Wire.h"
#include "Gate.h"
#include "GatePort.h"

#define POINTS_NUM  100

Wire::Wire()
{
    input = NULL;
    output = NULL;
    
//    start = ofVec2f(0, 0);
//    end = ofVec2f(0, 0);
}

Wire::~Wire()
{
}

//This is so we can check up the line fast
bool Wire::setInput( GatePort* input )
{
    if (!input)
        return false;
    
    this->input = input;
    setSource(input->getWorldPosition());
    
    return true;
}

bool Wire::setOutput( GatePort* output )
{
    if (!output)
        return false;
    
    this->output = output;
    setTarget(output->getWorldPosition());
    
    return true;
}


EState Wire::getWireElectricity()
{
    //get the states up the line
    return input->getStateImmediately();
}

EState Wire::getState()
{
    return state;
}

void Wire::setState(EState s)
{
    state = s;

    // trigger the signal. the signal will start to move now.
    signalPos = 5;
}

void Wire::reset()
{
    state = FLOATING;
    
    signalPos = 0;
}

void Wire::setSource(ofVec2f source)
{
    start = source;
}

void Wire::setTarget(ofVec2f target)
{
    end = target;
}

void Wire::draw()
{
    ofVec2f vec = end-start;
    float length = vec.length();
    
    ofPushMatrix();
    ofTranslate(start);
    ofRotate(ofRadToDeg(atan2(vec.y, vec.x)));

    ofSetColor(17, 103, 138);
    ofSetLineWidth(2);
    ofLine(0, 0, length, 0);
    
    if (signalPos > 0 && signalPos <= length)
    {
        if (state == HIGH)
        {
            ofSetColor(150, 150, 205);
            ofLine(0, 0, signalPos, 0);
            ofSetColor(255, 255, 255);
            ofLine(signalPos-5, 0, signalPos, 0);
        }
        if (signalPos < length)
        {
            signalPos += 4;
            if (signalPos == length)
            {
                output->setState(state);
                signalPos = length;
            }
        }
        
        if (signalPos > length)
        {
            output->setState(state);
            signalPos = length;
        }
    }
    
    ofPopMatrix();
}

