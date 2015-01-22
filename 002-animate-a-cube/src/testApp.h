#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		
		// declaration of functions
		void setup();
		void update();
		void draw();
	
		int counter;
		float brightness;
    
};
