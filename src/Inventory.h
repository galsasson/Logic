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
    
public:
    Inventory(ofVec2f p);
    
    void addIcon(InventoryIcon *icon);
    
    bool contains(ofVec2f p);
    InventoryIcon* getIcon(ofVec2f p);
    ofVec2f getWorldPosition();
        vector<InventoryIcon*> icons;
    void draw();
};

#endif /* defined(__Logic__Inventory__) */
