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
#include "ofMain.h"

class MainMenu : public Screen{
public:
    
    
    MainMenu();
    ~MainMenu();
    
    void setup();
    void update();
    void draw();
    
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    
    void drawElements();
    
    void buttonAnimandNavi();
    
    
    
};
#endif /* defined(__Logic__MainMenu__) */
