#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofEnableAlphaBlending();
    ofSetFrameRate(60);

    
    
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
//    screen =&mainMenu;
    screen = new MainMenu();
    screen->setup();
    ofSetBackgroundColor(0, 0, 0);
    
}

//--------------------------------------------------------------
void testApp::update(){
    screen->update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    // needed to support 320x480 screen (also for the simulator)
    //ofScale(0.5, 0.5);
    screen->draw();
    ofSetBackgroundColor(0, 0, 0);
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){

    screen->touchDown(touch);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){

    screen->touchMoved(touch);
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){

    screen->touchUp(touch);
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::lostFocus(){

}

//--------------------------------------------------------------
void testApp::gotFocus(){

}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

}

void testApp::selectScreen(string word, MainMenu *menu)
{
    
    if (word == "Play") {
        screen = new LevelSelector();
        screen->setup();
    } else if (word == "Help") {
        
    } else if (word == "Settings") {
        
    } else {
        
    }
    
    if (screen != NULL) {
        delete menu;
    }
}

void testApp::selectScreen(string word, LevelSelector *levelselector)
{
    if (word == "1") {
        screen = new GameScreen(0);
        screen->setup();
    } else if (word == "2") {
        screen = new GameScreen(1);
        screen->setup();
    } else if (word == "3") {
        screen = new GameScreen(2);
        screen->setup();
    } else if (word == "4") {
        screen = new GameScreen(3);
        screen->setup();
    } else if (word == "5") {
        screen = new GameScreen(4);
        screen->setup();
    } else if (word == "6") {
        screen = new GameScreen(5);
        screen->setup();
    } else if (word == "7") {
        screen = new GameScreen(6);
        screen->setup();
    } else if (word == "8") {
        screen = new GameScreen(7);
        screen->setup();
    } else if (word == "9") {
        screen = new GameScreen(8);
        screen->setup();
    } else if (word == "10") {
        screen = new GameScreen(9);
        screen->setup();
    } else if (word == "Back") {
        screen = new MainMenu();
        screen->setup();
    } 
    
    if (screen != NULL) {
        delete levelselector;
    }
}

