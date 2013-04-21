//
//  Source.cpp
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//

#include "Wire.h"
#include "Source.h"

Source::Source(ofVec2f p, vector<EState> bits)
{
    pos = p;
    electricity = bits;
    
    me = SOURCE;
    
    sendCounter = 0;
    sendSignal = false;
    
    portsNum = bits.size();
}

bool Source::connectToOutputs(vector<Wire*> wires)
{
    if (wires.size() != portsNum)
        return false;
    
    vector<GatePort*> gps;
    
    for (int i=0; i<portsNum; i++)
    {
        float x = (portsNum)*GATE_SQUARE_SIZE/2 - GATE_SQUARE_SIZE/2 - i*GATE_SQUARE_SIZE;
        float y = GATE_SQUARE_SIZE/2 + 18;
        GatePort *gp = new GatePort(this, ofVec2f(x, y), GATEPORT_OUTPUT);
        gp->connect(wires[i]);
        gps.push_back(gp);
    }
    
    outputs.push_back(gps);
    
    return true;
}

EState Source::getStateImmediately(GatePort *gp)
{
    for (int i=0; i<outputs.size(); i++)
    {
        for (int j=0; j<outputs[i].size(); j++)
        {
            if (gp == outputs[i][j])
            {
                return electricity[j];
            }
        }
    }
    
    // should not reach here
    return FLOATING;
}

vector<EState> Source::getGateElectricity()
{
    return electricity;
}

void Source::draw()
{
    ofPushMatrix();
    ofTranslate(pos);

    ofNoFill();
    ofSetColor(255);
    ofSetLineWidth(2);
    
    float totalWidth = GATE_SQUARE_SIZE*portsNum;
    for (int i=0; i<portsNum; i++)
    {
        ofRect(-totalWidth/2 + i*GATE_SQUARE_SIZE, -GATE_SQUARE_SIZE/2, GATE_SQUARE_SIZE, GATE_SQUARE_SIZE);
    }
    
    for (int i=0; i<outputs.size(); i++)
    {
        for (int j=0; j<portsNum; j++)
        {
            outputs[i][j]->draw();
        }
    }

    
    ofPopMatrix();
}

void Source::emitSignal()
{
    for (int i=0; i<outputs.size(); i++)
    {
        for (int j=0; j<outputs[i].size(); j++)
        {
            outputs[i][j]->setState(electricity[j]);
        }
    }
}

void Source::reset()
{
    for (int i=0; i<outputs.size(); i++)
    {
        for (int j=0; j<outputs[i].size(); j++)
        {
            outputs[i][j]->reset();
        }
    }
}
