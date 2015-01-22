#include "testApp.h"

// here we "define" the methods we "declared" in the "testApp.h" file

// i get called once
void testApp::setup(){
	
	// do some initialization
	
	// set the size of the window
	ofSetWindowShape(250, 250);
	
	// the rate at which the program runs (FPS)
	ofSetFrameRate(30);
	
	// setup the sound
	sampleRate = 44100;
	bufferSize = 250;
	ofSoundStreamSetup(2,				// output channels
					   2,				// input channels
					   sampleRate,		// how many samples (readings) per second
					   bufferSize,		// size of each copy of audio
					   4);				// latency of audio
	
	
	// a variable to store our audio
	audioInput = new float[bufferSize * 2];
}

// i get called in a loop that runs until the program ends
void testApp::update(){

}

// i also get called in a loop that runs until the program ends
void testApp::draw(){
	ofBackground(0);
	
	float amplitude = 100.0f;
	
	ofSetColor(100, 100, 100);
	ofLine(0, 125, 250, 125);
	
	ofSetColor(200, 180, 180);
	for (int i = 2; i < 250; i+=2) {
		
		float x1 = (float)i / 250.0;
		float y1 = amplitude * audioInput[i];	//amplitude * sin( x1 * 2.0*PI );
		float x2 = (float)(i - 1) / 250.0;
		float y2 = amplitude * audioInput[i-2];	//amplitude * sin( x2 * 2.0*PI );
		
		ofLine(x1 * 250.0f, -y1 + 125, x2 * 250.0f, -y2 + 125);
	}
	
	ofSetColor(200, 220, 220);
	for (int i = 3; i < 250; i+=2) {
		
		float x1 = (float)i / 250.0;
		float y1 = amplitude * audioInput[i];	//amplitude * sin( x1 * 2.0*PI );
		float x2 = (float)(i - 1) / 250.0;
		float y2 = amplitude * audioInput[i-2];	//amplitude * sin( x2 * 2.0*PI );
		
		ofLine(x1 * 250.0f, -y1 + 125, x2 * 250.0f, -y2 + 125);
	}
}

void testApp::audioRequested(float *buf, int size, int ch)
{
	
}

void testApp::audioReceived(float *buf, int size, int ch)
{
	// copy the data into our variable, audioInput
	memcpy(audioInput, buf, sizeof(float) * size * ch);
}