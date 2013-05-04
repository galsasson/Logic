//
//  ResourceManager.cpp
//  Logic
//
//  Created by Surya on 03/05/13.
//
//

#include "ResourceManager.h"

ResourceManager :: ResourceManager(){
    //font = ofTrueTypeFont();
    //img = ofImage();
}

ResourceManager :: ResourceManager(ofImage _i, ofTrueTypeFont _f){
    imgs.push_back(ofImage(_i));
    fonts.push_back(ofTrueTypeFont(_f));

    
}

void ResourceManager::addImage(ofImage _i){
    imgs.push_back(ofImage(_i));

}

void ResourceManager::addFont(ofTrueTypeFont _f){
    fonts.push_back(ofTrueTypeFont(_f));
    
}


ofImage ResourceManager::getResoureImage(int index){
    return imgs[index];
}

ofTrueTypeFont ResourceManager:: getResourceFont(int index){
    return fonts[index];
}