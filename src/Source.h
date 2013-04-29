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
    
    TouchPad pads[1];

    
public:
    
    Source(ofVec2f p, vector<EState> bits);
    ~Source(){};
    
    void initPorts();
    void initPads();

    bool connectToOutputs(vector<Wire*> wires);
    vector<Wire*> getWires(GatePortType t);
    void disconnectWires(GatePortType t, vector<Wire*> wires);

    void setPosition(ofVec2f p) {}

    EState getStateImmediately(GatePort *gp);
    vector<EState> getGateElectricity();
    
    GatePortType isTouchingPads(ofVec2f p);
    void releaseAllPads();
    void releasePad(GatePortType t);
    void hideAllPads();
    void holdPad(bool hold, GatePortType t);
    bool isPadConnected(GatePortType t);

    bool contains(ofVec2f p);
    void pickUp();
    void putDown();
    void oscilateOutputPads(bool on);
    
    void update();
    void draw();
    void reset();
    
    void emitSignal();
};
