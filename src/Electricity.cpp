//
//  Electricity.cpp
//  Logic
//
//  Created by Ryan Bartley on 4/23/13.
//
//

#include "Electricity.h"
#include "ColorScheme.h"


Electricity::Electricity()
{
    position = ofVec2f(0,0);
    
    drawElec = false;
}

Electricity::~Electricity()
{

}

void Electricity::setStartPosition(ofVec2f pos)
{
    translate = pos;
}

void Electricity::setRotate(float rotate)
{
    this->rotate = rotate;
}

void Electricity::setTranslate(ofVec2f translate)
{
    this->translate = translate;
}

void Electricity::setDraw(bool drawElec)
{
//    cout << "drawElec is " << (drawElec ? "true" : "false") << endl;
    this->drawElec = drawElec;
}

void Electricity::setPosition(ofVec2f pos)
{
    position = pos;
}

void Electricity::draw()
{
    if (drawElec){
        ofPushMatrix();
        ofEnableAlphaBlending();
        ofTranslate(translate);
        ofRotate(rotate);
        
        ofSetLineWidth(5);
        ofFill();
        ofSetColor(ofColor(255, 255, 0));
        ofCircle(position.x, position.y, 10);
        ofSetColor(ofColor(255, 0, 0));
        ofCircle(position.x-5, position.y, 5);
        
        ofPopMatrix();
    }
}