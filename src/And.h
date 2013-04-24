//
//  And.h
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//

#pragma once

#include "Gate.h"
#include "TouchPad.h"

class And : public Gate
{
    ofVec2f squareSize;
    ofVec2f halfSquareSize;
    ofTrueTypeFont font;
    
    ofVec2f halfTextSize;
    
    TouchPad pads[3];
        
public:
    
    And(ofVec2f p, int pNum);
    ~And();
    
    void initPorts();
    void initPads();
    
    bool connectToInputs(vector<Wire*> wires, GatePortType type);
    bool connectToOutputs(vector<Wire*> wires);
    vector<Wire*> getWires(GatePortType t);
    void disconnectWires(GatePortType t);
    
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
    void pickUp();
    void putDown();
    void oscilateInputPads(bool on);
    void oscilateOutputPads(bool on);
    
    void reset();
    void update();
    void draw();
};
