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

Level::Level()
{
    vector<EState> s1;
    s1.push_back(HIGH);
    s1.push_back(LOW);
    s1.push_back(HIGH);
    
    vector<EState> s2;
    s2.push_back(HIGH);
    s2.push_back(LOW);
    s2.push_back(LOW);
    
    result = new Result(ofVec2f(320, 850), 3);

    gates.push_back(new Source(ofVec2f(160, 50), s1));
    gates.push_back(new Source(ofVec2f(480, 50), s2));
    gates.push_back(new And(ofVec2f(320, 500), 3));
    gates.push_back(result);
    
    // connect source 1 with gate
    connect(gates[0], gates[2], GATEPORT_INPUTLEFT);
    
    // connect source 2 with gate
    connect(gates[1], gates[2], GATEPORT_INPUTRIGHT);
    
    // connect gate with result
    connect(gates[2], result, GATEPORT_INPUTTOP);
    
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
    background.draw(0, 0);
    
    for (int i=0 ; i<gates.size(); i++)
    {
        gates[i]->draw();
    }
    
    for (int i=0 ; i<wires.size(); i++)
    {
        wires[i]->draw();
    }

}

void Level::update()
{
    for (int i=0 ; i<gates.size(); i++)
    {
        gates[i]->update();
    }
    
//    result->suck();
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
