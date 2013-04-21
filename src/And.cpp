//
//  And.cpp
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//

#include "State.h"
#include "And.h"
#include "Wire.h"

And::And(ofVec2f p, int pNum)
{
    pos = p;
    portsNum = pNum;
    
    me = AND;
}

bool And::connectToInputs(vector<Wire*> wires, GatePortType type)
{
    if (wires.size() != portsNum)
        return false;
    
    for (int i=0; i<portsNum; i++)
    {
        if (type == GATEPORT_INPUTTOP)
        {
            float x = -(portsNum+2)*GATE_SQUARE_SIZE/2 + GATE_SQUARE_SIZE/2 + i*GATE_SQUARE_SIZE;
            float y = -(portsNum+1)*GATE_SQUARE_SIZE/2 - 18;
            GatePort *gp = new GatePort(this, ofVec2f(x, y), type);
            gp->connect(wires[i]);
            inputsTop.push_back(gp);
        }
        else if (type == GATEPORT_INPUTLEFT)
        {
            float x = -(portsNum+2)*GATE_SQUARE_SIZE/2 - 18;
            float y = -(portsNum+1)*GATE_SQUARE_SIZE/2 + GATE_SQUARE_SIZE/2 + i*GATE_SQUARE_SIZE;
            GatePort *gp = new GatePort(this, ofVec2f(x, y), type);
            gp->connect(wires[i]);
            inputsLeft.push_back(gp);
        }
        else if (type == GATEPORT_INPUTRIGHT)
        {
            float x = (portsNum+2)*GATE_SQUARE_SIZE/2 + 18;
            float y = -(portsNum+1)*GATE_SQUARE_SIZE/2 + GATE_SQUARE_SIZE/2 + i*GATE_SQUARE_SIZE;
            GatePort *gp = new GatePort(this, ofVec2f(x, y), type);
            gp->connect(wires[i]);
            inputsRight.push_back(gp);
        }
    }
    
    return true;
}

bool And::connectToOutputs(vector<Wire*> wires)
{
    if (wires.size() != portsNum)
        return false;
    
    vector<GatePort*> gps;
    
    for (int i=0; i<portsNum; i++)
    {
        float x = (portsNum)*GATE_SQUARE_SIZE/2 - GATE_SQUARE_SIZE/2 - i*GATE_SQUARE_SIZE;
        float y = (portsNum+1)*GATE_SQUARE_SIZE/2 + 18;
        GatePort *gp = new GatePort(this, ofVec2f(x, y), GATEPORT_OUTPUT);
        gp->connect(wires[i]);
        gps.push_back(gp);
    }
    
    outputs.push_back(gps);
    
    return true;
}

EState And::getStateImmediately(GatePort *gp)
{
    for (int i=0; i<outputs.size(); i++)
    {
        for (int j=0; j<outputs[i].size(); j++)
        {
            if (gp == outputs[i][j])
            {
                EState left = inputsLeft[j]->getStateImmediately();
                EState right = inputsRight[j]->getStateImmediately();
                if (left == FLOATING || right == FLOATING)
                    return FLOATING;
                else if (left == HIGH && right == HIGH)
                    return HIGH;
                else
                    return LOW;
            }
        }
    }
    
    // should not reach here
    return FLOATING;
}

void And::setState(GatePort *gp, EState s)
{
    for (int i=0; i<portsNum; i++)
    {
        if (gp == inputsLeft[i])
        {
            if (s == HIGH && inputsRight[i]->getState() == HIGH)
            {
                for (int set=0; set<outputs.size(); set++)
                {
                    outputs[set][i]->setState(HIGH);
                }
            }
            else {
                for (int set=0; set<outputs.size(); set++)
                {
                    outputs[set][i]->setState(LOW);
                }
            }
        }
        else if (gp == inputsRight[i])
        {
            if (s == HIGH && inputsLeft[i]->getState() == HIGH)
            {
                for (int set=0; set<outputs.size(); set++)
                {
                    outputs[set][i]->setState(HIGH);
                }
            }
            else {
                for (int set=0; set<outputs.size(); set++)
                {
                    outputs[set][i]->setState(LOW);
                }
            }
        }

    }
}

void And::reset()
{
    for (int i=0; i<outputs.size(); i++)
    {
        for (int j=0; j<outputs[i].size(); j++)
        {
            outputs[i][j]->reset();
        }
    }
    
    for (int i=0; i<portsNum; i++)
    {
        inputsLeft[i]->reset();
        inputsRight[i]->reset();
    }
}

void And::draw()
{
    ofPushMatrix();
    ofTranslate(pos);
    
    ofVec2f size = ofVec2f((portsNum+2)*GATE_SQUARE_SIZE, (portsNum+1)*GATE_SQUARE_SIZE);
    ofSetColor(10, 10, 30);
    ofFill();
    ofRect(-size.x/2, -size.y/2, size.x, size.y);
    
    for (int i=0; i<portsNum; i++)
    {
        inputsLeft[i]->draw();
        inputsRight[i]->draw();
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
