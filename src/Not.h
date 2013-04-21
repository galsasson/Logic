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
    
public:
    
    Not();
    ~Not();
    
    vector<EState> getGateElectricity();
//    void processElectricity();
    
};
