//
//  Word.h
//  Logic
//
//  Created by Ryan Bartley on 5/1/13.
//
//

#pragma once
#include "ofMain.h"
#include "Letter.h"
#include "Button.h"

class Word {
    
    vector<Letter*> letters;
    string word;
    ofPoint position;
    ofPoint transform;
    ofTrueTypeFont font;
    
    float depth;
    string fontTitle;
    int fontsize;
    Button* button;
    
    bool isButton;
    
public:
    
    Word(ofPoint position, string font, string word, float depth, int fontsize, bool button);
    ~Word();
    
    void setup();
    void draw();
    
    bool getIsButton();
    Button* getButton();
    ofRectangle getBoundingBox();
    
};
