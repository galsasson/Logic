//
//  LevelSelector.cpp
//  Logic
//
//  Created by Surya on 24/04/13.
//
//

#include "LevelSelector.h"
#include "testApp.h"

LevelSelector::LevelSelector(){
    
    
    
}
void LevelSelector::setup(){
    background.loadImage("Screens/LevelSelector.jpg");
}

void LevelSelector::update(){
    background.reloadTexture();
    
}

void LevelSelector::draw(){
    background.draw(0,0, ofGetWidth(), ofGetHeight());
}

void LevelSelector::touchCancelled(ofTouchEventArgs &touch){
    
}

void LevelSelector::touchDoubleTap(ofTouchEventArgs &touch){
    
}


void LevelSelector::touchDown(ofTouchEventArgs &touch){
    
}

void LevelSelector::touchMoved(ofTouchEventArgs &touch){
    
}

void LevelSelector::touchUp(ofTouchEventArgs &touch)
{
    
    testApp* app = (testApp*)ofGetAppPtr();
    app->screen = &app->gameScreen;
    
    app->gameScreen.setup(0);
    
}