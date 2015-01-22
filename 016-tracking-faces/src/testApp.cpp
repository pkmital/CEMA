#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetWindowShape(320, 240);
	
	video1.loadMovie("beatit.mov");
	img.allocate(video1.getWidth(), video1.getHeight(), OF_IMAGE_COLOR);
	img_scaled.allocate(320, 240, OF_IMAGE_COLOR);
	video1.play();
	
	finder.setup("haarcascade_frontalface_default.xml");
}

//--------------------------------------------------------------
void testApp::update(){
	video1.update();
	
	img.setFromPixels(video1.getPixels(), video1.getWidth(), video1.getHeight(), OF_IMAGE_COLOR);
	img_scaled = img;
	img_scaled.resize(320, 240);
	finder.findHaarObjects(img_scaled);
	
}

//--------------------------------------------------------------
void testApp::draw(){
	img_scaled.draw(0, 0);
	ofNoFill();
	for(int i = 0; i < finder.blobs.size(); i++) {
		ofRectangle cur = finder.blobs[i].boundingRect;
		ofRect(cur.x, cur.y, cur.width, cur.height);
	}
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