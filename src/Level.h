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
#include "Result.h"

class Level
{
    vector<Gate*> gates;
    vector<Wire*> wires;
    
    Result* result;
    
    ofImage background;
    
public:
    Level();
    void loadResources();
    
    void emitSignal();
    
    void update();
    void draw();
    
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    
private:
    void connect(Gate* g1, Gate* g2, GatePortType to);
};

#endif /* defined(__Logic__Level__) */
