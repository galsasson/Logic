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
    
public:
    
    Not(ofVec2f p, int pNum);
    ~Not();
    
    virtual bool connectToInputs(vector<Wire*> wires, GatePortType type);
    virtual bool connectToOutputs(vector<Wire*> wires);
    
    EState getStateImmediately(GatePort *gp);
    void setState(GatePort *gp, EState s);
    void reset();
    
    void draw();
};
