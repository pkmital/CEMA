#include "testApp.h"

// here we "define" the methods we "declared" in the "testApp.h" file

// i get called once
void testApp::setup(){
	
	// set the size of the window
	ofSetWindowShape(320, 240);
	
	// the rate at which the program runs (FPS)
	ofSetFrameRate(30);
	
	// load a movie located in the project's "bin/data" directory
	videoPlayer.loadMovie("sunra_pink.mov");
	videoPlayer.play();
}

// i get called in a loop that runs until the program ends
void testApp::update(){
	
	// update the current frame
	videoPlayer.update();
}

// i also get called in a loop that runs until the program ends
void testApp::draw(){
	ofBackground(0);
	
	
	// this is a special command to change the way shapes, images, and videos are drawn.
	// normally, when you draw a shape at position 0,0 with a width of 100, and a height of 100,
	// the object occupies a space from point (0,0) to point (100,100).
	// however, when you use OF_RECTMODE_CENTER, to draw the object in the same place, you would
	// draw the shape at position 50,50, i.e. using the center of the object rather than the 
	// top-left corner
	ofSetRectMode(OF_RECTMODE_CENTER);
	 
	// this moves all future drawing commands to the position (160,120)
	ofTranslate(160, 120, 0);
	 
	// here we are rotating our world using the mouse
	float degreesToRotate =  (float)mouseX / (float)ofGetScreenWidth() * 360.0;
	// we rotate by the degrees calculated above using ofRotate.
	// the (0, 1, 0) say to rotate along the y-axis.  we could put 1's in the x or z as well.
	ofRotate(degreesToRotate, 0, 1, 0);
	

	// draw the movie a position 0,0
	videoPlayer.draw(0,0);
}
