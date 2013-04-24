//
//  Inventory.h
//  Logic
//
//  Created by Gal Sasson on 4/22/13.
//
//

#ifndef __Logic__Inventory__
#define __Logic__Inventory__

#include <iostream>
#include "ofMain.h"
#include "InventoryIcon.h"

class Inventory
{
    ofVec2f pos;
    ofVec2f size;
    
    vector<InventoryIcon*> icons;
    
public:
    Inventory(ofVec2f p);
    
    void addIcon(InventoryIcon *icon);
    
    InventoryIcon* contains(ofVec2f p);
    ofVec2f getWorldPosition();
    void draw();
};

#endif /* defined(__Logic__Inventory__) */
