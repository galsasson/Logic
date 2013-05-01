//
//  Screen.h
//  Logic
//
//  Created by Surya on 24/04/13.
//
//

#ifndef __Logic__Screen__
#define __Logic__Screen__

#include <iostream>
#include "ofMain.h"
#include "Letter.h"

class Screen{
public:
    
    
    Screen();
    
    virtual void setup();
    virtual void update();
    virtual void draw();
    

    
    virtual void touchDown(ofTouchEventArgs & touch);
    virtual void touchMoved(ofTouchEventArgs & touch);
    virtual void touchUp(ofTouchEventArgs & touch);
    virtual void touchDoubleTap(ofTouchEventArgs & touch);
    virtual void touchCancelled(ofTouchEventArgs & touch);
    
    ofImage background;
    
    ofTrueTypeFont font;

};
#endif /* defined(__Logic__Screen__) */
