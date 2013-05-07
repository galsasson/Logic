//
//  InventoryIcon.cpp
//  Logic
//
//  Created by Gal Sasson on 4/22/13.
//
//

#include "InventoryIcon.h"
#include "Inventory.h"

InventoryIcon::InventoryIcon(ItemType t)
{
    type = t;
    typeString = toString();
    picked = false;
    
    size = ofVec2f(80, 60);
    
    
}
void InventoryIcon::loadResources(){
    font.loadFont("Rationale-Regular.ttf", 25);
}

string InventoryIcon::toString()
{
    switch (type)
    {
        case INVITEM_NOT:
            return "NOT";
        case INVITEM_AND:
            return "AND";
        case INVITEM_OR:
            return "OR";
    }
}

bool InventoryIcon::contains(ofVec2f p)
{
    if (p.x > pos.x && p.x < pos.x + size.x &&
        p.y > pos.y && p.y < pos.y + size.y)
    {
        return true;
    }
    
    return false;
}

void InventoryIcon::pickUp()
{
    picked = true;
}

void InventoryIcon::putDown()
{
    picked = false;
}

ofVec2f InventoryIcon::getWorldPosition()
{
    if (parent)
        return parent->getWorldPosition() + pos;
    
    return pos;
}

void InventoryIcon::draw()
{
    ofPushMatrix();
    ofTranslate(pos);
    
    ofFill();
    ofSetColor(40);
    ofRect(0, 0, size.x, size.y);
    ofSetColor(180);
    ofSetLineWidth(2);
    
    // draw chip "legs"
    float x = size.x/6;
    for (int i=0; i<5; i++)
    {
        ofLine(x, -5, x, 5);
        ofLine(x, size.y-5, x, size.y+5);
        x += size.x/6;
    }
    
    ofSetColor(255);
    ofRectangle rect = font.getStringBoundingBox(typeString, 0, 0);
    font.drawString(typeString, size.x/2 - rect.width/2, size.y/2+rect.height/2);
    
    ofPopMatrix();
}

