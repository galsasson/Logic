//
//  LevelSelector.h
//  Logic
//
//  Created by Surya on 24/04/13.
//
//

#ifndef __Logic__LevelSelector__
#define __Logic__LevelSelector__
#include "Screen.h"

#include <iostream>
class LevelSelector:public Screen{
public:
    LevelSelector();
    
    void setup();
    void update();
    void draw();
    
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    
};
#endif /* defined(__Logic__LevelSelector__) */
