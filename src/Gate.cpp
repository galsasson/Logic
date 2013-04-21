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

void Gate::reset()
{
    
}

void Gate::draw()
{
    
}

void Gate::update()
{
    
}

