#pragma once

#include "ofMain.h"
#include "maximilian.h"

class testApp : public ofBaseApp{

	public:
		
		// redeclaration of functions (declared in base class)
		void setup();
		void update();
		void draw();
	
		void keyPressed(int key);
	
		void audioRequested(float *buf, int size, int ch);
		void audioReceived(float *buf, int size, int ch);
	
		ofVideoGrabber camera;
	
		float prev_audio;
};
