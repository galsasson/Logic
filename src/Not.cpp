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
//    font.setLineHeight(size.y);
    
    me = NOT;
    picked = false;
    
    initPorts();
    initPads();
}

void Not::initPorts()
{
    // add input top ports
    for (int i=0; i<portsNum; i++)
    {
        float x = portsNum*size.x/2 - size.x/2 - i*size.x;
        float y = -(portsNum+1)*size.y/2 - 10;
        GatePort *gp = new GatePort(this, ofVec2f(x, y), GATEPORT_INPUTTOP);
        inputsTop.push_back(gp);
    }
        
    // add output ports
    vector<GatePort*> gps;
    for (int i=0; i<portsNum; i++)
    {
        float x = (portsNum)*size.x/2 - size.x/2 - i*size.x;
        float y = (portsNum+1)*size.y/2 + 15;
        GatePort *gp = new GatePort(this, ofVec2f(x, y), GATEPORT_OUTPUT);
        gps.push_back(gp);
    }
    outputs.push_back(gps);
}

void Not::initPads()
{
    ofVec2f totalSize = ofVec2f(portsNum*size.x, (portsNum+1)*size.y);
    
    pads[0] = TouchPad(ofVec2f(0, -totalSize.y/2-50), 50);
    pads[1] = TouchPad(ofVec2f(0, totalSize.y/2+50), 50);
}


bool Not::connectToInputs(vector<Wire*> wires, GatePortType type)
{
    if (wires.size() != portsNum)
        return false;
    
    for (int i=0; i<portsNum; i++)
    {
        if (type == GATEPORT_INPUTTOP)
        {
            inputsTop[i]->connect(wires[i]);
            pads[0].connected = true;
        }
    }
    
    return true;
}

bool Not::connectToOutputs(vector<Wire*> wires)
{
    if (wires.size() != portsNum)
        return false;
    
    for (int i=0; i<portsNum; i++)
    {
        outputs[outputs.size()-1][i]->connect(wires[i]);
    }
    pads[1].connected = true;
    
    // add output ports
    vector<GatePort*> gps;
    for (int i=0; i<portsNum; i++)
    {
        float x = (portsNum)*size.x/2 - size.x/2 - i*size.x;
        float y = (portsNum+1)*size.y/2 + 15;
        GatePort *gp = new GatePort(this, ofVec2f(x, y), GATEPORT_OUTPUT);
        gps.push_back(gp);
    }
    outputs.push_back(gps);
    
    return true;
}

vector<Wire*> Not::getWires(GatePortType t)
{
    vector<Wire*> wires;
    
    if (t == GATEPORT_INPUTTOP)
    {
        for (int i=0; i<portsNum; i++)
        {
            wires.push_back(inputsTop[i]->wire);
        }
    }
    else if (t == GATEPORT_OUTPUT)
    {
        for (int j=0; j<outputs.size()-1; j++)
        {
            for (int i=0; i<portsNum; i++)
            {
                wires.push_back(outputs[j][i]->wire);
            }
        }
    }
    
    return wires;
}

void Not::disconnectWires(GatePortType t, vector<Wire*> wires)
{
    if (t == GATEPORT_INPUTTOP)
    {
        for (int i=0; i<portsNum; i++)
        {
            inputsTop[i]->disconnect();
        }
        pads[0].connected = false;
    }
    else if (t == GATEPORT_OUTPUT)
    {
        for (int i=0; i<outputs.size()-1; i++)
        {
            if (outputs[i][0]->wire == wires[0])
                outputs.erase(outputs.begin()+i);
        }
        
        if (outputs.size()==1)
            pads[1].connected = false;
    }
}

void Not::setPosition(ofVec2f p)
{
    pos = p;
    
    for (int i=0; i<portsNum; i++)
    {
        inputsTop[i]->reconnect();
    }
    
    for (int i=0; i<outputs.size(); i++)
    {
        for (int j=0; j<portsNum; j++)
        {
            outputs[i][j]->reconnect();
        }
    }
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

GatePortType Not::isTouchingPads(ofVec2f p)
{
    p-=pos;
    if (pads[0].enabled && pads[0].contains(p))
    {
        pads[0].press();
        pads[1].setVisible(false, 0);
        return GATEPORT_INPUTTOP;
    }
    if (pads[1].enabled &&pads[1].contains(p))
    {
        pads[1].press();
        pads[0].setVisible(false, 0);
        return GATEPORT_OUTPUT;
    }
    
    return GATEPORT_UNKNOWN;
}

void Not::hideAllPads()
{
    for (int i=0; i<2; i++)
        pads[i].setVisible(false, 0);
}

void Not::releaseAllPads()
{
    for (int i=0; i<2; i++)
    {
        pads[i].release();
    }
}

void Not::releasePad(GatePortType t)
{
    if (t == GATEPORT_INPUTTOP)
        pads[0].release();
    else if (t == GATEPORT_OUTPUT)
        pads[1].release();
}

void Not::holdPad(bool hold, GatePortType t)
{
    if (t == GATEPORT_INPUTTOP)
        pads[0].hold(hold);
    else if (t == GATEPORT_OUTPUT)
        pads[1].hold(hold);
}

bool Not::isPadConnected(GatePortType t)
{
    if (t == GATEPORT_INPUTTOP)
        return pads[0].connected;
    else if (t == GATEPORT_OUTPUT)
        return pads[1].connected;
    
    return false;
}

bool Not::contains(ofVec2f p)
{
    if (p.distance(pos)<50)
        return true;
    
    return false;
}

void Not::pickUp()
{
    picked = true;
    
    for (int i=0; i<2; i++)
    {
        pads[i].setVisible(true, 0);
    }
}

void Not::putDown()
{
    picked = false;
    
    for (int i=0; i<2; i++)
    {
        pads[i].setVisible(false, 40);
    }
}

void Not::oscilateInputPads(bool on)
{
    if (!pads[0].connected)
        pads[0].oscilate(on);
}

void Not::oscilateOutputPads(bool on)
{
    pads[1].oscilate(on);
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

void Not::update()
{
    for (int i=0; i<2; i++)
    {
        pads[i].update();
    }
}

void Not::draw()
{
    ofPushMatrix();
    ofTranslate(pos);
    if (picked)
        ofScale(1.4f, 1.4f);
    
    ofVec2f totalSize = ofVec2f(portsNum*size.x, (portsNum+1)*size.y);
    ofSetColor(0, 0, 0, 100);
    ofFill();
    ofRect(-totalSize.x/2+10, -totalSize.y/2+10, totalSize.x, totalSize.y);
    ofSetColor(130);
    ofRect(-totalSize.x/2, -totalSize.y/2, totalSize.x, totalSize.y-size.y);
    ofSetColor(80);
    ofRect(-totalSize.x/2, totalSize.y/2-size.y, totalSize.x, size.y);
    ofNoFill();
    ofSetLineWidth(1);
    ofSetColor(130);
    ofRectRounded(-totalSize/2, totalSize.x, totalSize.y, 5);
    ofSetColor(200);
    ofRectRounded(-totalSize/2, totalSize.x, totalSize.y-size.y, 5);

    
    /* draw colored squares inside the gate that respresent the ports status */
    ofFill();
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
    
    // draw the touch pads
    for (int i=0; i<2; i++)
    {
        pads[i].draw();
    }
    
    ofPopMatrix();
}
