#include "testApp.h"

// here we "define" the methods we "declared" in the "testApp.h" file

// i get called once
void testApp::setup(){
	
	// do some initialization
	
	// set the size of the window
	ofSetWindowShape(250, 250);
	
	// the rate at which the program runs (FPS)
	ofSetFrameRate(30);
	
	myFont.loadFont("dekar.ttf", 36);
	
	// don't clear the background on each update/draw loop
	// ofSetBackgroundAuto(false);
}

// i get called in a loop that runs until the program ends
void testApp::update(){
	
}

// i also get called in a loop that runs until the program ends
void testApp::draw(){
	
	// set the size of the circle
	float radius = 3.0f;
	
	// draw a circle at the mouse position
	ofCircle(mouseX, mouseY, radius);
	
	myFont.drawString("hello!", 50, 50);
	
	char buf[256];
	sprintf(buf, "%d %d", mouseX, mouseY);
	myFont.drawString(buf, 50, 125);
	
	// note: 
	// the two variables, mouseX and mouseY are declared 
	// in the base (parent) class
}