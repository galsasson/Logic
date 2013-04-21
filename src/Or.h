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

class Or : public Gate {
    
public:
    
    Or();
    ~Or();
    
    vector<EState> getGateElectricity();
};
