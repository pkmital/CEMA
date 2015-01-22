#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		
		// redeclaration of functions (declared in base class)
		void setup();
		void update();
		void draw();
	
		// redeclaration of two special functions which handle audio i/o (declared in base class)
		void audioRequested(float *buf, int size, int ch);
		void audioReceived(float *buf, int size, int ch);
	
		// we will keep a pointer to our audio
		float *audioInput;
		int sampleRate, bufferSize;
};
