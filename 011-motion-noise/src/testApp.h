#pragma once

#include "ofMain.h"

#include "maximilian.h"										// new
#include "ofxOpenCv.h"

#define numchannels 6

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();	
	
		void audioRequested(float *buf, int size, int ch); // new
		void audioReceived(float *buf, int size, int ch);  // new
		 
		void keyPressed(int key);
	
	void mouseMoved(int x, int y, int button);
	
		double					minVal,	maxVal;
		CvPoint					minLoc, maxLoc;
		float					sum;
		ofVideoGrabber			vidGrabber;

        ofxCvColorImage			colorImg;

        ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayPreviousImage;
		ofxCvGrayscaleImage 	grayDiff;
	
	
		ofxCvContourFinder		contourFinder;
	
	int channel;
	double *quad;
		maxiFilter				myFilter;
		maxiSample				mySample;
		
		maxiMix					myAmbisonic;
	
		maxiOsc					myOsc1,myOsc2,myOsc3;
	
		maxiDyn					myComp;
		maxiOsc					myOsc;						// new
		maxiDelayline			myDelay;
};

