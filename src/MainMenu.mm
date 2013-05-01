//
//  MainMenu.cpp
//  Logic
//
//  Created by Surya on 24/04/13.
//
//

#include "MainMenu.h"
#include "testApp.h"


MainMenu::MainMenu(){
    
}

MainMenu::~MainMenu()
{
    for (vector<Word*>::iterator it = words.begin(); it != words.end(); it++) {
        delete *it;
    }
}

void MainMenu::setup(){
    
    //initiating the main menu words
    
    //Word(position of the word, fontname, word to be shown, depth of the mesh, font size, whether it's a button
    
    words.push_back(new Word(ofPoint(ofGetWidth()/2, ofGetHeight()/2-150, -250), "sdf.ttf", "Logic", 50, 120, false));
    words.push_back(new Word(ofPoint(ofGetWidth()/2, ofGetHeight()/2+100, -250), "sdf.ttf", "Play", 50, 30, true));
    words.push_back(new Word(ofPoint(ofGetWidth()/2, ofGetHeight()/2+150, -250), "sdf.ttf", "Help", 50, 30, true));
    words.push_back(new Word(ofPoint(ofGetWidth()/2, ofGetHeight()/2+200, -250), "sdf.ttf", "Settings", 50, 30, true));
    
    for (vector<Word*>::iterator it = words.begin(); it != words.end(); it++) {
        (*it)->setup();
    }
    



}

void MainMenu::update(){
    
    
}

void MainMenu::draw(){

    ofSetColor(255, 0, 0);
    ofNoFill();
    for (vector<Word*>::iterator it = words.begin(); it != words.end(); it++) {
        (*it)->draw();
    }
    
}

void MainMenu::touchCancelled(ofTouchEventArgs &touch){
    
}

void MainMenu::touchDoubleTap(ofTouchEventArgs &touch){
    
}


void MainMenu::touchDown(ofTouchEventArgs &touch){

    
    
}

void MainMenu::touchMoved(ofTouchEventArgs &touch){
    
}

void MainMenu::touchUp(ofTouchEventArgs &touch){
    cout<<touch.x<<" "<<touch.y<<endl;
    
    
    int i = 0;
    for (vector<Word*>::iterator it = words.begin(); it != words.end(); it++) {
        if ((*it)->getIsButton()) {
            if((*it)->getButton()->contains(ofVec2f(touch.x, touch.y))){
                testApp* app = (testApp*)ofGetAppPtr();
                
                switch (i) {
                        
                    case 0:
                        //TODO: FIGURE OUT WHERE WE DELETE THE SCREENS THAT CALL OTHER DESTRUCTORS
                        app->screen = &app->levelSelector;
                        app->screen->setup();
//                        delete this;
                        break;
                        
                    case 1:
                        
                        app->screen = &app->mainMenu;
                        app->screen->setup();
                        break;
                        
                    case 2:
                        
                        app->screen = &app->gameScreen;
                        app->screen->setup();
                        break;
                    default:
                        break;
                }
            }
            i++;
        }
        
    }
    
    
    
}
