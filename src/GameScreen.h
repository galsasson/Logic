//
//  GameScreen.h
//  Logic
//
//  Created by Surya on 24/04/13.
//
//

#ifndef __Logic__GameScreen__
#define __Logic__GameScreen__
#include "Screen.h"
#include "ofMain.h"
#include "Level.h"
#include <iostream>
class GameScreen:public Screen{
public:
    GameScreen();
    Level *level;
    
    void setup(int levelID);
    void update();
    void draw();
    
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    
};
#endif /* defined(__Logic__GameScreen__) */
