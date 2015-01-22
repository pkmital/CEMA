#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetWindowPosition(20, 20);
	ofSetWindowShape(640, 480);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	ofBackground(0,50,50);	
	
	// set up the boids
	for (int i = 0; i < 50; i++)
		boids.push_back(new Boid());
	
	// this uses depth information for occlusion
	// rather than always drawing things on top of each other
	glEnable(GL_DEPTH_TEST);
	
	ofEnableLighting();
	ofSetSmoothLighting(true);
	light1.setSpotlight();
	
	// this sets the camera's distance from the object
	cam.setDistance(500);
	
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
	glEnable(GL_DEPTH_TEST);
	
	//////////////////////
	// DRAW WIREFRAME BOX
	//
	// xy plane at z=-1 in camera sapce
	// (small rectangle at camera position)
	//
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);
	glEnd();
	
	
	// xy plane at z=1 in camera space
	// (generally invisible because so far away)
	//
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);
	glEnd();
	
	// connecting lines between above 2 planes
	// (these are the long lines)
	//
	glBegin(GL_LINES);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 1);
	
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 1);
	
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glEnd();
	
	
	light1.enable();
	
	cam.begin();	
	
		for (int i = 0; i < boids.size(); i++)
		{
			//boids[i]->draw();
			ofSphere(boids[i]->getPosition().x, boids[i]->getPosition().y, boids[i]->getPosition().y - 200, 5);
		}
	
	cam.end();

	light1.disable();
	light1.draw();
	
	
	ofSetColor(255);
	string msg = string("Using mouse inputs to navigate ('m' to toggle): ") + (cam.getMouseInputEnabled() ? "YES" : "NO");
	msg += "\nfps: " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(msg, 10, 20);
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch(key) {
		case 'M':
		case 'm':
			if(cam.getMouseInputEnabled()) cam.disableMouseInput();
			else cam.enableMouseInput();
			break;
			
		case 'F':
		case 'f':
			ofToggleFullscreen();
			break;
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

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
