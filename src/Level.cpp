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
#include "InventoryIcon.h"
#include "Button.h"

Level::Level(vector<EState> input1, vector<EState> input2, vector<EState> expRes)
{
    currentGate = NULL;
    conGate1 = NULL;
    conGate2 = NULL;
    conType1 = GATEPORT_UNKNOWN;
    conType2 = GATEPORT_UNKNOWN;
    
    portsNum = input1.size();
    
    elecPingPong = new PingPong(); 
    elecPingPong->setup(ofGetWidth(), ofGetHeight());   

    // build sources and result
    Source *src1 = new Source(ofVec2f(ofGetWidth()/2-100, 40), input1);
    Source *src2 = new Source(ofVec2f(ofGetWidth()/2+100, 40), input2);
    result = new Result(ofVec2f(ofGetWidth()/2, ofGetHeight()-150), expRes);

    gates.push_back(src1);
    gates.push_back(src2);
    gates.push_back(result);
    
    // build inventory
    inventory = new Inventory(ofVec2f(0, ofGetHeight()-100));
    inventory->addIcon(new InventoryIcon(INVITEM_AND));
    inventory->addIcon(new InventoryIcon(INVITEM_OR));
    inventory->addIcon(new InventoryIcon(INVITEM_NOT));
    
    goButton = new Button();
    goButton->setup(ofRectangle(0, 0, 100, 100), ofVec2f(ofGetWidth()-100, ofGetHeight()-100));
    
    //flag for FBO's and electricity
    drawElectricity = false;
    
    vector<EState> res = result->getResult();
    for (int i=0; i<res.size(); i++)
    {
        cout<<"result: "<<i<<" = "<<res[i]<<endl;
    }
    
//    loadResources();
}

void Level::getAndSetWireLengthsAndSteps()
{
    vector<Wire*>::iterator it = wires.begin();
    float totalLength = 0.0;
    for (; it != wires.end(); it++) {
        totalLength += (*it)->getPathLength();
    }
    
    //THIS IS TO DRAW THEM ALL AT THE SAME SPEED
    for (it = wires.begin(); it != wires.end(); it++) {
        float temp = (*it)->getPathLength()/totalLength;
        (*it)->setStep(temp);
    }
    
    //THIS IS TO DRAW THEM ALL AT THE FASTEST SPEED
//    float highest = 0.0f;
//    for (it = wires.begin(); it != wires.end(); it++) {
//        float temp = (*it)->getPathLength()/totalLength;
//        if (temp > highest) {
//            highest = temp;
//        }
//    }
//    
//    
//    for (it = wires.begin(); it != wires.end(); it++) {
//        (*it)->setStep(highest);
//    }
}

void Level::setup()
{

    cout<<"Game Level: "<< background.loadImage("level_background.jpg");

    for (int i=0; i<gates.size(); i++) {
      gates[i]->loadResources();
    }
    for (int i=0; i<inventory->icons.size(); i++) {
        inventory->icons[i]->loadResources();
    }
}

void Level::draw()
{
//    ofSetColor(200);
//    background.draw(0, 0);
    ofBackground(ColorScheme::getColor(4)*0.15);
    
    int i;
    for (i=0 ; i<wires.size(); i++)
    {
        
        wires[i]->draw();
    }

    for (i=0 ; i<gates.size(); i++)
    {
        gates[i]->draw();
    }
    
    if (drawElectricity) {
        glPushMatrix();
            ofSetColor(255);
            elecPingPong->getFbo().draw(0, 0);
        glPopMatrix();
    }
    
    inventory->draw();
    goButton->draw();
    
    if (currentGate)
        currentGate->draw();
}

void Level::update()
{
    for (int i=0; i<wires.size(); i++)
    {
        wires[i]->moveElectricity();
    }
    for (int i=0; i<gates.size(); i++)
    {
        gates[i]->update();
    }
    
    if (currentGate != NULL)
        currentGate->update();

    //this decides whether to draw stuff
    if (drawElectricity) {
        elecPingPong->renderToFbo(&wires);
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

void Level::disconnectWires(vector<Wire *> toRemove)
{
    // disconnect the wires from the components
    for (int r=0; r<toRemove.size(); r++)
    {
        GatePort *inGP = toRemove[r]->input;
        GatePort *outGP = toRemove[r]->output;
        (inGP->getParentGate())->disconnectWires(inGP->type, toRemove);
        (outGP->getParentGate())->disconnectWires(outGP->type, toRemove);
        
        for (int i=0; i<wires.size(); i++)
        {
            if (toRemove[r] == wires[i])
                wires.erase(wires.begin()+i);
        }
    }
    
    // delete the wires themselves
    for (vector<Wire*>::iterator it = toRemove.begin(); it != toRemove.end(); it++){
        delete *it;
    }
}

void Level::removeGate(Gate *gate)
{
    // first, lets delete the wires connected to that gate
    disconnectWires(gate->getWires(GATEPORT_INPUTLEFT));
    disconnectWires(gate->getWires(GATEPORT_INPUTTOP));
    disconnectWires(gate->getWires(GATEPORT_INPUTRIGHT));
    disconnectWires(gate->getWires(GATEPORT_OUTPUT));
    
    // remove this gate from the gates list
    for (int i=0; i<gates.size(); i++)
    {
        if (gates[i] == gate)
            gates.erase(gates.begin()+i);
    }
    
    // delete the gate
    delete gate;
}

void Level::emitSignal()
{
    Source *s = (Source*)gates[0];
    s->emitSignal();
    
    s = (Source*)gates[1];
    s->emitSignal();
    
}

void Level::releaseHoldPads()
{
    if (conGate1)
    {
        conGate1->releasePad(conType1);
        conGate1->holdPad(false, conType1);
        conGate1=NULL;
        for (int i=0; i<gates.size(); i++)
        {
            gates[i]->oscilateInputPads(false);
        }
    }
    if (conGate2)
    {
        conGate2->releasePad(conType2);
        conGate2->holdPad(false, conType2);
        conGate2=NULL;
        for (int i=0; i<gates.size(); i++)
        {
            gates[i]->oscilateOutputPads(false);
        }
    }
}

void Level::touchDown(ofTouchEventArgs & touch)
{
    cout << "touchDown in Level " << touch.x << " " << touch.y << endl;
    if (touch.numTouches == 1)
    {
        // see if the user touch inventory icon
        InventoryIcon *icon = inventory->getIcon(ofVec2f(touch.x, touch.y));
        if (icon != NULL)
        {
            if (icon->type == INVITEM_AND)
            {
                currentGate = new And(icon->getWorldPosition(), portsNum);
            }
            else if (icon->type == INVITEM_OR)
            {
                currentGate = new Or(icon->getWorldPosition(), portsNum);
            }
            else if (icon->type == INVITEM_NOT)
            {
                currentGate = new Not(icon->getWorldPosition(), portsNum);
            }
            gates.push_back(currentGate);
            currentGate->pickUp();
            return;
        }
        
        // see if a gate or a touch pad was touched
        for (int i=0; i<gates.size(); i++)
        {
            // user is picking a gate?
            if (gates[i]->contains(ofVec2f(touch.x, touch.y)))
            {
                cout<<"click inside a gate"<<endl;
                currentGate = gates[i];
                currentGate->pickUp();
                
                releaseHoldPads();
                
                // release all visible pads
                for (int j=0; j<gates.size(); j++)
                {
                    if (j!=i)
                        gates[j]->hideAllPads();
                }
                return;
            }
            
            GatePortType t = gates[i]->isTouchingPads(ofVec2f(touch.x, touch.y));
            if (t == GATEPORT_UNKNOWN)
                continue;

            if (t == GATEPORT_OUTPUT)
            {
                if (conGate1 == gates[i] && conGate1->isPadConnected(t))
                {
                    // this pad was clicked two times, remove wires
                    disconnectWires(conGate1->getWires(GATEPORT_OUTPUT));
                    releaseHoldPads();
                    conGate1 = NULL;
                    return;
                }
                
                conGate1 = gates[i];
                conType1 = t;
                if (conGate2 != NULL)
                {
                    // make a connect between conGate1 and conGate2
                    cout<<"make connection"<<endl;
                    connect(conGate1, conGate2, conType2);
                    releaseHoldPads();
                }
                else if (conType1 == GATEPORT_OUTPUT || !conGate1->isPadConnected(conType1))
                {
                    for (int j=0; j<gates.size(); j++)
                    {
                        if (gates[j] != gates[i])
                            gates[j]->oscilateInputPads(true);
                    }
                }
                return;
            }
            else
            {
                if (conGate2 == gates[i] && conGate2->isPadConnected(t))
                {
                    // this pad was clicked two times, remove wires
                    disconnectWires(conGate2->getWires(t));
                    releaseHoldPads();
                    conGate2 = NULL;
                    return;
                }

                cout<<"touched input touch pad"<<endl;;
                conGate2 = gates[i];
                conType2 = t;
                if (conGate1 != NULL)
                {
                    // make a connect between conGate1 and conGate2
                    cout<<"make connection"<<endl;
                    connect(conGate1, conGate2, conType2);
                    releaseHoldPads();
                }
                else if (conType2 == GATEPORT_OUTPUT || !conGate2->isPadConnected(conType2))
                {
                    for (int j=0; j<gates.size(); j++)
                    {
                        if (gates[j] != gates[i])
                            gates[j]->oscilateOutputPads(true);
                    }
                }
                return;
            }
        }
        
        releaseHoldPads();
    }

    if (goButton->contains(ofVec2f(touch.x, touch.y)))
    {
        getAndSetWireLengthsAndSteps();
        emitSignal();
        drawElectricity = true;
    }
}

void Level::touchMoved(ofTouchEventArgs & touch)
{   cout << "touchMoved in Level " << touch.x << " " << touch.y << endl;
    if (currentGate)
    {
        currentGate->setPosition(ofVec2f(touch.x, touch.y));
        
        if (inventory->contains(ofVec2f(touch.x, touch.y)))
        {
            currentGate->aboutToDelete = true;
        }
        else
            currentGate->aboutToDelete = false;
    }
}

void Level::touchUp(ofTouchEventArgs & touch)
{
    cout << "touchUp in Level " << touch.x << " " << touch.y << endl;
    if (currentGate)
    {
        if (inventory->contains(ofVec2f(touch.x, touch.y)))
        {
            // delete this gate, its on the inventory
            removeGate(currentGate);
            currentGate = NULL;
        }
        else {
            // just put down the gate
            currentGate->putDown();
            currentGate = NULL;
        }
    }
    
    if (conGate1)
    {
        if (conGate1->isPadConnected(conType1))
        {
            
        }
        conGate1->releasePad(conType1);
        conGate1->holdPad(true, conType1);
    }
    
    if (conGate2)
    {
        conGate2->releasePad(conType2);
        conGate2->holdPad(true, conType2);
    }
    
    
    
    for (int i=0; i<gates.size(); i++)
    {
        gates[i]->reset();
    }
    for (int i=0; i<wires.size(); i++)
    {
        wires[i]->reset();
    }
    
    if (drawElectricity) {
        drawElectricity = false;
        elecPingPong->clearFBO();
    }
}
