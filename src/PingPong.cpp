//
//  pingpong.cpp
//  Logic
//
//  Created by Ryan Bartley on 4/22/13.
//
//

#include "PingPong.h"
#include "Wire.h"
#include "ColorScheme.h"
#include "Electricity.h"

PingPong::PingPong()
{
    ping = NULL;
    pong = NULL;
    
    time = 0;
}

PingPong::~PingPong()
{
    cleanup();
}

void PingPong::setup(int width, int height)
{
    cleanup();
    ping = new ofFbo();
    pong = new ofFbo();
    ping->allocate(width, height);
    pong->allocate(width, height);
    
    this->width = width;
    this->height = height;
    
    clearFBO();
}

void PingPong::clearFBO()
{
    pong->begin();
    ofClear(0, 0, 0, 0);
    pong->end();
    
    ping->begin();
    ofClear(0, 0, 0, 0);
    ping->end();
}

void PingPong::cleanup()
{
    if (ping != NULL) {
        delete ping;
        ping = NULL;
    }
    if (pong != NULL) {
        delete pong;
        pong = NULL;
    }
}

ofFbo& PingPong::getFbo()
{
    return *pong;
}

//write for the wire class
void PingPong::renderToFbo(vector<Wire*>* w)
{
    ofPushStyle();
    ping->begin();
    {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofClear(0, 0, 0, 0);
        glColor4f(255, 255, 255, 255);
        
        glPushMatrix();
        glTranslatef(width/2, height/2, 0);
        
        ofSetColor(ColorScheme::getWireOn());
        glScalef(1.0007, 1.0002, 1);
        pong->setAnchorPercent(0.5f, 0.5f);
        
        pong->draw(0, 0);
        glPopMatrix();
        
        ofSetColor(ColorScheme::getWireOn());
        for (vector<Wire*>::iterator it = (*w).begin(); it != (*w).end(); it++){
//            (*it)->draw();
            (*it)->getElectricity()->draw();
        }
    }
    ping->end();
    ofPopStyle();
    pong->setAnchorPercent(0.0f, 0.0f);
    
    ofFbo* temp = ping;
    ping = pong;
    pong = temp;
}

//write for the gate lights.
void PingPong::renderToFbo(Gate* g)
{
    ping->begin();
    {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofClear(0, 0, 0, 0);
        glColor4f(255, 255, 255, 255);
        
        glPushMatrix();
        glTranslatef(width/2, height/2, 0);
        
        ofSetColor(ColorScheme::getWireOn());
        glScalef(1.0005, 1.00009, abs(sin(time)));
        pong->setAnchorPercent(.5f, .5f);
        
        pong->draw(0, 0);
        glPopMatrix();
        
        ofSetColor(ColorScheme::getWireOn());
        
        
    }
}
