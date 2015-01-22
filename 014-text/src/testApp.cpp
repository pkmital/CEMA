#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	// set the size of the window
	ofSetWindowShape(400, 400);
	
	// load in a true type font for drawing text
	myFont_frabk_16.loadFont("frabk.ttf", 16);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	
	// let's blend our words using alpha transparency
	ofEnableAlphaBlending();
	
	// we'll set it to a low alpha since there are so many words
	ofSetColor(0, 0, 0, 40);
	
	// keep all drawing commands within this one transformation matrix
	ofPushMatrix();
	
		// translate our drawing near to the center of the screen
		ofTranslate(180, 190, 0);

		// create an "ifstream" object which lets us read from files
		ifstream myReadFile;
	
		// this will store the data coming from the text file directly
		char output[100];
		
		// this is a more convenient string container that openFrameworks often uses
		string myString;
	
		// we'll open the text file located in the data path
		// we use this function, "ofToDataPath(...)" in order to 
		// prepend "milton.txt" with the location of the data folder
		myReadFile.open(ofToDataPath("milton.txt").c_str());
	
		// if we were able to open "milton.txt"
		if (myReadFile.is_open()) 
		{
			// while there is still text to read, while we have not reached the EOF (end of file)
			while (!myReadFile.eof()) 
			{
				// input until it reaches a whitespace (a space)
				myReadFile >> output;
				// convert to string
				myString = output;
				
				// keep a transformation just for the current word
				ofPushMatrix();
					// translate the word to a random x,y,z
					ofTranslate(ofRandom(200) - 100, ofRandom(200) - 100, ofRandom(200) - 100);
					// draw at the (transformed) origin
					myFont_frabk_16.drawString(myString, 0, 0);
				
				// done with this word's transformation
				ofPopMatrix();
				
			}
		}
	
	// done with our current transformation matrix
	ofPopMatrix();
	
	// done with blending
	ofDisableAlphaBlending();
}
