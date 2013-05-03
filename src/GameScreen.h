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
    GameScreen(int levelID);
    Level *level;
    
    void setup();
    void update();
    void draw();
    
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    
    int levelID;
    
};
#endif /* defined(__Logic__GameScreen__) */
