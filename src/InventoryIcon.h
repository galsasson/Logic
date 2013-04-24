//
//  InventoryIcon.h
//  Logic
//
//  Created by Gal Sasson on 4/22/13.
//
//

#ifndef __Logic__InventoryIcon__
#define __Logic__InventoryIcon__

#include <iostream>
#include "ofMain.h"
//#include "Inventory.h"

class Inventory;

enum ItemType {
    INVITEM_NOT,
    INVITEM_AND,
    INVITEM_OR,
};

class InventoryIcon
{
private:
    string typeString;
    ofTrueTypeFont font;
    bool picked;
    
    string toString();
    
public:
    ofVec2f pos;
    ofVec2f size;
    Inventory *parent;
    ItemType type;

    InventoryIcon(ItemType type);
    
    bool contains(ofVec2f p);
    void pickUp();
    void putDown();
    
    ofVec2f getWorldPosition();
    void draw();
};

#endif /* defined(__Logic__InventoryIcon__) */
