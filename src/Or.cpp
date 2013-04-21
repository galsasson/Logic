//
//  And.cpp
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//

#include "Or.h"
#include "Wire.h"

Or::Or()
{
    me = OR;
}

/*
vector<EState> Or::getGateElectricity()
{
    vector<EState> result;
    
    if (inputs.size() < 2) {
        // for now, on error, return empty vector
        return result;
    }
    
    vector<EState> e1 = inputs[0]->getWireElectricity();
    vector<EState> e2 = inputs[1]->getWireElectricity();
    
    if (e1.size() != e2.size()) {
        // for now, on error, return empty vector
        return result;
    }
    
    for (int i=0; i<e1.size(); i++)
    {
        if (e1[i] == HIGH || e2[i] == HIGH)
            result.push_back(HIGH);
        else
            result.push_back(LOW);
    }
    
    return result;
}
*/

