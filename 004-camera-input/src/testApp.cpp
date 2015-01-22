#include "testApp.h"

// here we "define" the methods we "declared" in the "testApp.h" file

// i get called once
void testApp::setup(){
	
	// do some initialization
	
	// set the size of the window
	ofSetWindowShape(320, 240);
	
	// the rate at which the program runs (FPS)
	ofSetFrameRate(30);
	
	// setup the camera
	camera.initGrabber(320, 240);
}

// i get called in a loop that runs until the program ends
void testApp::update(){
	camera.update();
}

// i also get called in a loop that runs until the program ends
void testApp::draw(){
	ofBackground(0);
	
	// draw the camera
	camera.draw(0,0);
}

void testApp::keyPressed(int key)
{
	switch (key) {
		case 's':
			camera.videoSettings();
			break;
		default:
			break;
	}
}