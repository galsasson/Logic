//
//  Letter.cpp
//  Logic
//
//  Created by Ryan Bartley on 4/29/13.
//
//

#include "Letter.h"

void Letter::setup(ofPath letter, float depth, float height)
{
    front = letter.getTessellation();
    back = front;

    //color stuff that i was playing around with
    
//    ofFloatColor red, green, blue;
//    red = ofFloatColor(1, 0, 0);
    
    this->transformHeight = height;
    
    vector<ofPoint>& v = back.getVertices();
    for (vector<ofPoint>::iterator it = v.begin(); it != v.end(); it++) {
        
        //push the back vertices back by depth
        it->z -= depth;
        
        //this is where we'd add color to the letters
        //maybe create an interface for giving new colors around.
        
//        float number = static_cast<float>(v.end()-it)/static_cast<float>(v.end()-v.begin());
//        red.setHsb(0, 0, number);
//        if (v.end()-it == v.size()) {
//            back.addColor(red);
//            front.addColor(red);
//        } else if (v.end()-it == 0) {
//            back.addColor(red);
//            front.addColor(red);
//        }
        
    }
    
    //creating the in between mesh between the front and the back
    
    vector<ofPolyline> lines = letter.getOutline();
    for(int j=0; j<lines.size(); j++)
    {
        
        vector<ofPoint>& points = lines[j].getVertices();
        int k;
        for(k=0; k<points.size()-1; k++)
        {
            ofPoint p1 = points[k+0];
            ofPoint p2 = points[k+1];
            
            side.addVertex(p1);
            side.addVertex(p2);
            side.addVertex(ofPoint(p1.x, p1.y, p1.z-depth));
            
            side.addVertex(ofPoint(p1.x, p1.y, p1.z-depth));
            side.addVertex(ofPoint(p2.x, p2.y, p2.z-depth));
            side.addVertex(p2);
        }
        
    
        ofPoint p1 = points[k];
        ofPoint p2 = points[0];
        
        side.addVertex(p1);
        side.addVertex(p2);
        side.addVertex(ofPoint(p1.x, p1.y, p1.z-depth));
        
        side.addVertex(ofPoint(p1.x, p1.y, p1.z-depth));
        side.addVertex(ofPoint(p2.x, p2.y, p2.z-depth));
        side.addVertex(p2);
    }
    
}

void Letter::draw()
{
    //drawing the letters
    glPushMatrix();
        //transforming them under the line that they start at to match the button
        //inside word
        ofTranslate(0, transformHeight);
        front.draw();
        back.draw();
        side.draw();
    glPopMatrix();
}