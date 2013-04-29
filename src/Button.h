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
    Button(ofVec2f p, int w, int h);
    ofVec2f pos;
    
    int width;
    int height;
    
    bool contains(ofVec2f p);
    
};
#endif /* defined(__Logic__Button__) */
