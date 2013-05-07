//
//  Or.cpp
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//

#include "Or.h"
#include "Wire.h"
#include "ColorScheme.h"

Or::Or(ofVec2f p, int pNum)
{
    pos = p;
    portsNum = pNum;
    
    size = ofVec2f(25, 25);
    font.loadFont("Rationale-Regular.ttf", 25);
    font.setLineHeight(size.y);
    
    me = OR;
    picked = false;
    
    locked = false;
    
    initPorts();
    initPads();
}

void Or::initPorts()
{
    // add input left ports
    for (int i=0; i<portsNum; i++)
    {
        float x = -(portsNum+2)*size.x/2 - 15;
        float y = -(portsNum+1)*size.y/2 + size.y/2 + i*size.y;
        GatePort *gp = new GatePort(this, ofVec2f(x, y), GATEPORT_INPUTLEFT);
        inputsLeft.push_back(gp);
    }
    
    // add input right ports
    for (int i=0; i<portsNum; i++)
    {
        float x = (portsNum+2)*size.x/2 + 15;
        float y = -(portsNum+1)*size.y/2 + size.y/2 + i*size.y;
        GatePort *gp = new GatePort(this, ofVec2f(x, y), GATEPORT_INPUTRIGHT);
        inputsRight.push_back(gp);
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

void Or::initPads()
{
    ofVec2f totalSize = ofVec2f((portsNum+2)*size.x, (portsNum+1)*size.y);
    
    pads[0] = TouchPad(ofVec2f(-totalSize.x/2-50, -size.y/2), 50);
    pads[1] = TouchPad(ofVec2f(totalSize.x/2+50, -size.y/2), 50);
    pads[2] = TouchPad(ofVec2f(0, totalSize.y/2+50), 50);
}


bool Or::connectToInputs(vector<Wire*> wires, GatePortType type)
{
    if (wires.size() != portsNum)
        return false;
    
    for (int i=0; i<portsNum; i++)
    {
        if (type == GATEPORT_INPUTLEFT)
        {
            inputsLeft[i]->connect(wires[i]);
            pads[0].connected = true;
        }
        else if (type == GATEPORT_INPUTRIGHT)
        {
            inputsRight[i]->connect(wires[i]);
            pads[1].connected = true;
        }
    }
    
    return true;
}

bool Or::connectToOutputs(vector<Wire*> wires)
{
    if (wires.size() != portsNum)
        return false;
    
    for (int i=0; i<portsNum; i++)
    {
        outputs[outputs.size()-1][i]->connect(wires[i]);
    }
    pads[2].connected = true;
    
    // add clean output ports
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

vector<Wire*> Or::getWires(GatePortType t)
{
    vector<Wire*> wires;
    
    if (t == GATEPORT_INPUTLEFT)
    {
        for (int i=0; i<portsNum; i++)
        {
            if (inputsLeft[i]->wire != NULL)
                wires.push_back(inputsLeft[i]->wire);
        }
    }
    else if (t == GATEPORT_INPUTRIGHT)
    {
        for (int i=0; i<portsNum; i++)
        {
            if (inputsRight[i]->wire != NULL)
                wires.push_back(inputsRight[i]->wire);
        }
    }
    else if (t == GATEPORT_OUTPUT)
    {
        for (int j=0; j<outputs.size()-1; j++)
        {
            for (int i=0; i<portsNum; i++)
            {
                if (outputs[j][i]->wire != NULL)
                    wires.push_back(outputs[j][i]->wire);
            }
        }
    }
    
    return wires;
}

void Or::disconnectWires(GatePortType t, vector<Wire*> wires)
{
    if (t == GATEPORT_INPUTLEFT)
    {
        for (int i=0; i<portsNum; i++)
        {
            inputsLeft[i]->disconnect();
        }
        pads[0].connected = false;
    }
    else if (t == GATEPORT_INPUTRIGHT)
    {
        for (int i=0; i<portsNum; i++)
        {
            inputsRight[i]->disconnect();
        }
        pads[1].connected = false;
    }
    else if (t == GATEPORT_OUTPUT)
    {
        for (int i=0; i<outputs.size()-1; i++)
        {
            if (outputs[i][0]->wire == wires[0])
                outputs.erase(outputs.begin()+i);
        }
        
        if (outputs.size()==1)
            pads[2].connected = false;
    }
}

void Or::setPosition(ofVec2f p)
{
    pos = p;
    
    for (int i=0; i<portsNum; i++)
    {
        inputsLeft[i]->reconnect();
        inputsRight[i]->reconnect();
    }
    
    for (int i=0; i<outputs.size(); i++)
    {
        for (int j=0; j<portsNum; j++)
        {
            outputs[i][j]->reconnect();
        }
    }
}


EState Or::getStateImmediately(GatePort *gp)
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
                else if (left == LOW && right == LOW)
                    return LOW;
                else
                    return HIGH;
            }
        }
    }
    
    // should not reach here
    return FLOATING;
}

void Or::setState(GatePort *gp, EState s)
{
    for (int i=0; i<portsNum; i++)
    {
        if (gp == inputsLeft[i] && inputsRight[i]->getState() != FLOATING)
        {
            if (s == LOW && inputsRight[i]->getState() == LOW)
            {
                for (int set=0; set<outputs.size(); set++)
                {
                    outputs[set][i]->setState(LOW);
                }
            }
            else {
                for (int set=0; set<outputs.size(); set++)
                {
                    outputs[set][i]->setState(HIGH);
                }
            }
        }
        else if (gp == inputsRight[i] && inputsLeft[i]->getState() != FLOATING)
        {
            if (s == LOW && inputsLeft[i]->getState() == LOW)
            {
                for (int set=0; set<outputs.size(); set++)
                {
                    outputs[set][i]->setState(LOW);
                }
            }
            else {
                for (int set=0; set<outputs.size(); set++)
                {
                    outputs[set][i]->setState(HIGH);
                }
            }
        }
        
    }
}

GatePortType Or::isTouchingPads(ofVec2f p)
{
    p-=pos;
    if (pads[0].enabled && pads[0].contains(p))
    {
        pads[0].press();
        pads[1].setVisible(false, 0);
        pads[2].setVisible(false, 0);
        return GATEPORT_INPUTLEFT;
    }
    if (pads[1].enabled &&pads[1].contains(p))
    {
        pads[1].press();
        pads[0].setVisible(false, 0);
        pads[2].setVisible(false, 0);
        return GATEPORT_INPUTRIGHT;
    }
    if (pads[2].enabled && pads[2].contains(p))
    {
        pads[2].press();
        pads[0].setVisible(false, 0);
        pads[1].setVisible(false, 0);
        return GATEPORT_OUTPUT;
    }
    
    return GATEPORT_UNKNOWN;
}

void Or::hideAllPads()
{
    for (int i=0; i<3; i++)
        pads[i].setVisible(false, 0);
}

void Or::releaseAllPads()
{
    for (int i=0; i<3; i++)
    {
        pads[i].release();
    }
}

void Or::releasePad(GatePortType t)
{
    if (t == GATEPORT_INPUTLEFT)
        pads[0].release();
    else if (t == GATEPORT_INPUTRIGHT)
        pads[1].release();
    else if (t == GATEPORT_OUTPUT)
        pads[2].release();
}

void Or::holdPad(bool hold, GatePortType t)
{
    if (t == GATEPORT_INPUTLEFT)
        pads[0].hold(hold);
    else if (t == GATEPORT_INPUTRIGHT)
        pads[1].hold(hold);
    else if (t == GATEPORT_OUTPUT)
        pads[2].hold(hold);
}

bool Or::isPadConnected(GatePortType t)
{
    if (t == GATEPORT_INPUTLEFT)
        return pads[0].connected;
    else if (t == GATEPORT_INPUTRIGHT)
        return pads[1].connected;
    else if (t == GATEPORT_OUTPUT)
        return pads[2].connected;
    
    return false;
}

bool Or::contains(ofVec2f p)
{
    if (p.distance(pos)<60)
        return true;
    
    return false;
}

bool Or::pickUp()
{
    if (locked)
        return false;
    
    picked = true;
    for (int i=0; i<3; i++)
    {
        pads[i].setVisible(true, 0);
    }
    
    return true;
}

void Or::putDown()
{
    picked = false;
    
    for (int i=0; i<3; i++)
    {
        pads[i].setVisible(false, 40);
    }
}

void Or::oscilateInputPads(bool on)
{
    if (!pads[0].connected)
        pads[0].oscilate(on);
    
    if (!pads[1].connected)
        pads[1].oscilate(on);
}

void Or::oscilateOutputPads(bool on)
{
    pads[2].oscilate(on);
}


void Or::reset()
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

void Or::update()
{
    for (int i=0; i<3; i++)
    {
        pads[i].update();
    }
}

void Or::draw()
{
    ofPushMatrix();
    ofTranslate(pos);
    if (picked)
        ofScale(1.4f, 1.4f);
    
    ofVec2f totalSize = ofVec2f((portsNum+2)*size.x, (portsNum+1)*size.y);
    ofVec2f halfSize = totalSize/2;

    ofNoFill();
    for (int i=0; i<3; i++)
    {
        ofSetLineWidth(5-i*2);
        ofSetColor(ColorScheme::getGateBorder(), 155+i*50);
        ofRectRounded(-totalSize/2, totalSize.x, totalSize.y, 5);
    }
    ofSetColor(ColorScheme::getGateBorder());
    ofRectRounded(-totalSize/2, totalSize.x, totalSize.y-size.y, 5);

    
    
    /* draw colored squares inside the gate that respresent the ports status */
    ofFill();
    float x = -(portsNum+2)*size.x/2 + 4;
    float y = -(portsNum+1)*size.y/2 + 4;
    for (int i=0; i<portsNum; i++)
    {
        // draw left input
        if (inputsLeft[i]->getState() == HIGH)
            ofSetColor(ColorScheme::getColor(i));
        else
            ofSetColor(ColorScheme::getColor(i)*0.3);
        ofRect(x, y, size.x-8, size.y-8);
        
        // draw right input
        if (inputsRight[i]->getState() == HIGH)
            ofSetColor(ColorScheme::getColor(i));
        else
            ofSetColor(ColorScheme::getColor(i)*0.3);
        ofRect(-x, y, -(size.x-8), size.y-8);
        
        // draw outputs
        if (outputs[0][i]->getState() == HIGH)
            ofSetColor(ColorScheme::getColor(i));
        else
            ofSetColor(ColorScheme::getColor(i)*0.3);
        ofRect(portsNum*size.x/2 - (i+1)*size.x+4, portsNum*size.y/2-8, size.x-8, size.y-8);
        
        y += size.y;
    }
    
    /* draw the ports of the gate */
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
    
    // write test on the gate
    ofSetColor(ColorScheme::getGateText());
    ofRectangle rect = font.getStringBoundingBox("OR", 0, 0);
    font.drawString("OR", -rect.width/2, 0);
    
    // draw the touch pads
    for (int i=0; i<3; i++)
    {
        pads[i].draw();
    }
    
    if (aboutToDelete)
    {
        ofFill();
        ofSetColor(255, 0, 0, 100);
        ofRectRounded(-halfSize, totalSize.x, totalSize.y, 5);
    }

    ofPopMatrix();
}
