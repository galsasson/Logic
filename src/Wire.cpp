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
#include "ColorScheme.h"

#define POINTS_NUM  100

Wire::Wire()
{
    input = NULL;
    output = NULL;
    
    shootSignal = false;
    signalPos = 0;
    
    points.push_back(ofVec2f(0,0));
    points.push_back(ofVec2f(0,0));
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
    shootSignal = true;
}

void Wire::reset()
{
    state = FLOATING;
    
    signalPos = 0;
    shootSignal = false;
}

void Wire::setSource(ofVec2f source)
{
    points[0] = source;
}

void Wire::setTarget(ofVec2f target)
{
    points[1] = target;
}

void Wire::moveElectricity()
{
    if (shootSignal)
    {
        signalPos+=20;
        if (signalPos > getPathLength())
        {
            output->setState(state);
            signalPos = getPathLength();
            shootSignal = false;
        }
    }
    
}

void Wire::draw()
{
    
    float lengthPassed = 0;
    // for every line in the wire path (points)
    for (int i=1; i<points.size(); i++)
    {
        ofPushMatrix();
        ofVec2f vec = points[i]-points[i-1];
        float length = vec.length();
        ofTranslate(points[i-1]);
        ofRotate(ofRadToDeg(atan2(vec.y, vec.x)));

        // draw the line off
        ofSetColor(ColorScheme::getWireOff());
        ofSetLineWidth(3);
        ofLine(0, 0, length, 0);
    
        // draw the wire on
        if (state == HIGH)
        {
            if (signalPos >= lengthPassed + length)
            {
                // draw the entire wire on
                ofSetColor(ColorScheme::getWireOn());
                ofLine(0, 0, length, 0);
            }
            else if (signalPos > lengthPassed)
            {
                // draw wire on until reminder
                float reminder = signalPos - lengthPassed;
                ofSetColor(ColorScheme::getWireOn());
                ofLine(0, 0, reminder, 0);
                
                // draw the glowing tip
                if (shootSignal)
                {
                    ofSetLineWidth(2);
                    ofSetColor(255, 255, 255);
                    ofLine(reminder-10, 0, reminder, 0);
                }
            }
        }
        
        lengthPassed += length;
        ofPopMatrix();
        
    }
    
}

float Wire::getPathLength()
{
    float length = 0;
    
    for (int i=1; i<points.size(); i++)
    {
        length += (points[i] - points[i-1]).length();
    }
    
    return length;
}

