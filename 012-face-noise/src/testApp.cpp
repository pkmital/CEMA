#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetWindowShape(320, 240);
	
	camera.initGrabber(320, 240);
	finder.setup("haarcascade_frontalface_default.xml");
	img.allocate(320, 240, OF_IMAGE_COLOR);
	
	// setup the sound
	int sampleRate = 44100;
	int bufferSize = 320;
	ofSoundStreamSetup(1,				// output channels
					   1,				// input channels
					   sampleRate,		// how many samples (readings) per second
					   bufferSize,		// size of each copy of audio
					   4);				// latency of audio
}

//--------------------------------------------------------------
void testApp::update(){
	camera.update();
	img.setFromPixels(camera.getPixels(), 320, 240, OF_IMAGE_COLOR);
	finder.findHaarObjects(img);
}

//--------------------------------------------------------------
void testApp::draw(){
	camera.draw(0, 0);
	ofNoFill();
	for(int i = 0; i < finder.blobs.size(); i++) {
		ofRectangle cur = finder.blobs[i].boundingRect;
		ofRect(cur.x, cur.y, cur.width, cur.height);
	}
}


void testApp::audioRequested(float *buf, int size, int ch)
{
	memset(buf, 0, sizeof(float)*size);
	for (int i = 0; i < size; i++) {
		for(int j = 0; j < finder.blobs.size(); j++) {
			buf[i] += osc1[j].sinewave(finder.blobs[j].boundingRect.x);
		}
	}
	
}
void testApp::audioReceived(float *buf, int size, int ch)
{
	
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
