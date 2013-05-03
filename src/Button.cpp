//
//  Button.cpp
//  Logic
//
//  Created by Surya on 28/04/13.
//
//

#include "Button.h"


Button::Button()
{
    pressed = false;
    navigate = false;
}

Button::~Button()
{
    
}
void Button::setup(ofRectangle rectangle, ofPoint trans)
{
    this->rectangle = rectangle;
    this->transform = trans;
}

void Button::draw()
{
    glPushMatrix();
        ofTranslate(transform.x, transform.y, 0);
        ofRect(0, 0, rectangle.getWidth(),rectangle.getHeight());
    glPopMatrix();
}

void Button::activateNavigation(bool navigate)
{
    this->navigate = navigate;
}

bool Button::getNavigate()
{
    return navigate;
}

bool Button::contains(ofVec2f p)
{
    
    if (p.x>transform.x && p.x<transform.x+rectangle.getWidth() && p.y<transform.y+rectangle.getHeight() && p.y>transform.y)
    {
       
        pressed = true;
        return true;
    }
    else {
        pressed = false;
        return false;
    }
}

