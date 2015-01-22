#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	// change the window to hold enough space for 6 movies (3x2)
	ofSetWindowShape(320,240);
	
	ofSetFrameRate(30);
	
	// initialize our camera with a resolution of 320z240
	vidGrabber.initGrabber(320,240);
	
	// load a movie in and set it to loop, and then start it (play())
	vidPlayer.loadMovie("sunra_pink.mov");
	vidPlayer.setLoopState(OF_LOOP_NORMAL);
	vidPlayer.play();
	
	sum = 0;
	
	// these are (wrappers for) opencv image containers 
	// we'll use for image processing
	// we are going to find the difference between successive frames
    colorImg.allocate(320,240);
	colorDiffImg.allocate(320, 240);
	grayImage.allocate(320,240);
	grayPreviousImage.allocate(320,240);
	grayDiff.allocate(320,240);
	previousImages.push_back(grayPreviousImage);
	previousImages.push_back(grayPreviousImage);
	previousImages.push_back(grayPreviousImage);
	
}

//--------------------------------------------------------------
void testApp::update(){
	// background to black
	ofBackground(0);
	
	// update the camera
	vidGrabber.update();
	
	if (vidGrabber.isFrameNew()) {
		// set the color image (opencv container) to the camera image
		colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
		// convert to grayscale
		grayImage = colorImg;
		// calculate the difference image
		grayDiff = grayImage;
		// compute the absolute difference with the previous frame's grayscale image
		grayDiff.absDiff(previousImages[0]);
		
		// store the current grayscale image for the next iteration of update()
		previousImages.push_back(grayImage);
		if (previousImages.size() > 10) {
			previousImages.erase(previousImages.begin());
		}
		
		// let's threshold the difference image,
		// all values less than 10 are 0, all values above 10 become 255
		//grayDiff.threshold(10);
		
		// here we will find the sum and then average of all the pixels in the difference image
		// this will be used for a simple measure of "motion" 
		sum = 0.9 * sum + 0.1 * cvSum(grayDiff.getCvImage()).val[0] / 320.0 / 240.0 / 10.0;
		
		// let's change the speed of our movie based on the motion value we calculated
		vidPlayer.setSpeed(sum);
		vidPlayer.update();
	}
	
	
}

//--------------------------------------------------------------
void testApp::draw(){
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	colorImg.draw(0,0,ofGetWindowWidth(),ofGetWindowHeight());
	grayDiff.draw(0,0,ofGetWindowWidth(),ofGetWindowHeight());

	
	// draw the sum of the motion pixels divided by the number of motion pixels 
	// (average of difference values)
	char buf[256];
	sprintf(buf, "%f", sum);
	ofDrawBitmapString(buf, 20, 20);
}

