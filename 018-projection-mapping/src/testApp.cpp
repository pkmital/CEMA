/*
 
 *  Created by Parag K. Mital - http://pkmital.com 
 *  Contact: parag@pkmital.com
 *
 *  Copyright 2011 Parag K. Mital. All rights reserved.
 * 
 *	Permission is hereby granted, free of charge, to any person
 *	obtaining a copy of this software and associated documentation
 *	files (the "Software"), to deal in the Software without
 *	restriction, including without limitation the rights to use,
 *	copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the
 *	Software is furnished to do so, subject to the following
 *	conditions:
 *	
 *	The above copyright notice and this permission notice shall be
 *	included in all copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,	
 *	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *	OTHER DEALINGS IN THE SOFTWARE.
 
 */

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
    // load a movie
    video1.loadMovie("head.mov");
    video1.setVolume(0);
    video1.play();
	
    // load a second movie
    video2.loadMovie("video2.mov");
    video2.setVolume(0);
    video2.play();
	 

	
	myFont_frabk_16.loadFont("frabk.ttf", 12);
	
	numMappers = 6;
    // this is how we setup our projection mapper
    // we give it our windows dimensions, and a starting x, y (0,0)
	for (int i = 0; i < numMappers; i++) {
		myMapper[i].initialize(320, 240,  i*40, i*40);
		char buf[256];
		sprintf(buf, "mapper%d.txt", i);
		myMapper[i].load(ofToDataPath(buf));
	}
	
	// fullscreen to start with
	ofSetFullscreen(true);
	
    // this changes our drawing rate to match our screen's refresh rate
    ofSetVerticalSync(true);
	
    bDrawBoxes = true;
}

//--------------------------------------------------------------
void testApp::update(){
	
    // we have to update everything
    video1.update();
    video2.update();
	for (int i = 0; i < numMappers; i++) {
		myMapper[i].update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	
    // give us a black background
    ofBackground(0);
    ofSetColor(255, 255, 255);
	
    myMapper[0].startMapping();
	video1.draw(0, 0, 320, 240);

    myMapper[0].stopMapping();
	
    myMapper[1].startMapping();
	
	ofPushMatrix();
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofTranslate(160, 120, 0);
	ofRotate(ofGetElapsedTimef()*20.0, 0, 1.0, 0);
	ofRect(0, 0, 320, 240);
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofPopMatrix();
    myMapper[1].stopMapping();
	
    myMapper[2].startMapping();
	{
		video2.draw(0, 0, 320, 240);
	}
    myMapper[2].stopMapping();
	
    myMapper[3].startMapping();
	{
		video2.draw(0, 0, 320, 240);

	}
    myMapper[3].stopMapping();
	
    myMapper[4].startMapping();
	{
		video2.draw(0, 0, 320, 240);
	}
    myMapper[4].stopMapping();
	
    myMapper[5].startMapping();
	video2.draw(0, 0, 320, 240);
    myMapper[5].stopMapping();
	/*
    myMapper[6].startMapping();
		//video1.draw(0, 0, 320, 240);
	ofPushMatrix();
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofTranslate(160, 120, 0);
	ofRotate(ofGetElapsedTimef()*20.0, 0, 1.0, 0);
	ofRect(0, 0, 320, 240);
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofPopMatrix();
    myMapper[6].stopMapping();
	
    myMapper[7].startMapping();
	ofPushMatrix();
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofTranslate(160, 120, 0);
	ofRotate(ofGetElapsedTimef()*20.0, 1.0, 0.0, 0);
	ofRect(0, 0, 320, 240);
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofPopMatrix();
    myMapper[7].stopMapping();
	*/
    // we can draw the bounding boxes around the projection mapper
    if (bDrawBoxes) {
		for (int i = 0; i < numMappers; i++) {
			myMapper[i].drawBoundingBox();
		}
    }
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
    // if the keyboard is pressed with b
    if (key == 'b') {
        // we start/stop drawing bounding boxes
        bDrawBoxes = !bDrawBoxes;
    }
	
    // we can also make our window fullscreen by pressing 'f'
    else if(key == 'f') {
        ofToggleFullscreen();
    }
	
	else if(key == 'l') {
		for (int i = 0; i < numMappers; i++) {
			char buf[256];
			sprintf(buf, "mapper%d.txt", i);
			myMapper[i].load(ofToDataPath(buf));
		}
	}
	
	else if(key == 's') {
		for (int i = 0; i < numMappers; i++) {
			char buf[256];
			sprintf(buf, "mapper%d.txt", i);
			myMapper[i].save(ofToDataPath(buf));
		}
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
	for (int i = 0; i < numMappers; i++) {
		myMapper[i].mouseDragged(x, y);
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    for (int i = 0; i < numMappers; i++) {
		myMapper[i].mousePressed(x, y);
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    for (int i = 0; i < numMappers; i++) {
		myMapper[i].mouseReleased(x, y);
	}
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