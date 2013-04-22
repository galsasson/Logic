//
//  Source.cpp
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//

#include "Wire.h"
#include "Source.h"
#include "ColorScheme.h"

Source::Source(ofVec2f p, vector<EState> bits)
{
    pos = p;
    electricity = bits;
    portsNum = bits.size();
    
    me = SOURCE;
    
    sendCounter = 0;
    sendSignal = false;
    
    size = ofVec2f(30, 70);
    
    font.loadFont("Rationale-Regular.ttf", 30);
}

bool Source::connectToOutputs(vector<Wire*> wires)
{
    if (wires.size() != portsNum)
        return false;
    
    vector<GatePort*> gps;
    
    for (int i=0; i<portsNum; i++)
    {
        float x = (portsNum)*size.x/2 - size.x/2 - i*size.x;
        float y = GATE_SQUARE_SIZE/2 + 35;
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

    // draw the ports first
    for (int i=0; i<outputs.size(); i++)
    {
        for (int j=0; j<portsNum; j++)
        {
            outputs[i][j]->draw();
        }
    }

    ofFill();
    ofSetColor(0, 0, 0, 100);
    ofRect(-size.x*portsNum/2+10, -size.y/2+10, size.x*portsNum, size.y);
    ofSetColor(40);
    ofRect(-size.x*portsNum/2, -size.y/2, size.x*portsNum, size.y);
    ofSetColor(30);
    ofRect(-size.x*portsNum/2, size.y/2-30, size.x*portsNum, 30);
    
    ofSetColor(180);
    float totalWidth = size.x*portsNum;
    for (int i=0; i<portsNum; i++)
    {
        if (electricity[portsNum-1-i] == HIGH)
            font.drawString("1", -totalWidth/2 + size.x/2 + i*size.x-5, size.y/2-35);
        else
            font.drawString("0", -totalWidth/2 + size.x/2 + i*size.x-9, size.y/2-35);
    }
    
    // draw the colored square of the outputs
    float x=-totalWidth/2+4;
    float y=size.y/2-26;
    for (int i=portsNum-1; i>=0; i--)
    {
        if (outputs[0][i]->getState() == HIGH)
            ofSetColor(ColorScheme::getColor(i));
        else
            ofSetColor(ColorScheme::getColor(i)*0.3);
        ofRect(x, y, size.x-8, 22);
        
        x+=size.x;
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
