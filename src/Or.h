//
//  And.h
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//

#pragma once

#include "Gate.h"
#include "ofMain.h"

class Wire;

class Or : public Gate {

    ofVec2f size;
    ofTrueTypeFont font;
    
public:
    
    Or(ofVec2f p, int pNum);
    ~Or();
    
    virtual bool connectToInputs(vector<Wire*> wires, GatePortType type);
    virtual bool connectToOutputs(vector<Wire*> wires);
    
    EState getStateImmediately(GatePort *gp);
    void setState(GatePort *gp, EState s);
    void reset();
    
    void draw();
};
