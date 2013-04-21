//
//  And.cpp
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//

#include "Not.h"
#include "Wire.h"

Not::Not()
{
    me = NOT;
}

/*
vector<EState> Not::getGateElectricity()
{
    vector<EState> result;
    
    if (inputs.size() < 1) {
        // for now, on error, return empty vector
        return result;
    }
    
    vector<EState> e1 = inputs[0]->getWireElectricity();
    
    for (int i=0; i<e1.size(); i++)
    {
        if (e1[i] == HIGH)
            result.push_back(LOW);
        else
            result.push_back(HIGH);
    }
    
    return result;
}
*/
