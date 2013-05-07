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
    
    isCorrect = false;
    resultSet = false;
    showResultCounter = 0;
    size = ofVec2f(30,30);
    totalSize = ofVec2f(portsNum*size.x+50, size.y*2+20);
    
    locked = true;
    
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
        float y = -totalSize.y/2 - 15;
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

bool Result::pickUp()
{

    return false;
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

bool Result::isDataIn()
{
    // check if we have result
    for (int i=0; i<portsNum; i++)
    {
        if (inputsTop[i]->getState() == FLOATING)
        {
            return false;
        }
    }
    
    return true;
}

bool Result::haveCorrectResult()
{
    vector<EState> res = getResult();
    for (int i=0; i<res.size(); i++)
    {
        if (res[i] != expectedResult[i])
        {
            return false;
        }
    }
    
    return true;
}

void Result::startShowingResult(bool correct)
{
    resultSet = true;
    isCorrect = correct;
    
    showResultCounter = PI*4;
}


void Result::reset()
{
    for (int i=0; i<inputsTop.size(); i++)
    {
        inputsTop[i]->reset();
    }
    
    resultSet = false;
    isCorrect = false;
    showResultCounter = 0;
}

void Result::update()
{
    pads[0].update();
    
    // we are currently showing the result
    if (showResultCounter>0)
    {
        showResultCounter -= 0.3;
        if (showResultCounter <= 0)
        {
            showResultCounter = 0;
        }
    }
}

void Result::draw()
{

    ofPushMatrix();
    ofTranslate(pos);

    ofNoFill();
    for (int i=0; i<3; i++)
    {
        ofSetLineWidth(5-i*2);
        ofSetColor(ColorScheme::getGateBorder(), 155+i*50);
        ofRectRounded(-totalSize/2, totalSize.x, totalSize.y, 5);
    }
    
    ofSetColor(ColorScheme::getGateBorder());
    ofLine(-totalSize.x/2+10, 0, totalSize.x/2-10, 0);
    
    /* draw colored squares inside the gate that respresent the ports status */
    for (int i=0; i<portsNum; i++)
    {
        inputsTop[i]->draw();
        
        ofFill();
        // draw top input
        if (inputsTop[i]->getState() == HIGH)
            ofSetColor(ColorScheme::getColor(i));
        else
            ofSetColor(ColorScheme::getColor(i)*0.3);
        
        ofRect(portsNum*size.x/2 - (i+1)*size.x+4, -totalSize.y/2+10, size.x-8, size.y-8);
        
        if (expectedResult[i] == HIGH)
            ofSetColor(ColorScheme::getColor(i));
        else
            ofSetColor(ColorScheme::getColor(i)*0.3);
        ofRect(portsNum*size.x/2 - (i+1)*size.x+4, 10, size.x-8, size.y-8);
    }
    
    pads[0].draw();
    
    // draw the result bounding box (green / red)
    if (resultSet)
    {
        if (isCorrect)
        {
            ofSetColor(0, 255, 0, abs(cos(showResultCounter))*255);
        }
        else
        {
            ofSetColor(255, 0, 0, abs(cos(showResultCounter))*255);
        }
        ofNoFill();
        ofSetLineWidth(4);
        ofRectRounded(-totalSize/2, totalSize.x, totalSize.y, 5);
    }
    
    ofPopMatrix();
}
