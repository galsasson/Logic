//
//  Electricity.h
//  Logic
//
//  Created by Ryan Bartley on 4/23/13.
//
//

#pragma once

#include "ofMain.h"



class Electricity {
    
    ofVec2f position;
    ofVec2f translate;
    float rotate;
    ofColor color;
    bool drawElec;
    
public:

    Electricity();
    ~Electricity();
    
    void setStartPosition(ofVec2f pos);
    
    void setPosition(ofVec2f pos);
    
    void setRotate(float rotate);
    void setTranslate(ofVec2f translate);
    
    float getRotate() {return rotate;};
    ofVec2f& getTranslate() {return translate;};
    
    void setDraw(bool drawElec);
    
    void draw();
};
