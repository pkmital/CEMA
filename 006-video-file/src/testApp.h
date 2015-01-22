#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		
		// redeclaration of functions (declared in base class)
		void setup();
		void update();
		void draw();
	
		ofVideoPlayer videoPlayer;
	
		ofSoundPlayer sound1, sound2;
};
