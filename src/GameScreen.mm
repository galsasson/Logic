//
//  GameScreen.cpp
//  Logic
//
//  Created by Surya on 24/04/13.
//
//

#include "GameScreen.h"
#include "testApp.h"

GameScreen::GameScreen(){

    
	
    level = NULL;
    
    
    ofEnableAlphaBlending();
    //ofSetFrameRate(60);
//	ofBackground(127,127,127);


}

void GameScreen::setup(int levelID)
{
    vector<EState> i1;
    vector<EState> i2;
    vector<EState> exp;

    switch (levelID)
    {
        default:
        case 0:
            i1.push_back(HIGH);
            i1.push_back(LOW);
            i2.push_back(LOW);
            i2.push_back(HIGH);
            exp.push_back(HIGH);
            exp.push_back(HIGH);
            break;
    }
    
    level = new Level(i1, i2, exp);
    level->setup();
}

void GameScreen::update(){
    if (!level)
        return;
    
    level->update();
}

void GameScreen::draw(){
    if (!level)
        return;
    
    level->draw();
}

void GameScreen::touchCancelled(ofTouchEventArgs &touch){
    
}

void GameScreen::touchDoubleTap(ofTouchEventArgs &touch){

}


void GameScreen::touchDown(ofTouchEventArgs &touch){
    level->touchDown(touch);
}

void GameScreen::touchMoved(ofTouchEventArgs &touch){
    level->touchMoved(touch);
}

void GameScreen::touchUp(ofTouchEventArgs &touch){
    level->touchUp(touch);

    
}