#include "testApp.h"

testApp::~testApp()
{
	for (int i = 0; i < boids.size(); i++)
	{
		delete boids[i];
	}
}

//--------------------------------------------------------------
void testApp::setup(){	 
	
	ofSetWindowPosition(20, 20);
	ofSetWindowShape(640, 480);
	ofSetFrameRate(60);
	
	ofBackground(0,50,50);	
	
	// set up the boids
	for (int i = 0; i < 50; i++)
		boids.push_back(new Boid());
	
}


//--------------------------------------------------------------
void testApp::update(){
	
	ofVec3f min_pos(0, 0);
	ofVec3f max_pos(ofGetWidth(), ofGetHeight());
	for (int i = 0; i < boids.size(); i++)
	{
		boids[i]->update(boids, min_pos, max_pos);	
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetupScreen();
	
	for (int i = 0; i < boids.size(); i++)
	{
		boids[i]->draw();
	}

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){ 

	if(key == 'f'){
	
		ofToggleFullscreen();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
