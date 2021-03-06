//
//  GatePort.cpp
//  Logic
//
//  Created by Gal Sasson on 4/20/13.
//
//

#include "GatePort.h"
#include "Wire.h"
#include "Gate.h"
#include "ColorScheme.h"

GatePort::GatePort(Gate *parent, ofVec2f p, GatePortType t)
{
    this->parent = parent;
    pos = p;
    type = t;
    state = FLOATING;
    
    wire = NULL;
}

GatePort::~GatePort()
{
//    cout<<"GatePort: deleted\n";
}

void GatePort::connect(Wire *w)
{
    wire = w;
    
    /* explanation: 
     * If I'm an OUTPUT gateport I should be connected to the input of the wire.
     * If I'm an INPUT gateport I should be connected to the output of the wire.
     */
    if (type == GATEPORT_OUTPUT)
        wire->setInput(this);
    else
        wire->setOutput(this);
}

void GatePort::reconnect()
{
    if (wire)
    {
        connect(wire);
    }
}

void GatePort::disconnect()
{
    wire = NULL;
}

EState GatePort::getStateImmediately()
{
    if (type == GATEPORT_OUTPUT)
    {
        // ask the gate for the status
        return parent->getStateImmediately(this);
    }
    else
    {
        // ask the wire for the status
        if (wire)
            return wire->getWireElectricity();
        else
            return FLOATING;
    }
}

EState GatePort::getState()
{
    return state;
}

void GatePort::setState(EState s)
{
    state = s;
    
    if (type == GATEPORT_OUTPUT)
    {
        // send the state down the wire
        if (wire != NULL)
            wire->setState(s);
    }
    else {
        // update the gate about the new state
        parent->setState(this, s);
    }
}

ofVec2f GatePort::getWorldPosition()
{
    return parent->getWorldPosition() + pos;
}

void GatePort::reset()
{
    state = FLOATING;
}

void GatePort::draw()
{
    ofPushMatrix();
    ofTranslate(pos);
    
    if (state == HIGH) {
        ofSetColor(ColorScheme::getWireOn());
        ofFill();
        ofEllipse(0, 0, 12, 12);
    }
    else {
        ofSetColor(ColorScheme::getWireOff());
    }
    
    ofNoFill();
    ofSetLineWidth(2);
    ofEllipse(0, 0, 12, 12);
    
    ofPopMatrix();
}
