//
//  MainMenu.h
//  Logic
//
//  Created by Surya on 24/04/13.
//
//

#ifndef __Logic__MainMenu__
#define __Logic__MainMenu__

#include <iostream>
#include "Screen.h"
#include "Button.h"
#include "ofMain.h"
#include "Word.h"

class MainMenu : public Screen{
public:
    vector<Word*> words;
    
    MainMenu();
    ~MainMenu();
    
    void setup();
    void update();
    void draw();
    
    vector<Button> buttons;
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    
    
};
#endif /* defined(__Logic__MainMenu__) */
