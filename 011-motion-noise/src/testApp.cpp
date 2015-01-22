#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	// change the window to hold enough space for 6 movies (3x2)
	ofSetWindowShape(320*3,240*2);
	
	ofSetFrameRate(30);
	
	// initialize our camera with a resolution of 320z240
	vidGrabber.initGrabber(320,240);
	
	sum = 0;
	
	// these are (wrappers for) opencv image containers 
	// we'll use for image processing
	// we are going to find the difference between successive frames
    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayPreviousImage.allocate(320,240);
	grayDiff.allocate(320,240);
	
	mySample.load(ofToDataPath("beat2.wav"), 1);
	
	channel = 0;
	quad = new double[4];
	// center 0
	// sub 1
	// FR - FL 2,3
	// SR - SL 4,5
	
	// setup the sound
	int sampleRate = 48000;
	int bufferSize = 512;
	ofSoundStreamSetup(numchannels,		// output channels
					   1,				// input channels
					   sampleRate,		// how many samples (readings) per second
					   bufferSize,		// size of each copy of audio
					   4);				// latency of audio
}

//--------------------------------------------------------------
void testApp::update(){
	// background to black
	ofBackground(0);
	
	// update the camera
	vidGrabber.update();
	// set the color image (opencv container) to the camera image
    colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
	// convert to grayscale
	grayImage = colorImg;
	// calculate the difference image
	grayDiff = grayImage;
	// compute the absolute difference with the previous frame's grayscale image
	grayDiff.absDiff(grayPreviousImage);
	
	// store the current grayscale image for the next iteration of update()
	grayPreviousImage = colorImg;
	
	// let's threshold the difference image,
	// all values less than 10 are 0, all values above 10 become 255
	grayDiff.threshold(10);
	
	// here we will find the sum and then average of all the pixels in the difference image
	// this will be used for a simple measure of "motion" 
	sum = 0.9 * sum + 0.1 * cvSum(grayDiff.getCvImage()).val[0] / 320.0 / 240.0 / 10.0;
	
	cvMinMaxLoc(grayDiff.getCvImage(), &minVal, &maxVal, &minLoc, &maxLoc);
	
	
}

//--------------------------------------------------------------
void testApp::draw(){
	// draw the input camera image
	vidGrabber.draw(0,0);
	// draw the opencv image
	colorImg.draw(0,240);
	// draw the grayscale conversion
	grayImage.draw(320,0);
	// draw the previous grayscale image
	grayPreviousImage.draw(320,240);
	// draw the difference image (thresholded)
	grayDiff.draw(640,0);
	
	// draw the sum of the motion pixels divided by the number of motion pixels 
	// (average of difference values)
	char buf[256];
	sprintf(buf, "%f", sum);
	ofDrawBitmapString(buf, 20, 20);
}


void testApp::audioRequested(float *buf, int size, int ch)
{
	memset(buf, 0, sizeof(float)*numchannels*size);
	for (int i = 0; i < size; i++) {
		//double sample = myFilter.lopass( mySample.play(sum) * 2.0, ofClamp(sum/2.0, 0.1, 0.6) );//mySample.play();
		double sample = mySample.play();
		quad = myAmbisonic.quad(sample, 
								quad, 
								1.0 - (float)mouseX / (float)ofGetScreenWidth() , 
								1.0 - (float)mouseY / (float)ofGetScreenHeight() );
		buf[i*numchannels + 0] = sample / 3.0;
		buf[i*numchannels + 2] = quad[0];
		buf[i*numchannels + 3] = quad[1];
		buf[i*numchannels + 4] = quad[2];
		buf[i*numchannels + 5] = quad[3];
	}
}

void testApp::keyPressed(int key)
{
	if (key == '0') 
		channel = 0;
	else if(key == '1')
		channel = 1;
	else if(key == '2')
		channel = 2;
	else if(key == '3')
		channel = 3;
	else if(key == '4')
		channel = 4;
	else if(key == '5')
		channel = 5;
}

void testApp::mouseMoved(int x, int y, int button)
{
	
}

void testApp::audioReceived(float *buf, int size, int ch)
{
	
}