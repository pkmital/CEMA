#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetWindowShape(320, 240);
	ofSetWindowPosition(1500, 20);
	
	video1.loadMovie("pingu.mov");
	video1.setVolume(0);
	video1.play();
	video2.loadMovie("sunra_pink.mov");
	video2.setVolume(0);
	video2.play();
	video3.loadMovie("beatit.mov");
	video3.setVolume(0);
	video3.play();
	
}

//--------------------------------------------------------------
void testApp::update(){
	video1.update();
	video2.update();
	video3.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofEnableAlphaBlending();
	
	ofSetColor(255, 255, 255, 100);
	video1.draw(0, 0, 320, 240);
	
	ofSetColor(255, 255, 255, 100);
	video2.draw(0, 0, 320, 240);
	
	ofSetColor(255, 255, 255, 100);
	video3.draw(0, 0, 320, 240);
	
	ofDisableAlphaBlending();
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