//
//  Screen.cpp
//  Logic
//
//  Created by Surya on 24/04/13.
//
//

#include "Screen.h"

Screen::Screen(){
    isSetup = false;
    words.clear();
    touchedButton = false;
    cout << "super constructor called" << endl;
}

void Screen::setup(){
    
}

void Screen::update(){
    
}

void Screen::draw(){
    
}

void Screen::touchDown(ofTouchEventArgs &touch){
    
}

void Screen::touchMoved(ofTouchEventArgs &touch){
    
}

void Screen::touchUp(ofTouchEventArgs &touch){
    
}

void Screen::touchDoubleTap(ofTouchEventArgs &touch){

}

void Screen::touchCancelled(ofTouchEventArgs &touch){
    
}

bool Screen::getIsSetup()
{
    return isSetup;
}

void Screen::lightSetup()
{
    glEnable(GL_DEPTH_TEST);
    
    // turn on smooth lighting //
    ofSetSmoothLighting(true);
    
	center.set(ofGetWidth()*.5, -100, 100);
    
    // Point lights emit light in all directions //
    // set the diffuse color, color reflected from the light source //
    light.setDiffuseColor( ofColor(0.f, 100.0f, 189.0f));
    
    // specular color, the highlight/shininess color //
	light.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    light.setPosition(center.x, center.y, center.z);
    
    colorHue = ofRandom(0, 250);
    
    lightColor.setBrightness( 210.f );
    lightColor.setSaturation( 150.f );
    
}

void Screen::lightUpdate()
{
    colorHue += .5f;
    if(colorHue >= 255) colorHue = 0.f;
    lightColor.setHue(200);
    if (center.y < ofGetHeight()/2+200) {
        center.y += 5;
    }
    
    light.setPosition(center.x, center.y, center.z);
    light.setDiffuseColor(lightColor);
    
    
}

void Screen::lightDraw()
{
    // enable lighting
    ofEnableLighting();
    
    // the position of the light must be updated every frame,
    // call enable() so that it can update itself //
    light.enable();
    
    ofFill();
    
    ofPushMatrix();
    
        ofPushMatrix();
            ofSetColor(light.getAmbientColor());
    
            //TODO: background for ambient lighting
            ofRect(0-200, 0-200, -200, ofGetWidth()+300, ofGetHeight()+400);
        ofPopMatrix();
    
        ofSetColor(light.getDiffuseColor());
    
        //DRAW THE ELEMENTS INSIDE THE LIGHT
        drawElements();
    
    ofPopMatrix();
	
    // turn off lighting //
    ofDisableLighting();
}



void Screen::drawElements()
{
    
}
