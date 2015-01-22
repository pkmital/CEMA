#include "testApp.h"

// here we "define" the methods we "declared" in the "testApp.h" file

// i get called once
void testApp::setup(){
	
	// set the size of the window
	ofSetWindowShape(250, 250);
	
	// the rate at which the program runs (FPS)
	ofSetFrameRate(30);
	
	// load a specific sound file
	sound.loadSound("5_gongs.aif", false);
	sound.setLoop(true);
	
	counter = 0;
}

// i get called in a loop that runs until the program ends
void testApp::update(){

}

// i also get called in a loop that runs until the program ends
void testApp::draw(){
	ofBackground(0);
		
}

void testApp::mousePressed(int x, int y, int button){
	counter = (counter + 1) % 2;
	
	if (counter == 0) {
		sound.loadSound("5_gongs.aif", false);
	}
	else if (counter == 1) {
		sound.loadSound("5_tri-part.aif", false);
	}
	
	sound.play();
}