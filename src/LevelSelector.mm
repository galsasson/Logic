//
//  LevelSelector.cpp
//  Logic
//
//  Created by Surya on 24/04/13.
//
//

#include "LevelSelector.h"
#include "testApp.h"

LevelSelector::LevelSelector()
{

}

void LevelSelector::setup()
{
    
    //initiating the LEVEL SELECTOR words
    
    //Word(position of the word, fontname, word to be shown, depth of the mesh, font size, whether it's a button)
    
    words.push_back(new Word(ofPoint(ofGetWidth()/2, ofGetHeight()/2-150, 0), "sdf.ttf", "Level", 50, 90, false));
    words.push_back(new Word(ofPoint(ofGetWidth()/2-100, ofGetHeight()/2, 0), "sdf.ttf", "1", 10, 50, true));
    words.push_back(new Word(ofPoint(ofGetWidth()/2-0, ofGetHeight()/2, 0), "sdf.ttf", "2", 10, 50, true));
    words.push_back(new Word(ofPoint(ofGetWidth()/2+100, ofGetHeight()/2, 0), "sdf.ttf", "3", 10, 50, true));
    words.push_back(new Word(ofPoint(ofGetWidth()/2-100, ofGetHeight()/2+75, 0), "sdf.ttf", "4", 10, 50, true));
    words.push_back(new Word(ofPoint(ofGetWidth()/2-0, ofGetHeight()/2+75, 0), "sdf.ttf", "5", 10, 50, true));
    words.push_back(new Word(ofPoint(ofGetWidth()/2+100, ofGetHeight()/2+75, 0), "sdf.ttf", "6", 10, 50, true));
    words.push_back(new Word(ofPoint(ofGetWidth()/2-100, ofGetHeight()/2+150, 0), "sdf.ttf", "7", 10, 50, true));
    words.push_back(new Word(ofPoint(ofGetWidth()/2+0, ofGetHeight()/2+150, 0), "sdf.ttf", "8", 10, 50, true));
    words.push_back(new Word(ofPoint(ofGetWidth()/2+100, ofGetHeight()/2+150, 0), "sdf.ttf", "9", 10, 50, true));
    words.push_back(new Word(ofPoint(ofGetWidth()/2+0, ofGetHeight()/2+225, 0), "sdf.ttf", "10", 10, 50, true));
    words.push_back(new Word(ofPoint(ofGetWidth()/2+0, ofGetHeight()/2+300, 0), "sdf.ttf", "Back", 10, 30, true));

    for (vector<Word*>::iterator it = words.begin(); it != words.end(); it++) {
        (*it)->setup();
    }
    
    lightSetup();
    
}

void LevelSelector::buttonAnimandNavi()
{
    if (touchedButton) {
        for (vector<Word*>::iterator it = words.begin(); it != words.end(); it++) {
            if ((*it)->getIsButton()) {
                if ((*it)->getButton()->pressed) {
                    (*it)->animate();
                }
                if ((*it)->getButton()->getNavigate()) {
                    testApp* app = (testApp*)ofGetAppPtr();
                    app->selectScreen((*it)->getWord(), this);
                }
            }
        }
    }
}

void LevelSelector::update()
{
    lightUpdate();
    buttonAnimandNavi();
    
}

void LevelSelector::drawElements()
{
    for (vector<Word*>::iterator it = words.begin(); it != words.end(); it++) {
        (*it)->draw();
    }
}

void LevelSelector::draw()
{
    lightDraw();
}

void LevelSelector::touchCancelled(ofTouchEventArgs &touch)
{
    
}

void LevelSelector::touchDoubleTap(ofTouchEventArgs &touch)
{
    
}

void LevelSelector::touchDown(ofTouchEventArgs &touch)
{
    
}

void LevelSelector::touchMoved(ofTouchEventArgs &touch)
{
    
}

void LevelSelector::touchUp(ofTouchEventArgs &touch)
{
    
    if (!touchedButton) {
        for (vector<Word*>::iterator it = words.begin(); it != words.end(); it++) {
            if ((*it)->getIsButton()) {
                if((*it)->getButton()->contains(ofVec2f(touch.x, touch.y))){
                    (*it)->getButton()->pressed = true;
                    touchedButton = true;
                }
            }
        }
    }
    
}
