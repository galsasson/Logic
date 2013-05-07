//
//  Level.h
//  Logic
//
//  Created by Gal Sasson on 4/16/13.
//
//

#ifndef __Logic__Level__
#define __Logic__Level__

#include <iostream>
#include "ofMain.h"
#include "Gate.h"
#include "Wire.h"
#include "Source.h"
#include "Result.h"
#include "Inventory.h"
#include "PingPong.h"
#include "Electricity.h"
#include "Button.h"

class Level
{
    vector<Wire*> wires;
    vector<Electricity*> electricity;
    
    Source* s1;
    Source* s2;
    Result* result;
    
    ofImage background;
    
    Gate *currentGate;
    
    Gate *conGate1;
    GatePortType conType1;
    Gate *conGate2;
    GatePortType conType2;
    
    Button *goButton;
    
    int portsNum;

    PingPong* elecPingPong;
    
    bool drawElectricity;
    
    bool emittingSignal;
    
public:
    
    Level(vector<EState> input1, vector<EState> input2, vector<EState> expRes);
    void setup();
    
    void emitSignal();
    void resetSignal();
    
    void update();
    void draw();
    
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    
    vector<Gate*> gates;
    Inventory *inventory;
    void getAndSetWireLengthsAndSteps();
    
private:
    void connect(Gate* g1, Gate* g2, GatePortType to);
    void disconnectWires(vector<Wire*> toRemove);
    void removeGate(Gate *gate);
    
    void releaseHoldPads();
};

#endif /* defined(__Logic__Level__) */
