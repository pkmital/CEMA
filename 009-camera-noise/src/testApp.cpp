#include "testApp.h"
#include "maximilian.h"

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

	prev_audio = 0;
	
	// setup the sound
	int sampleRate = 44100;
	int bufferSize = 320;
	ofSoundStreamSetup(2,				// output channels
					   1,				// input channels
					   sampleRate,		// how many samples (readings) per second
					   bufferSize,		// size of each copy of audio
					   4);				// latency of audio
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
	if(key == 's')
		camera.videoSettings();
}

void testApp::audioRequested(float *buf, int size, int ch)
{
	unsigned char *pixels = camera.getPixels();
	for (int i = 0; i < size; i++) {
		
		float audio = pixels[i] / 255.0 - 0.5;
		buf[i] = prev_audio * 0.9 + audio * 0.1;
		prev_audio = audio;
	}
}


void testApp::audioReceived(float *buf, int size, int ch)
{

}