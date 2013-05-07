//
//  And.h
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//

#pragma once

#include "Gate.h"

class Wire;

class Not : public Gate {
    
    ofVec2f size;
    ofTrueTypeFont font;
    
    TouchPad pads[2];
    
public:
    
    Not(ofVec2f p, int pNum);
    ~Not();
    
    void initPorts();
    void initPads();
    
    virtual bool connectToInputs(vector<Wire*> wires, GatePortType type);
    virtual bool connectToOutputs(vector<Wire*> wires);
    vector<Wire*> getWires(GatePortType t);
    void disconnectWires(GatePortType t, vector<Wire*> wires);
    
    void setPosition(ofVec2f p);
    
    EState getStateImmediately(GatePort *gp);
    void setState(GatePort *gp, EState s);
    
    GatePortType isTouchingPads(ofVec2f p);
    void releaseAllPads();
    void releasePad(GatePortType t);
    void hideAllPads();
    void holdPad(bool hold, GatePortType t);
    bool isPadConnected(GatePortType t);
    
    bool contains(ofVec2f p);
    bool pickUp();
    void putDown();
    void oscilateInputPads(bool on);
    void oscilateOutputPads(bool on);

    void reset();
    void update();
    void draw();
};
