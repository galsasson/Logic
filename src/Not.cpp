//
//  Not.cpp
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//

#include "Not.h"
#include "Wire.h"
#include "ColorScheme.h"

Not::Not(ofVec2f p, int pNum)
{
    pos = p;
    portsNum = pNum;
    
    size = ofVec2f(25, 25);
    font.loadFont("Rationale-Regular.ttf", 25);
    font.setLineHeight(size.y);
    
    me = AND;
}

bool Not::connectToInputs(vector<Wire*> wires, GatePortType type)
{
    if (wires.size() != portsNum)
        return false;
    
    for (int i=0; i<portsNum; i++)
    {
        if (type == GATEPORT_INPUTTOP)
        {
            float x = portsNum*size.x/2 - size.x/2 - i*size.x;
            float y = -(portsNum+1)*size.y/2 - 10;
            GatePort *gp = new GatePort(this, ofVec2f(x, y), type);
            gp->connect(wires[i]);
            inputsTop.push_back(gp);
        }
        else if (type == GATEPORT_INPUTLEFT)
        {
            float x = -(portsNum+2)*size.x/2 - 10;
            float y = -(portsNum+1)*size.y/2 + size.y/2 + i*size.y;
            GatePort *gp = new GatePort(this, ofVec2f(x, y), type);
            gp->connect(wires[i]);
            inputsLeft.push_back(gp);
        }
        else if (type == GATEPORT_INPUTRIGHT)
        {
            float x = (portsNum+2)*size.x/2 + 15;
            float y = -(portsNum+1)*size.y/2 + size.y/2 + i*size.y;
            GatePort *gp = new GatePort(this, ofVec2f(x, y), type);
            gp->connect(wires[i]);
            inputsRight.push_back(gp);
        }
    }
    
    return true;
}

bool Not::connectToOutputs(vector<Wire*> wires)
{
    if (wires.size() != portsNum)
        return false;
    
    vector<GatePort*> gps;
    
    for (int i=0; i<portsNum; i++)
    {
        float x = (portsNum)*size.x/2 - size.x/2 - i*size.x;
        float y = (portsNum+1)*size.y/2 + 15;
        GatePort *gp = new GatePort(this, ofVec2f(x, y), GATEPORT_OUTPUT);
        gp->connect(wires[i]);
        gps.push_back(gp);
    }
    
    outputs.push_back(gps);
    
    return true;
}

EState Not::getStateImmediately(GatePort *gp)
{
    for (int i=0; i<outputs.size(); i++)
    {
        for (int j=0; j<outputs[i].size(); j++)
        {
            if (gp == outputs[i][j])
            {
                EState top = inputsTop[j]->getStateImmediately();
                if (top == FLOATING)
                    return FLOATING;
                else if (top == HIGH)
                    return LOW;
                else
                    return HIGH;
            }
        }
    }
    
    // should not reach here
    return FLOATING;
}

void Not::setState(GatePort *gp, EState s)
{
    for (int i=0; i<portsNum; i++)
    {
        if (gp == inputsTop[i])
        {
            if (s == LOW)
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

void Not::reset()
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
        inputsTop[i]->reset();
    }
}

void Not::draw()
{
    ofPushMatrix();
    ofTranslate(pos);
    
    ofVec2f totalSize = ofVec2f(portsNum*size.x, (portsNum+1)*size.y);
    ofSetColor(0, 0, 0, 100);
    ofFill();
    ofRect(-totalSize.x/2+10, -totalSize.y/2+10, totalSize.x, totalSize.y);
    ofSetColor(40);
    ofRect(-totalSize.x/2, -totalSize.y/2, totalSize.x, totalSize.y-size.y);
    ofSetColor(30);
    ofRect(-totalSize.x/2, totalSize.y/2-size.y, totalSize.x, size.y);
    
    
    /* draw colored squares inside the gate that respresent the ports status */
    float x = totalSize.x/2 - size.x + 4;
    float y = -totalSize.y/2 + 4;
    for (int i=0; i<portsNum; i++)
    {
        // draw top input
        if (inputsTop[i]->getState() == HIGH)
            ofSetColor(ColorScheme::getColor(i));
        else
            ofSetColor(ColorScheme::getColor(i)*0.3);
        ofRect(x, y, size.x-8, size.y-8);
        
        // draw outputs
        if (outputs[0][i]->getState() == HIGH)
            ofSetColor(ColorScheme::getColor(i));
        else
            ofSetColor(ColorScheme::getColor(i)*0.3);
        ofRect(portsNum*size.x/2 - (i+1)*size.x+4, portsNum*size.y/2-8, size.x-8, size.y-8);
        
        x -= size.x;
    }
    
    /* draw the ports of the gate */
    for (int i=0; i<portsNum; i++)
    {
        inputsTop[i]->draw();
    }
    
    for (int i=0; i<outputs.size(); i++)
    {
        for (int j=0; j<portsNum; j++)
        {
            outputs[i][j]->draw();
        }
    }
    
    // write test on the gate
    ofSetColor(180);
    ofRectangle rect = font.getStringBoundingBox("NOT", 0, 0);
    font.drawString("NOT", -rect.width/2, rect.height/2);
    
    ofPopMatrix();
}
