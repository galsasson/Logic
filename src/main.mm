#include "ofMain.h"
#include "testApp.h"

int main(){
    ofPtr<ofAppiPhoneWindow> iOSWindow = ofPtr<ofAppiPhoneWindow> (new ofAppiPhoneWindow());
    iOSWindow->enableRetina();
    iOSWindow->enableAntiAliasing(2);
    iOSWindow->enableRetinaSupport();
	ofSetupOpenGL(iOSWindow, 640, 960, OF_FULLSCREEN);			// <-------- setup the GL context
	ofRunApp(new testApp);
}
