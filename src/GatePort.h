//
//  GatePort.h
//  Logic
//
//  Created by Gal Sasson on 4/20/13.
//
//

#ifndef __Logic__GatePort__
#define __Logic__GatePort__

#include <iostream>
#include "ofMain.h"
#include "State.h"

class Wire;
class Gate;

enum GatePortType {
    GATEPORT_OUTPUT,
    GATEPORT_INPUTLEFT,
    GATEPORT_INPUTRIGHT,
    GATEPORT_INPUTTOP,
    GATEPORT_UNKNOWN,
};

class GatePort
{
private:
    ofVec2f pos;
    Gate *parent;
    EState state;
    
public:
    GatePort(Gate *parent, ofVec2f p, GatePortType t);
    ~GatePort();

    void connect(Wire *w);
    void reconnect();
    void disconnect();
    
    EState getState();
    void setState(EState s);
    EState getStateImmediately();
    void reset();
    
    ofVec2f getWorldPosition();
    Gate* getParentGate() { return parent; }
    
    void draw();
    
    Wire *wire;    
    GatePortType type;
};

#endif /* defined(__Logic__GatePort__) */
