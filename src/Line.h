//
//  Line.h
//  wireDrawingTest
//
//  Created by Surya on 12/04/13.
//
//

#pragma once
#include <iostream>
#include "ofMain.h"

class Line{
public:
    Line();

    void addPoint(ofVec2f p);
    ofVec2f getPoint(int i);
    int size();
    
    vector<ofVec2f> points;
};

