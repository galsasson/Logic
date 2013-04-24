//
//  Inventory.cpp
//  Logic
//
//  Created by Gal Sasson on 4/22/13.
//
//

#include "Inventory.h"
#include "ColorScheme.h"

Inventory::Inventory(ofVec2f p)
{
    pos = p;
    
    size = ofVec2f(540, 100);
}


void Inventory::addIcon(InventoryIcon *icon)
{
    // find the next available spot to put the icon in.
    float x=10;
    for (int i=0; i<icons.size(); i++)
    {
        x += icons[i]->size.x+30;
    }
    
    icon->pos = ofVec2f(x, size.y/2 - icon->size.y/2);
    
    icon->parent = this;
    icons.push_back(icon);
}

InventoryIcon* Inventory::contains(ofVec2f p)
{
    for (int i=0; i<icons.size(); i++)
    {
        if (icons[i]->contains(p-pos))
            return icons[i];
    }
    
    return NULL;
}

ofVec2f Inventory::getWorldPosition()
{
    return pos;
}

void Inventory::draw()
{
    ofPushMatrix();
    ofTranslate(pos);
    
    ofFill();
    ofSetColor(ColorScheme::getColor(4)*0.2);
    ofRect(0, 0, size.x, size.y);
    
    for (int i=0; i<icons.size(); i++)
    {
        icons[i]->draw();
    }
    
    ofPopMatrix();
}