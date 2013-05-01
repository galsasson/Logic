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
    
    bool pressed;
    
public:
    Button();
    ~Button();
    void setup(ofRectangle rectangle, ofVec2f pos);
    
    ofRectangle rectangle;
    ofPoint position;
    
    bool contains(ofVec2f p);
    void draw();
};
#endif /* defined(__Logic__Button__) */
