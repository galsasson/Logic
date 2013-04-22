//
//  Level.cpp
//  Logic
//
//  Created by Gal Sasson on 4/16/13.
//
//

//#include "OpenGL/gl.h"
#include "Level.h"
#include "Source.h"
#include "Result.h"
#include "Gate.h"
#include "Wire.h"
#include "And.h"
#include "Or.h"
#include "Not.h"
#include "ColorScheme.h"

Level::Level()
{
    vector<EState> s1;
    s1.push_back(HIGH);
    s1.push_back(LOW);
    s1.push_back(HIGH);
    
    vector<EState> s2;
    s2.push_back(HIGH);
    s2.push_back(HIGH);
    s2.push_back(LOW);
    
    Source *src1 = new Source(ofVec2f(160, 40), s1);
    Source *src2 = new Source(ofVec2f(480, 40), s2);
    And *and1 = new And(ofVec2f(500, 250), 3);
    Not *not1 = new Not(ofVec2f(480, 420), 3);
    Or *or1 = new Or(ofVec2f(150, 400), 3);
    And *and2 = new And(ofVec2f(320, 550), 3);
    
    
    result = new Result(ofVec2f(320, 850), 3);

    gates.push_back(src1);
    gates.push_back(src2);
    gates.push_back(and1);
    gates.push_back(not1);
    gates.push_back(or1);
    gates.push_back(and2);
    gates.push_back(result);
    
    connect(src1, and1, GATEPORT_INPUTLEFT);
    connect(src2, and1, GATEPORT_INPUTRIGHT);
    connect(and1, not1, GATEPORT_INPUTTOP);
    connect(not1, and2, GATEPORT_INPUTRIGHT);
    connect(src1, or1, GATEPORT_INPUTLEFT);
    connect(src2, or1, GATEPORT_INPUTRIGHT);
    connect(or1, and2, GATEPORT_INPUTLEFT);
    connect(and2, result, GATEPORT_INPUTTOP);
    
    vector<EState> res = result->getResult();
    for (int i=0; i<res.size(); i++)
    {
        cout<<"result: "<<i<<" = "<<res[i]<<endl;
    }
    
    loadResources();
}

void Level::loadResources()
{
    background.loadImage("level_background.jpg");
}

void Level::draw()
{
//    ofSetColor(200);
//    background.draw(0, 0);
    ofBackground(ColorScheme::getColor(4)*0.15);
    
    for (int i=0 ; i<wires.size(); i++)
    {
        wires[i]->draw();
    }

    for (int i=0 ; i<gates.size(); i++)
    {
        gates[i]->draw();
    }

}

void Level::update()
{
    for (int i=0; i<wires.size(); i++)
    {
        wires[i]->moveElectricity();
    }
}


void Level::connect(Gate* g1, Gate* g2, GatePortType to)
{
    if (g1->portsNum != g2->portsNum)
        return;
    
    vector<Wire*> ws;
    
    for (int i=0; i<g1->portsNum; i++)
    {
        ws.push_back(new Wire());
    }
    
    g1->connectToOutputs(ws);
    g2->connectToInputs(ws, to);
    
    wires.insert(wires.end(), ws.begin(), ws.end());
}

void Level::emitSignal()
{
    Source *s = (Source*)gates[0];
    s->emitSignal();
    
    s = (Source*)gates[1];
    s->emitSignal();
    
}

void Level::touchDown(ofTouchEventArgs & touch)
{
    emitSignal();
}

void Level::touchMoved(ofTouchEventArgs & touch)
{
    
}

void Level::touchUp(ofTouchEventArgs & touch)
{
    for (int i=0; i<gates.size(); i++)
    {
        gates[i]->reset();
    }
    for (int i=0; i<wires.size(); i++)
    {
        wires[i]->reset();
    }
}
