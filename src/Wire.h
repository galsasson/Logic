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
class Electricity;

class Wire {
    EState          state;
    
    vector<ofVec2f> points;
    
    ofVec2f start, end;
    
    bool            shootSignal;
    float           signalPos;
    
    float           step;
    
    Electricity*    electricity;
    bool            drawElec;
    
    ofVec2f*        translate;
    
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
    
    //keeping the steps correct
    void setStep(float step) {this->step = step;};
    
    void setSource(ofVec2f s);
    void setTarget(ofVec2f t);
    
    void moveElectricity();
    
    Electricity* getElectricity();

    void draw();
    
    float getPathLength();
    
private:
    
};



