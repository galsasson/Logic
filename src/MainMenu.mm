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

void MainMenu::setup(){
    background.loadImage("Screens/MainMenu.jpg");
    buttons.clear();
    //level selector
    buttons.push_back(Button(ofVec2f(260, 530), 100, 50));
    //mainMenu (temp)
    buttons.push_back(Button(ofVec2f(260, 600), 100, 50));
    //gameScreen
    buttons.push_back(Button(ofVec2f(240, 680), 150, 50));




}

void MainMenu::update(){
    
    
}

void MainMenu::draw(){
    background.draw(0,0, ofGetWidth(), ofGetHeight());
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofRect(260, 530, 100, 50);
    ofRect(260, 600, 100, 50);
    ofRect(240, 680, 150, 50);
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

        for (int i =0; i<buttons.size(); i++) {
            if(buttons[i].contains(ofVec2f(touch.x, touch.y))){
                testApp* app = (testApp*)ofGetAppPtr();
                cout<<i<<endl;
                switch (i) {
                        
                    case 0:
                        
                        app->screen = &app->levelSelector;
                        app->screen->setup();
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
            
        }


    
}