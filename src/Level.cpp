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

Level::Level(int num, vector<EState> input1, vector<EState> input2, vector<EState> expRes)
{
    levelNum = num;
    currentGate = NULL;
    conGate1 = NULL;
    conGate2 = NULL;
    conType1 = GATEPORT_UNKNOWN;
    conType2 = GATEPORT_UNKNOWN;
    
    portsNum = input1.size();
    
    elecPingPong = new PingPong(); 
    elecPingPong->setup(ofGetWidth(), ofGetHeight());   

    // build sources and result
    s1 = new Source(ofVec2f(ofGetWidth()/2-100, 90), input1);
    s2 = new Source(ofVec2f(ofGetWidth()/2+100, 90), input2);
    result = new Result(ofVec2f(ofGetWidth()/2, ofGetHeight()-145), expRes);

    gates.push_back(s1);
    gates.push_back(s2);
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
    
    emittingSignal = false;
    
    ostringstream convert;
    convert << levelNum;
    levelString = "Level " + convert.str();
    
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
    
    font.loadFont("Rationale-Regular.ttf", 25);
}

void Level::draw()
{
    ofBackground(0);
    
    // draw glowy frame
    ofSetColor(ColorScheme::getGateBorder());
    ofSetLineWidth(3);
    ofNoFill();
    ofRect(0, 0, ofGetWidth()-1, ofGetHeight()-1);
    
    // draw top bar
    ofFill();
    ofRect(0, 0, ofGetWidth(), 50);
    ofSetColor(255);
    ostringstream levelStr;
    levelStr << "Level " << (levelNum+1);
    font.drawString(levelStr.str(), 10, 40);
    
    
    int i;
    if (drawElectricity) {
        elecPingPong->getFbo().draw(0, 0);
    }
    
    for (i=0 ; i<gates.size(); i++)
    {
        gates[i]->draw();
    }
    
    for (i=0 ; i<wires.size(); i++)
    {
        wires[i]->draw();
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
    
    // if electricity is flowing now
    if (emittingSignal)
    {
        // if electricity did not reach yet the result gate
        if (!result->resultSet)
        {
            if (result->isDataIn())
            {
                // now the electricity got to the result gate, show the result
                result->startShowingResult(result->haveCorrectResult());
            }
        }
//        else
//        {
//            // we are showing the result already
//            if (result->showResultCounter == 0)
//            {
//                resetSignal();
//            }
//        }
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
    // electricity drawing stuff
    getAndSetWireLengthsAndSteps();
    drawElectricity = true;

    // emit signal from sources
    Source *s = (Source*)gates[0];
    s->emitSignal();
    
    s = (Source*)gates[1];
    s->emitSignal();
    
    // check if the result gate is getting a signal
    vector<EState> res = result->getResult();
    if (res[0] == FLOATING)
    {
        // the circuit is not connected all the way, result doesn't get a signal
        result->startShowingResult(false);
    }
    
    emittingSignal = true;
}

void Level::resetSignal()
{
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
    
    emittingSignal = false;
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
    
    conGate1 = NULL;
    conGate2 = NULL;
}

void Level::touchDown(ofTouchEventArgs & touch)
{
    cout << "touchDown in Level " << touch.x << " " << touch.y << endl;
    if (touch.numTouches == 1)
    {
        // if result is present, this touch will only reset the electricity
        if (emittingSignal && result->resultSet)
        {
            resetSignal();
            return;
        }
        
        // see if the user touch inventory icon
        InventoryIcon *icon = inventory->getIcon(ofVec2f(touch.x, touch.y));
        if (icon != NULL)
        {
            Gate *gate;
            
            if (icon->type == INVITEM_AND)
            {
                gate = new And(icon->getWorldPosition(), portsNum);
            }
            else if (icon->type == INVITEM_OR)
            {
                gate = new Or(icon->getWorldPosition(), portsNum);
            }
            else if (icon->type == INVITEM_NOT)
            {
                gate = new Not(icon->getWorldPosition(), portsNum);
            }
            gates.push_back(gate);
            if (gate->pickUp())
                currentGate = gate;
            else
                removeGate(gate);
            return;
        }
        
        // see if a gate or a touch pad was touched
        for (int i=0; i<gates.size(); i++)
        {
            // user is picking a gate?
            if (gates[i]->contains(ofVec2f(touch.x, touch.y)))
            {
                cout<<"click inside a gate"<<endl;
                if (gates[i]->pickUp())
                    currentGate = gates[i];
                
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
        emitSignal();
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
        conGate1->releasePad(conType1);
        conGate1->holdPad(true, conType1);
    }
    
    if (conGate2)
    {
        conGate2->releasePad(conType2);
        conGate2->holdPad(true, conType2);
    }
}
