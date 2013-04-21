#include "ofMain.h"
#include "testApp.h"

int main(){
	ofSetupOpenGL(640,960, OF_FULLSCREEN);			// <-------- setup the GL context

	ofRunApp(new testApp);
}
