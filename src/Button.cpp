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
}

Button::~Button()
{
    
}
void Button::setup(ofRectangle rectangle, ofVec2f pos)
{
    this->rectangle = rectangle;
    this->position = pos;
    cout << "x is " << position.x << " and y is "<< position.y << " which makes right side " << position.x+this->rectangle.width << " and the bottom side is " << position.y+this->rectangle.height << endl;
}

void Button::draw()
{
    
//            ofTranslate(rectangle.x-(rectangle.getWidth()/2.0), rectangle.y-(rectangle.getHeight()/2)-125, 0);
            
            ofRect(position.x, position.y, rectangle.getWidth(), rectangle.getHeight());
            
       
    
    
}

bool Button::contains(ofVec2f p)
{
    cout << "Position incoming " << p << " and the position of the Bounding box is " << position << " and Bounding box width is " << position.x+rectangle.getWidth() << " and Bounding box height is " << position.y+rectangle.getHeight() << endl;
    
    if (p.x>position.x && p.x<position.x+rectangle.getWidth() && p.y<position.y+rectangle.getHeight() && p.y>position.y)
    {
        pressed = true;
        return true;
    }
    else {
        pressed = false;
        return false;
    }
}

