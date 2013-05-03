//
//  Letter.h
//  Logic
//
//  Created by Ryan Bartley on 4/29/13.
//
//

#pragma once
#include "ofMain.h"

class Letter {
    
    
public:
    
    ofMesh front;
    ofMesh back;
    ofMesh side;
    
    float transformHeight;
    bool makeDepth;
    
    void setup(ofPath letter, float depth, float height);
    void draw();
    
    
};
