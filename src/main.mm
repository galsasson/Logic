#include "ofMain.h"
#include "testApp.h"

int main(){
    ofAppiPhoneWindow * iOSWindow = new ofAppiPhoneWindow();
	ofSetupOpenGL(iOSWindow, 640,960, OF_FULLSCREEN);			// <-------- setup the GL context
    iOSWindow->enableRetina();
    iOSWindow->enableAntiAliasing(2);
    

	ofRunApp(new testApp);
}
