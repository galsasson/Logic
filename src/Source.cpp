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
    
    initPorts();
    initPads();
}

void Source::loadResources(){
    font.loadFont("Rationale-Regular.ttf", 25);    
}

void Source::initPorts()
{
    // init output ports
    vector<GatePort*> gps;
    for (int i=0; i<portsNum; i++)
    {
        float x = (portsNum)*size.x/2 - size.x/2 - i*size.x;
        float y = GATE_SQUARE_SIZE/2 + 35;
        GatePort *gp = new GatePort(this, ofVec2f(x, y), GATEPORT_OUTPUT);
        gps.push_back(gp);
    }
    outputs.push_back(gps);
}

void Source::initPads()
{
    pads[0] = TouchPad(ofVec2f(0, size.y/2+50), 50);
}

bool Source::connectToOutputs(vector<Wire*> wires)
{
    if (wires.size() != portsNum)
        return false;

    for (int i=0; i<portsNum; i++)
    {
        outputs[outputs.size()-1][i]->connect(wires[i]);
    }
    pads[0].connected = true;

    // set up a clean output ports for next time
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

vector<Wire*> Source::getWires(GatePortType t)
{
    vector<Wire*> wires;
    
    if (t == GATEPORT_OUTPUT)
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

void Source::disconnectWires(GatePortType t, vector<Wire*> wires)
{
    if (t == GATEPORT_OUTPUT)
    {
        for (int i=0; i<outputs.size()-1; i++)
        {
            if (outputs[i][0]->wire == wires[0])
                outputs.erase(outputs.begin()+i);
        }
        
        if (outputs.size()==1)
            pads[0].connected = false;
    }
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

GatePortType Source::isTouchingPads(ofVec2f p)
{
    p-=pos;
    if (pads[0].enabled && pads[0].contains(p))
    {
        pads[0].press();
        return GATEPORT_OUTPUT;
    }
    
    return GATEPORT_UNKNOWN;
}

void Source::hideAllPads()
{
    pads[0].setVisible(false, 0);
}

void Source::releaseAllPads()
{
    pads[0].release();
}

void Source::releasePad(GatePortType t)
{
    if (t == GATEPORT_OUTPUT)
        pads[0].release();
}

void Source::holdPad(bool hold, GatePortType t)
{
    if (t == GATEPORT_OUTPUT)
        pads[0].hold(hold);
}

bool Source::isPadConnected(GatePortType t)
{
    if (t == GATEPORT_OUTPUT)
        return pads[0].connected;
    
    return false;
}


bool Source::contains(ofVec2f p)
{
    if (p.distance(pos)<50)
        return true;
    
    return false;
}

void Source::pickUp()
{
//    picked = true;
    
    pads[0].setVisible(true, 0);
}

void Source::putDown()
{
//    picked = false;
    
    pads[0].setVisible(false, 40);
}

void Source::oscilateOutputPads(bool on)
{
    pads[0].oscilate(on);
}

void Source::update()
{
    pads[0].update();
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
    /*
    ofSetColor(0, 0, 0, 100);
    ofRect(-size.x*portsNum/2+10, -size.y/2+10, size.x*portsNum, size.y);
    */
    ofSetColor(130);
    ofRect(-size.x*portsNum/2, -size.y/2, size.x*portsNum, size.y);
    ofSetColor(80);
    ofRect(-size.x*portsNum/2, size.y/2-30, size.x*portsNum, 30);
    ofNoFill();
    ofSetLineWidth(1);
    ofSetColor(130);
    ofRectRounded(-size.x*portsNum/2, -size.y/2, size.x*portsNum, size.y, 5);
    ofSetColor(200);
    ofRectRounded(-size.x*portsNum/2, -size.y/2, size.x*portsNum, size.y-30, 5);

    ofSetColor(180);
    ofFill();
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
        if (electricity[i]==HIGH)
            ofSetColor(ColorScheme::getColor(i));
        else
            ofSetColor(ColorScheme::getColor(i)*0.3);
        ofRect(x, y, size.x-8, 22);
        
        x+=size.x;
    }
    
    pads[0].draw();
    
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
