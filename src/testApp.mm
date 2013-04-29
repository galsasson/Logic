#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
    vector<EState> i1;
    i1.push_back(HIGH);
    i1.push_back(LOW);
    
    vector<EState> i2;
    i2.push_back(LOW);
    i2.push_back(HIGH);
    
    vector<EState> exp;
    exp.push_back(HIGH);
    exp.push_back(HIGH);
    
    
    level = new Level(i1, i2, exp);
    
//    ofEnableSmoothing();

    ofEnableAlphaBlending();
    ofSetFrameRate(60);
	ofBackground(127,127,127);
}

//--------------------------------------------------------------
void testApp::update(){
    level->update();
}

//--------------------------------------------------------------
void testApp::draw(){
    // needed to support 320x480 screen (also for the simulator)
    //ofScale(0.5, 0.5);
    
	level->draw();
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    level->touchDown(touch);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    level->touchMoved(touch);
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    level->touchUp(touch);
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

