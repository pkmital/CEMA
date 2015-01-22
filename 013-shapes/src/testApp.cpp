#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetWindowShape(400, 400);
	ofSetWindowPosition(1500, 20);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

	ofBackground(200, 100, 100);
	ofSetRectMode(OF_RECTMODE_CENTER); // OF_RECTMODE_CORNER
	
	ofPushMatrix();
	
	ofScale(mouseX / (float)ofGetWindowWidth() * 4.0, 
			mouseY / (float)ofGetWindowHeight() * 4.0, 
			1);
	
	// head
	ofRect(200,	50, 50, 50);
	// body
	ofRect(200, 150, 20, 80);
	
	
	ofSetRectMode(OF_RECTMODE_CORNER); 
	float degress = ofMap(mouseY, 0, ofGetWindowHeight(), 
						  45, 135, true);
	
	// left leg
	ofPushMatrix();
		ofTranslate(175, 225, 0);
		ofRotate(degress, 0, 0, 1);
		ofRect(0, 0, 15, 80);
	ofPopMatrix();
	
	// right leg
	ofPushMatrix();
		ofTranslate(220, 230, 0);
		ofRotate(-degress, 0, 0, 1);
		ofRect(0, 0, 15, 80);
	ofPopMatrix();
	
	// left arm
	ofPushMatrix();
		ofTranslate(175, 100, 0);
		ofRotate(degress, 0, 0, 1);
		ofRect(0, 0, 15, 80);
	ofPopMatrix();
	/*
	// right arm
	ofPushMatrix();
		ofTranslate(250, 100, 0);
		ofRotate(45, 0, 0, 1);
		ofRect(0, 0, 15, 80);
	ofPopMatrix();
	*/
	
	ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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