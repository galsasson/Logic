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
#include "ColorScheme.h"

And::And(ofVec2f p, int pNum)
{
    pos = p;
    portsNum = pNum;
    
    squareSize = ofVec2f(25, 25);
    halfSquareSize = squareSize/2;
    font.loadFont("Rationale-Regular.ttf", 25);
    halfTextSize = font.getStringBoundingBox("AND", 0, 0).getBottomRight();

    me = AND;
    picked = false;
    
    initPorts();
    initPads();
}

void And::initPorts()
{
    // add input left ports
    for (int i=0; i<portsNum; i++)
    {
        float x = -(portsNum+2)*halfSquareSize.x - 10;
        float y = -(portsNum+1)*halfSquareSize.y + halfSquareSize.y + i*squareSize.y;
        GatePort *gp = new GatePort(this, ofVec2f(x, y), GATEPORT_INPUTLEFT);
        inputsLeft.push_back(gp);
    }
    
    // add input right ports
    for (int i=0; i<portsNum; i++)
    {
        float x = (portsNum+2)*halfSquareSize.x + 15;
        float y = -(portsNum+1)*halfSquareSize.y + halfSquareSize.y + i*squareSize.y;
        GatePort *gp = new GatePort(this, ofVec2f(x, y), GATEPORT_INPUTRIGHT);
        inputsRight.push_back(gp);
    }
    
    // add output ports
    vector<GatePort*> gps;
    for (int i=0; i<portsNum; i++)
    {
        float x = (portsNum)*halfSquareSize.x - halfSquareSize.x - i*squareSize.x;
        float y = (portsNum+1)*halfSquareSize.y + 15;
        GatePort *gp = new GatePort(this, ofVec2f(x, y), GATEPORT_OUTPUT);
        gps.push_back(gp);
    }
    outputs.push_back(gps);
}

void And::initPads()
{
    ofVec2f totalSize = ofVec2f((portsNum+2)*squareSize.x, (portsNum+1)*squareSize.y);
    
    pads[0] = TouchPad(ofVec2f(-totalSize.x/2-50, -halfSquareSize.y), 50);
    pads[1] = TouchPad(ofVec2f(totalSize.x/2+50, -halfSquareSize.y), 50);
    pads[2] = TouchPad(ofVec2f(0, totalSize.y/2+50), 50);
}

bool And::connectToInputs(vector<Wire*> wires, GatePortType type)
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

bool And::connectToOutputs(vector<Wire*> wires)
{
    if (wires.size() != portsNum)
        return false;
    
    for (int i=0; i<portsNum; i++)
    {
        outputs[outputs.size()-1][i]->connect(wires[i]);
    }
    pads[2].connected = true;
    
    // add new clean output ports
    vector<GatePort*> gps;
    for (int i=0; i<portsNum; i++)
    {
        float x = (portsNum)*halfSquareSize.x - halfSquareSize.x - i*squareSize.x;
        float y = (portsNum+1)*halfSquareSize.y + 15;
        GatePort *gp = new GatePort(this, ofVec2f(x, y), GATEPORT_OUTPUT);
        gps.push_back(gp);
    }
    outputs.push_back(gps);
    
    return true;
}

vector<Wire*> And::getWires(GatePortType t)
{
    vector<Wire*> wires;
    
    if (t == GATEPORT_INPUTLEFT)
    {
        for (int i=0; i<portsNum; i++)
        {
            wires.push_back(inputsLeft[i]->wire);
        }
    }
    else if (t == GATEPORT_INPUTRIGHT)
    {
        for (int i=0; i<portsNum; i++)
        {
            wires.push_back(inputsRight[i]->wire);
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

void And::disconnectWires(GatePortType t, vector<Wire*> wires)
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

void And::setPosition(ofVec2f p)
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
        if (gp == inputsLeft[i] && inputsRight[i]->getState() != FLOATING)
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
        else if (gp == inputsRight[i] && inputsLeft[i]->getState() != FLOATING)
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

GatePortType And::isTouchingPads(ofVec2f p)
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

void And::hideAllPads()
{
    for (int i=0; i<3; i++)
        pads[i].setVisible(false, 0);
}

void And::releaseAllPads()
{
    for (int i=0; i<3; i++)
    {
        pads[i].release();
    }
}

void And::releasePad(GatePortType t)
{
    if (t == GATEPORT_INPUTLEFT)
        pads[0].release();
    else if (t == GATEPORT_INPUTRIGHT)
        pads[1].release();
    else if (t == GATEPORT_OUTPUT)
        pads[2].release();
}

void And::holdPad(bool hold, GatePortType t)
{
    if (t == GATEPORT_INPUTLEFT)
        pads[0].hold(hold);
    else if (t == GATEPORT_INPUTRIGHT)
        pads[1].hold(hold);
    else if (t == GATEPORT_OUTPUT)
        pads[2].hold(hold);
}

bool And::isPadConnected(GatePortType t)
{
    if (t == GATEPORT_INPUTLEFT)
        return pads[0].connected;
    else if (t == GATEPORT_INPUTRIGHT)
        return pads[1].connected;
    else if (t == GATEPORT_OUTPUT)
        return pads[2].connected;
    
    return false;
}

bool And::contains(ofVec2f p)
{
    if (p.distance(pos)<60)
        return true;
    
    return false;
}

void And::pickUp()
{
    picked = true;
    
    for (int i=0; i<3; i++)
    {
        pads[i].setVisible(true, 0);
    }
}

void And::putDown()
{
    picked = false;
    
    for (int i=0; i<3; i++)
    {
        pads[i].setVisible(false, 40);
    }
}

void And::oscilateInputPads(bool on)
{
    if (!pads[0].connected)
        pads[0].oscilate(on);
    
    if (!pads[1].connected)
        pads[1].oscilate(on);
}

void And::oscilateOutputPads(bool on)
{
    pads[2].oscilate(on);
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

void And::update()
{
    for (int i=0; i<3; i++)
    {
        pads[i].update();
    }
}

void And::draw()
{
    ofPushMatrix();
    ofTranslate(pos);
    if (picked)
        ofScale(1.4f, 1.4f);
    
    ofVec2f totalSize = ofVec2f((portsNum+2)*squareSize.x, (portsNum+1)*squareSize.y);
    ofVec2f halfSize = totalSize/2;
    ofSetColor(0, 0, 0, 100);
    ofFill();
    ofRect(-halfSize+10, totalSize.x, totalSize.y);
    ofSetColor(130);
    ofRect(-halfSize, totalSize.x, totalSize.y-squareSize.y);
    ofSetColor(80);
    ofRect(-halfSize.x, -halfSquareSize.y + portsNum*halfSquareSize.y, totalSize.x, squareSize.y);
    ofNoFill();
    ofSetLineWidth(1);
    ofSetColor(130);
    ofRectRounded(-halfSize, totalSize.x, totalSize.y, 5);
    ofSetColor(200);
    ofRectRounded(-halfSize, totalSize.x, totalSize.y-squareSize.y, 5);

    
    /* draw colored squares inside the gate that respresent the ports status */
    ofFill();
    // draw left input
    float x = -(portsNum+2)*halfSquareSize.x + 4;
    float y = -(portsNum+1)*halfSquareSize.y + 4;
    for (int i=0; i<inputsLeft.size(); i++)
    {
        if (inputsLeft[i]->getState() == HIGH)
            ofSetColor(ColorScheme::getColor(i));
        else
            ofSetColor(ColorScheme::getColor(i)*0.3);
        ofRect(x, y, squareSize.x-8, squareSize.y-8);
        y += squareSize.y;
    }
    
    // draw right input
    x = -(portsNum+2)*halfSquareSize.x + 4;
    y = -(portsNum+1)*halfSquareSize.y + 4;
    for (int i=0; i<inputsRight.size(); i++)
    {
        if (inputsRight[i]->getState() == HIGH)
            ofSetColor(ColorScheme::getColor(i));
        else
            ofSetColor(ColorScheme::getColor(i)*0.3);
        ofRect(-x, y, -(squareSize.x-8), squareSize.y-8);
        y += squareSize.y;
    }
    
    // draw outputs
    if (outputs.size()>0)
    {
        for (int i=0; i<outputs[0].size(); i++)
        {
        if (outputs[0][i]->getState() == HIGH)
            ofSetColor(ColorScheme::getColor(i));
        else
            ofSetColor(ColorScheme::getColor(i)*0.3);
        ofRect(portsNum*halfSquareSize.x - (i+1)*squareSize.x+4, portsNum*halfSquareSize.y-8, squareSize.x-8, squareSize.y-8);
        }

    }
    
    /* draw the ports of the gate */
    for (int i=0; i<inputsLeft.size(); i++)
    {
        inputsLeft[i]->draw();
    }
    
    for (int i=0; i<inputsRight.size(); i++)
    {
        inputsRight[i]->draw();
    }
    
    for (int i=0; i<outputs.size(); i++)
    {
        for (int j=0; j<portsNum; j++)
        {
            outputs[i][j]->draw();
        }
    }
    
    // write text on the gate
    ofSetColor(180);
    font.drawString("AND", -halfTextSize.x/2, 0);

    // draw the touch pads
    for (int i=0; i<3; i++)
    {
        pads[i].draw();
    }
    
    ofPopMatrix();
}
