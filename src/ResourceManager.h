//
//  ResourceManager.h
//  Logic
//
//  Created by Surya on 03/05/13.
//
//

#ifndef __Logic__ResourceManager__
#define __Logic__ResourceManager__

#include <iostream>
#include "ofMain.h"
class ResourceManager{
public:

    ResourceManager();
    ResourceManager(ofImage _i, ofTrueTypeFont _f);
    void addImage(ofImage _i);
    void addFont(ofTrueTypeFont _f);
    ofTrueTypeFont getResourceFont(int index);
    ofImage getResoureImage(int index);
    
    vector<ofImage> imgs;
    vector<ofTrueTypeFont> fonts;

    
};
#endif /* defined(__Logic__ResourceManager__) */
