#include "testApp.h"

// here we "define" the methods we "declared" in the "testApp.h" file

// i get called once
void testApp::setup(){
	
	// do some initialization
	
	// set the size of the window
	ofSetWindowShape(250, 250);
	
	// the rate at which the program runs (FPS)
	ofSetFrameRate(30);
	
	// we are going to increment this variable each "frame"
	counter = 0;
	
}

// i get called in a loop that runs until the program ends
void testApp::update(){

	// update some variables
	counter = counter + 1;
}

// i also get called in a loop that runs until the program ends
void testApp::draw(){
	ofBackground(0);
	
		
	ofSetColor(255, 0, 0);
	ofLine(0, 125, 250, 125);
	
	
	
	 float amplitude = 100.0f;

	ofSetColor(200, 200, 200);
	for (int i = 1; i < 250; i++) {
		
		float x1 = (float)i / 250.0;
		float y1 = amplitude * sin( x1 * 2.0*PI );
		float x2 = (float)(i - 1) / 250.0;
		float y2 = amplitude * sin( x2 * 2.0*PI );
		
		ofLine(x1 * 250.0f, -y1 + 125, x2 * 250.0f, -y2 + 125);
	}
	 
}