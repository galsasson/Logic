//
//  Button.h
//  Logic
//
//  Created by Surya on 28/04/13.
//
//

#ifndef __Logic__Button__
#define __Logic__Button__

#include <iostream>
#include  "ofMain.h"
class Button{
    
    
    
public:
    Button();
    ~Button();
    void setup(ofRectangle rectangle, ofPoint trans);
    
    ofRectangle rectangle;
    
    ofPoint transform;
    bool pressed;
    bool navigate;
    
    bool contains(ofVec2f p);
    void draw();
    void activateNavigation(bool navigate);
    bool getNavigate();
    
};
#endif /* defined(__Logic__Button__) */
