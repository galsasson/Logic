//
//  Wire.h
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//

#pragma once

#include "ofMain.h"
#include "State.h"
#include "GatePort.h"

class Gate;

class Wire {
    EState state;
    
    vector<ofVec2f> points;
    
    ofVec2f start, end;
    
    bool shootSignal;
    float signalPos;
    
public:
    GatePort* input;
    GatePort* output;
    

    Wire();
    ~Wire();
    
    bool setInput(GatePort* input);
    bool setOutput(GatePort* output);
    
    void reset();
    EState getWireElectricity();
    
    EState getState();
    void setState(EState s);
    
    void setSource(ofVec2f s);
    void setTarget(ofVec2f t);
    
    void moveElectricity();

    void draw();
    
private:
    float getPathLength();
};



