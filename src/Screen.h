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
#include "Word.h"

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
    
    virtual void lightSetup();
    virtual void lightUpdate();
    virtual void lightDraw();
    virtual void drawElements();
    
    virtual bool getIsSetup();
    
protected:    
    bool isSetup;
    ofLight light;
	ofVec3f center;
    ofColor lightColor;
    float colorHue;
    vector<Word*> words;
    bool touchedButton;

};
#endif /* defined(__Logic__Screen__) */
