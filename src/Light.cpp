//
//  Light.cpp
//  Logic
//
//  Created by Ryan Bartley on 4/24/13.
//
//

#include "Light.h"
#include "ColorScheme.h"

Light::Light()
{
    
}

Light::~Light()
{
    
}

void Light::setStartPosition(ofVec2f pos)
{
    this->position = pos;
}

void Light::setPosition(ofVec2f pos)
{
    position = pos;
}

void Light::setRotate(float rotate)
{
    this->rotate = rotate;
}

void Light::setTranslate(ofVec2f translate)
{
    this->translate = translate;
}

void Light::setDraw(bool drawElec)
{
    this->drawElec = drawElec;
}

void Light::draw()
{
    if (drawElec) {
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