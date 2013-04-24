//
//  Gate.cpp
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//

#include "Gate.h"
#include "Wire.h"

bool Gate::connectToInputs(vector<Wire*> wires, GatePortType type)
{
    return false;
}

bool Gate::connectToOutputs(vector<Wire*> wires)
{
    return false;
}

vector<Wire*> Gate::getWires(GatePortType t)
{
    vector<Wire*> wires;
    
    return wires;
}


EState Gate::getStateImmediately(GatePort *gp)
{
    return FLOATING;
}

void Gate::setState(GatePort *gp, EState s)
{
    
}

ofVec2f Gate::getWorldPosition()
{
    return pos;
}

void Gate::setPosition(ofVec2f p)
{
    pos = p;
}

bool Gate::topInputTouched(ofVec2f p)
{
    return false;
}

bool Gate::leftInputTouched(ofVec2f p)
{
    return false;
}

bool Gate::rightInputTouched(ofVec2f p)
{
    return false;
}

bool Gate::outputTouched(ofVec2f p)
{
    return false;
}

GatePortType Gate::isTouchingPads(ofVec2f p)
{
    return GATEPORT_UNKNOWN;
}

bool Gate::contains(ofVec2f p)
{
    return false;
}

void Gate::pickUp()
{
    picked = true;
}

void Gate::putDown()
{
    picked = false;
}

void Gate::oscilateInputPads(bool on)
{
    return;
}

void Gate::oscilateOutputPads(bool on)
{
    return;
}

