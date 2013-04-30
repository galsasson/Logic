//
//  pingpong.h
//  Logic
//
//  Created by Ryan Bartley on 4/22/13.
//
//

#pragma once

#include "ofMain.h"

class Wire;
class Gate;

class PingPong {
    
    ofFbo* ping;
    ofFbo* pong;
    
    void cleanup();
    
    bool clearedFbo;
    GLfloat width;
    GLfloat height;
    
    int time;
    
public:
    
    PingPong();
    ~PingPong();
    void setup(int width, int height);
    void renderToFbo(vector<Wire*>* w);
    //For the lights on the gates, we'll haze
    //the shit out of them
    void renderToFbo(Gate* g);
    ofFbo& getFbo();
    
};
