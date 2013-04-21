//
//  Line.cpp
//  wireDrawingTest
//
//  Created by Surya on 12/04/13.
//
//

#include "Line.h"



Line::Line(){
    points.resize(100);
}

void Line::addPoint(ofVec2f p){
    points.push_back(p);
}

ofVec2f Line::getPoint(int i){

    return points[i];
}

int Line::size(){
    return points.size();
}
