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
public:

    Result(ofVec2f p, int pNum);
    ~Result();
    
    bool connectToInputs(vector<Wire*> wires, GatePortType type);

    vector<EState> getResult();
    
    void reset();
    void draw();
};
