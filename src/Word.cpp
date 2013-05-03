//
//  Word.cpp
//  Logic
//
//  Created by Ryan Bartley on 5/1/13.
//
//

#include "Word.h"

Word::Word(ofPoint position, string font, string word, float depth, int fontsize, bool button)
{
    //This is the position of the word and it will use this position for the button as well
    this->position = position;
    this->fontTitle = font;
    this->word = word;
    this->depth = depth;
    this->fontsize = fontsize;
    
    this->animationAmount = -15;
    
    //Whether we want to use a button making it false will make the pointer null
    isButton = button;
    if (isButton) {
        this->button = new Button();
    } else {
        this->button = NULL;
    }
    
    transform = ofPoint(0,0,0);
    zAnimation = 0;
}

Word::~Word()
{
    //destructor for all words called through the delete in the menus
    
    for (vector<Letter*>::iterator it = letters.begin(); it != letters.end(); it++) {
        delete *it;
    }
    if (isButton) {
        delete button;
    }
    
}

string Word::getWord()
{
    return word;
}

void Word::setup()
{

    this->position = position;
    
    //font set up stuff
    //maybe we'll send these in to the constructor as well at some point
    bool bAntiAliased = true;
    bool bFullCharacterSet = true;
    bool makeContours = true;
    float simplifyAmt = 30; // uses ofPolyline::simplify
    
    //creating the font
    
    this->font.loadFont(fontTitle, fontsize, bAntiAliased, bFullCharacterSet, makeContours, simplifyAmt);
    this->font.setLineHeight(fontsize+10);
    
    //creating the overall transform point for the draw and also the button position

    this->transform = ofPoint(position.x-(getBoundingBox().getWidth()/2.0), position.y-(getBoundingBox().getHeight()/2)-100, position.z);

    //if it's a button setup the button
    //the transform gives the position in screen space
    
    if (isButton) {
        this->button->setup(getBoundingBox(), this->transform);
    } 
    
    //create the letters and push them down based upon the bounding box
    //height specifically used because of button placement and text origin
    //text writes up and 
    
    vector<ofPath> letterPaths = this->font.getStringAsPoints(this->word);
    for(int i=0; i<letterPaths.size(); i++)
    {
        Letter* l = new Letter();
        l->setup(letterPaths[i], this->depth, getBoundingBox().height);
        letters.push_back(l);
    }

}

void Word::animate()
{
    if (zAnimation < -100) {
        animationAmount = 15;
    } else if (zAnimation > 100) {
        animationAmount = -15;
    }
    zAnimation+=animationAmount;
    
    if (zAnimation > 1) {
        button->activateNavigation(true);
    }
}

void Word::draw()
{
    
    glEnable(GL_DEPTH_TEST);
    
    {
        ofPushMatrix();
        {
            //using the transform that was created above to make sure it is directly in the middle
            //we're transforming by half the width and subtracting that from the position we'd like
            //it to be.
            ofTranslate(this->transform.x, this->transform.y, this->transform.z+zAnimation);
            
            //for debug of button, uncomment this.
            
            
            //drawing letters inside this transform
            for(vector<Letter*>::iterator it = letters.begin(); it != letters.end(); it++)
            {
                (*it)->draw();
                
            }
            
        }
        ofPopMatrix();
    }
//    if (isButton) {
//        button->draw();
//    }
    glDisable(GL_DEPTH_TEST);
}

bool Word::getIsButton()
{
    //checking whether we this is a button to see if we need to return it
    return isButton;
}

Button* Word::getButton()
{
    //returning the button to see if we're touching it through .contain
    return button;
}

ofRectangle Word::getBoundingBox()
{
    //created to give the bounding box to figure out where the user presses.
    return font.getStringBoundingBox(word, 0, 0);
}
