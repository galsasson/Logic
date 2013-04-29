//
//  Button.cpp
//  Logic
//
//  Created by Surya on 28/04/13.
//
//

#include "Button.h"


Button::Button(){

}


Button::Button(ofVec2f p, int w, int h){
    
    pos = ofVec2f(p);
    width = w;
    height = h;
}

bool Button::contains(ofVec2f p){
    

    return (p.x>pos.x && p.x<pos.x+width && p.y<pos.y+height && p.y>pos.y);
}

