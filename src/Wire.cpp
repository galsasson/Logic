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
#include "Electricity.h"

#define POINTS_NUM  100

Wire::Wire()
{
    input = NULL;
    output = NULL;
    
    electricity = new Electricity();
    
    shootSignal = false;
    signalPos = 0;
    
    points.push_back(ofVec2f(0,0));
    points.push_back(ofVec2f(0,0));
    //This is to make the electricity start and stop drawing
    //It functionally doesn't work right now.
    drawElec = false;
}

Wire::~Wire()
{
//    cout<<"Wire: deleted\n";
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
    //Why aren't we doing it this way?
    //points.push_back(source);
    points[0] = source;
    electricity->setStartPosition(source);
}

void Wire::setTarget(ofVec2f target)
{
    //Why aren't we doing it this way?
    //points.push_back(target);
    points[1] = target;
}

void Wire::moveElectricity()
{
    if (shootSignal)
    {
        signalPos+=(100*step);
        drawElec = false;
        if (signalPos > getPathLength())
        {
            output->setState(state);
            signalPos = getPathLength();
            shootSignal = false;
            drawElec = false;
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
        float atanPos = ofRadToDeg(atan2(vec.y, vec.x));
        ofTranslate(points[i-1]);
        ofRotate(atanPos);
        electricity->setTranslate(points[i-1]);
        electricity->setRotate(atanPos);
        
        // draw the line off
        ofSetColor(ColorScheme::getWireOff());
        ofSetLineWidth(3);
        ofLine(0, 0, length, 0);
        
        // draw the wire on
        if (state == HIGH)
        {
            if (signalPos > lengthPassed)
            {
                // draw the entire wire on
                ofSetColor(ColorScheme::getWireOn());
                ofLine(0, 0, signalPos-lengthPassed, 0);
                //this doesn't totally work yet
                drawElec = true;
                electricity->setPosition(ofVec2f(signalPos - lengthPassed, 0));
            } else {
                //this doesn't totally work yet
                drawElec = false;
            }
        }
        else {
            
        }
    }
    
    electricity->setDraw(drawElec);
    //        lengthPassed += length;
    ofPopMatrix();
    
}



Electricity* Wire::getElectricity()
{
    return electricity;
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

