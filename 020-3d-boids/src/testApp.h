#pragma once

#include "ofMain.h"
#include "ofVectorMath.h"
#include <vector>
#include "boid.h"

class testApp : public ofBaseApp {
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
	
    
    ofLight light1;

	ofEasyCam cam; // add mouse controls for camera movement
	vector<Boid *>		boids;
};
