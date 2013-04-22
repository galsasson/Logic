//
//  Source.h
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//

#pragma once

#include "ofMain.h"
#include "Gate.h"

#define SQUARESIZE 50

class Wire;

class Source : public Gate {
    
    vector<EState> electricity;
    
    ofVec2f size;
    ofTrueTypeFont font;
    
    int sendCounter;
    bool sendSignal;
    
public:
    
    Source(ofVec2f p, vector<EState> bits);
    ~Source(){};
    
    bool connectToOutputs(vector<Wire*> wires);
    
    EState getStateImmediately(GatePort *gp);
    vector<EState> getGateElectricity();
    
    void draw();
    void reset();
    
    void emitSignal();
};
