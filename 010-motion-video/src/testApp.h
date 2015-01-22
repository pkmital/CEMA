#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();	
		 
		float					sum;
		ofVideoGrabber			vidGrabber;
	
		ofxCvColorImage			colorImg;
		ofxCvColorImage			colorDiffImg;

		ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayPreviousImage;
		ofxCvGrayscaleImage 	grayDiff;

		ofVideoPlayer			vidPlayer;
	
		vector<ofxCvGrayscaleImage> previousImages;
};

