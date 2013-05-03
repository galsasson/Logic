#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"

#include "Level.h"
#include "Screen.h"
#include "LevelSelector.h"
#include "GameScreen.h"
#include "MainMenu.h"

class testApp : public ofxiPhoneApp{
    
    public:


        void setup();
        void update();
        void draw();
        void exit();
	
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);

        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);
    
    void selectScreen(string word, MainMenu* menu);
    void selectScreen(string word, LevelSelector* menu);

    Screen* screen;
};


