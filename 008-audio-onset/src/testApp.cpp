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
					   1,				// input channels
					   sampleRate,		// how many samples (readings) per second
					   bufferSize,		// size of each copy of audio
					   4);				// latency of audio
	
	
	// a variable to store our audio
	audioInput = new float[bufferSize];

	rms_values.push_back(0);
}

// i get called in a loop that runs until the program ends
void testApp::update(){

	// we can "smooth" the rms value by using feedback.
	// this is a simple example of using the previous value 
	// with a weight (0.9) and the current value (0.1)
	// rms_values.push_back(0.9 * rms_values.back() + 0.1 * rms);
	
	// add the current rms value
	rms_values.push_back(rms);
	
	// we only keep a maximum of 25 values of the rms readings
	if (rms_values.size() > 25) {
		// if we have added more than 25, then we delete the first one
		rms_values.erase(rms_values.begin(), rms_values.begin() + 1);
	}
	
	
}

// i also get called in a loop that runs until the program ends
void testApp::draw(){
	ofBackground(0);
	
	// draw a line across the middle of the screen
	ofSetColor(100, 100, 100);
	ofLine(0, 125, 250, 125);
	
	// we draw the audio input as before
	ofSetColor(200, 200, 200);
	float amplitude = 100.0f;
	for (int i = 1; i < 250; i++) {
		
		// get two pairs of points
		float x1 = (float)i / 250.0;
		float y1 = amplitude * audioInput[i];	//amplitude * sin( x1 * 2.0*PI );
		float x2 = (float)(i - 1) / 250.0;
		float y2 = amplitude * audioInput[i-1];	//amplitude * sin( x2 * 2.0*PI );
		
		// draw a tiny segment of the overall line
		ofLine(x1 * 250.0f, -y1 + 125, 
			   x2 * 250.0f, -y2 + 125);
		
		// loop until i is no longer < 250
	}
	
	// draw a circle in the middle of the screen with the size
	// set by the rms value
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofCircle(125, 125, rms * 250);
	ofSetRectMode(OF_RECTMODE_CORNER);

	for (int i = 1; i < rms_values.size(); i++) {
		ofLine((i  ) * 250.0/25.0, -rms_values[i  ]*1000.0 + 250.0, 
			   (i-1) * 250.0/25.0, -rms_values[i-1]*1000.0 + 250.0);
	}
	
	// calculate the average of the rms values
	float average_rms = 0.0f;
	for (int i = 0; i < rms_values.size(); i++) {
		average_rms = average_rms + rms_values[i];
	}
	average_rms = average_rms / rms_values.size();
	
	// calculate the variance of the rms values
	float var_rms = 0.0f;
	for (int i = 0; i < rms_values.size(); i++) {
		var_rms = var_rms + abs(rms_values[i] - average_rms);
	}
	var_rms = var_rms / rms_values.size();
	
	// now we see if the current value is outside the mean + variance
	// basic statistics tells us a normally distributed function
	// has a mean and a variance where 97% of the data is explained by
	// 3 standard deviations.  we use this principle here in detecting 
	// the the current rms reading is outside this probability
	if (rms_values.back() > (average_rms + 2.0*var_rms)) {
		// draw a rectangle to denote the detection of an onset
		ofRect(0, 0, 250, 250);
	}
	
}

void testApp::audioRequested(float *buf, int size, int ch)
{
	
}

void testApp::audioReceived(float *buf, int size, int ch)
{
	// copy the data into our variable, audioInput
	memcpy(audioInput, buf, sizeof(float) * size);
	
	// add all the audio input values
	float total = 0;
	for (int i = 0; i < size; i++) {
		// we add the "square" of each value so that negative numbers
		// become positive.  this is like thinking of the "magnitude"
		total = total + (buf[i] * buf[i]);
	}
	// the "mean" part of the RMS, we divide by the number of audio input samples
	// we added in the for loop above
	total = total / (float)size;
	
	// the "root" part of RMS, we take the square root to get our RMS reading for the 
	// current chunk of audio input values
	rms = sqrt(total);
	
}