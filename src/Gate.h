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
#include "TouchPad.h"

#define DEBUG 

#define STRIPWIDTH  25
#define GATE_SQUARE_SIZE 30


class Wire;
class Light;

class Gate {

protected:
    
    vector<Light*> lightBulbs;
    vector<GatePort*> inputsLeft;
    vector<GatePort*> inputsRight;
    vector<GatePort*> inputsTop;
    vector< vector<GatePort*> > outputs;
    
    ofVec2f pos;
    bool picked;
    
    //this is to see what type of gate i am
    Gates me;
    
public:
    // how many ports in this gate
    int portsNum;
    bool aboutToDelete;
    bool locked;
    
    ~Gate();
    
    virtual void loadResources();
    virtual bool connectToInputs(vector<Wire*> wires, GatePortType type);
    virtual bool connectToOutputs(vector<Wire*> wires);
    virtual vector<Wire*> getWires(GatePortType t);
    virtual void disconnectWires(GatePortType t, vector<Wire*> wires) {}
    
    virtual EState getStateImmediately(GatePort *gp);
    virtual void setState(GatePort *gp, EState s);
    
    virtual bool topInputTouched(ofVec2f p);
    virtual bool leftInputTouched(ofVec2f p);
    virtual bool rightInputTouched(ofVec2f p);
    virtual bool outputTouched(ofVec2f p);
    virtual GatePortType isTouchingPads(ofVec2f p);
    virtual void releaseAllPads() {}
    virtual void releasePad(GatePortType t) {}
    virtual void hideAllPads() {}
    virtual void holdPad(bool hold, GatePortType t) {}
    virtual bool isPadConnected(GatePortType t) { return false; }

    virtual bool contains(ofVec2f p);
    virtual bool pickUp();
    virtual void putDown();
    virtual void oscilateInputPads(bool on);
    virtual void oscilateOutputPads(bool on);
    
    virtual void reset() {}
    virtual void setup(){}
    virtual void update() {}
    virtual void draw() {}
    
    ofVec2f getWorldPosition();
    virtual void setPosition(ofVec2f p);
    
    virtual Gates getMe() { return me; };
    virtual vector<Light*> getLightBulbs() {return lightBulbs;};
    //this isn't a pixel location Vector it's for a column/row
    //position which we can then standardize
    virtual void setGridPosition(ofVec2f grid) { pos = grid; };
    virtual ofVec2f getGridPosition() { return pos; };
};
