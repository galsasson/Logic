//
//  Result.h
//  Logic
//
//  Created by Ryan Bartley on 4/12/13.
//
//

#pragma once 

#include "Gate.h"

class Wire;

class Result : public Gate {
    
    vector<EState> result;
private:
    vector<float> wireResult;
    bool gotResult;
    bool resultSet;
    ofVec2f size;
    ofVec2f totalSize;
    
    TouchPad pads[1];
    
public:
    vector<EState> expectedResult;


    Result(ofVec2f p, vector<EState> expRes);
    ~Result();
    
    void initPorts();
    void initPads();
    
    bool connectToInputs(vector<Wire*> wires, GatePortType type);
    vector<Wire*> getWires(GatePortType t);
    void disconnectWires(GatePortType t);

    void setPosition(ofVec2f p);

    vector<EState> getResult();

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

    void reset();
    void update();
    void draw();
};
