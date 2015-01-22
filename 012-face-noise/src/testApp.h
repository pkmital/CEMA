#pragma once

#include "ofMain.h"
#include "ofxCvHaarFinder.h"

#include "maximilian.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

	ofVideoGrabber		camera;
	ofImage				img;
	ofxCvHaarFinder		finder;
	
	maxiOsc osc1[10];
	
	void audioRequested(float *buf, int size, int ch);
	void audioReceived(float *buf, int size, int ch);
};
