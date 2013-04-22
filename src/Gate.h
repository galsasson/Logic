//
//  Gate.h
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//

#pragma once

#include "ofMain.h"
#include "State.h"
#include "GatePort.h"
#define DEBUG 

#define STRIPWIDTH  25
#define GATE_SQUARE_SIZE 30


class Wire;

class Gate {

protected:
    
    vector<GatePort*> inputsLeft;
    vector<GatePort*> inputsRight;
    vector<GatePort*> inputsTop;
    vector< vector<GatePort*> > outputs;
    
    ofVec2f pos;
    
    //this is to see what type of gate i am
    Gates me;
    
public:
    // how many ports in this gate
    int portsNum;
    

    virtual bool connectToInputs(vector<Wire*> wires, GatePortType type);
    virtual bool connectToOutputs(vector<Wire*> wires);
    
    virtual EState getStateImmediately(GatePort *gp);
    virtual void setState(GatePort *gp, EState s);
    virtual void reset();
    
    virtual void update();
    virtual void draw();
    
    ofVec2f getWorldPosition();
    
    virtual Gates getMe() { return me; };
    
    //this isn't a pixel location Vector it's for a column/row
    //position which we can then standardize
    virtual void setGridPosition(ofVec2f grid) { pos = grid; };
    virtual ofVec2f getGridPosition() { return pos; };
};