//
//  Result.cpp
//  Logic
//
//  Created by Ryan Bartley on 4/12/13.
//
//

#include "Result.h"
#include "Wire.h"
#include "Gate.h"
#include "ColorScheme.h"


Result::Result(ofVec2f p, vector<EState> expRes)
{
    pos = p;
    portsNum = expRes.size();
    expectedResult = expRes;
    
    gotResult = false;
    resultSet = false;
    size = ofVec2f(25,25);
    totalSize = ofVec2f(300, 100);
    
    initPorts();
    initPads();
}

Result::~Result()
{
    result.clear();
}

void Result::initPorts()
{
    // add input top ports
    for (int i=0; i<portsNum; i++)
    {
        float x = portsNum*size.x/2 - size.x/2 - i*size.x;
        float y = -(portsNum+1)*size.y/2 - 25;
        GatePort *gp = new GatePort(this, ofVec2f(x, y), GATEPORT_INPUTTOP);
        inputsTop.push_back(gp);
    }
    
}

void Result::initPads()
{
    pads[0] = TouchPad(ofVec2f(0, -totalSize.y/2-50), 50);
}


bool Result::connectToInputs(vector<Wire*> wires, GatePortType type)
{
    if (wires.size() != portsNum)
        return false;
    
    for (int i=0; i<portsNum; i++)
    {
        if (type == GATEPORT_INPUTTOP)
        {
            inputsTop[i]->connect(wires[i]);
        }
        pads[0].connected = true;
    }
        
    return true;
}

vector<Wire*> Result::getWires(GatePortType t)
{
    vector<Wire*> wires;
    
    if (t == GATEPORT_INPUTTOP)
    {
        for (int i=0; i<portsNum; i++)
        {
            wires.push_back(inputsTop[i]->wire);
        }
    }
    
    return wires;
}

void Result::disconnectWires(GatePortType t, vector<Wire*> wires)
{
    if (t == GATEPORT_INPUTTOP)
    {
        for (int i=0; i<portsNum; i++)
        {
            inputsTop[i]->disconnect();
        }
        pads[0].connected = false;
    }
}

void Result::setPosition(ofVec2f p)
{
    return;
}

vector<EState> Result::getResult()
{
    vector<EState> res;
    
    if (portsNum != inputsTop.size())
        return res;
    
    for (int i=0; i<portsNum; i++)
    {
        res.push_back(inputsTop[i]->getStateImmediately());
    }

    return res;
}

GatePortType Result::isTouchingPads(ofVec2f p)
{
    p-=pos;
    if (pads[0].enabled && pads[0].contains(p))
    {
        pads[0].press();
        return GATEPORT_INPUTTOP;
    }
    
    return GATEPORT_UNKNOWN;
}

void Result::hideAllPads()
{
    pads[0].setVisible(false, 0);
}

void Result::releaseAllPads()
{
    pads[0].release();
}

void Result::releasePad(GatePortType t)
{
    if (t == GATEPORT_INPUTTOP)
        pads[0].release();
}

void Result::holdPad(bool hold, GatePortType t)
{
    if (t == GATEPORT_INPUTTOP)
        pads[0].hold(hold);
}

bool Result::isPadConnected(GatePortType t)
{
    if (t == GATEPORT_INPUTTOP)
        return pads[0].connected;
    
    return false;
}

bool Result::contains(ofVec2f p)
{
    if (p.distance(pos)<50)
        return true;
    
    return false;
}

void Result::pickUp()
{
    pads[0].setVisible(true, 0);
}

void Result::putDown()
{
    pads[0].setVisible(false, 40);
}

void Result::oscilateInputPads(bool on)
{
    if (!pads[0].connected)
        pads[0].oscilate(on);
}


void Result::reset()
{
    for (int i=0; i<inputsTop.size(); i++)
    {
        inputsTop[i]->reset();
    }
}

void Result::update()
{
    pads[0].update();
}

void Result::draw()
{

    ofPushMatrix();
    ofTranslate(pos);
    
    ofFill();
    ofSetColor(100);
    ofRectRounded(-totalSize/2, totalSize.x, totalSize.y, 5);
    ofSetColor(160);
    ofNoFill();
    ofRectRounded(-totalSize/2, totalSize.x, totalSize.y, 5);
    
    /* draw colored squares inside the gate that respresent the ports status */
    for (int i=0; i<portsNum; i++)
    {
        inputsTop[i]->draw();
        
        ofFill();
        // draw left input
        if (inputsTop[i]->getState() == HIGH)
            ofSetColor(ColorScheme::getColor(i));
        else
            ofSetColor(ColorScheme::getColor(i)*0.3);
        
        ofRect(portsNum*size.x/2 - (i+1)*size.x+4, portsNum*size.y/2-50, size.x-8, size.y-8);
        
        if (expectedResult[i] == HIGH)
            ofSetColor(ColorScheme::getColor(i));
        else
            ofSetColor(ColorScheme::getColor(i)*0.3);
        ofRect(portsNum*size.x/2 - (i+1)*size.x+4, portsNum*size.y/2-8, size.x-8, size.y-8);
    }
    
    pads[0].draw();
    
    ofPopMatrix();
}
