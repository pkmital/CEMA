#include "osxVoiceOverApp.h"
#include <sstream>

// Available voices in OSX
string osxVoiceOverApp::voiceArray[NUM_VOICES] = {
	
	VOICE_BRUCE,
	VOICE_FRED,
	VOICE_JUNIOR,
	VOICE_RALPH,
	VOICE_ALEX,
	VOICE_AGNES,
	VOICE_VICKI,
	VOICE_VICTORIA,
	VOICE_PRINCESS,
	VOICE_KATHY,
	VOICE_HYSTERICAL,
	VOICE_CELLOS,
	VOICE_TRINOIDS,
	VOICE_BOING,
	VOICE_DERANGED,
	VOICE_WHISPER,
	VOICE_ZARVOX,
	VOICE_GOOD_NEWS,
	VOICE_ALBERT,
	VOICE_BELLS,
	VOICE_BAHH,
	VOICE_PIPE_ORGAN,
	VOICE_BUBBLES,
	VOICE_BAD_NEWS,
	VOICE_LEKHA
};

//--------------------------------------------------------------
void osxVoiceOverApp::setup(){
	
	ofSetWindowTitle("OSX Universal Access ~ VoiceOver demo");

	// Set App path directory
	_pathDirectory = getAppPathDirectory();
	
	// Load the Universal Access Logo
	universalAccessIcon.loadImage(_pathDirectory+"/data/assets/images/Universal_Access_icon.png");
	
	// Load Myraid font
	myraidFont.loadFont(_pathDirectory+"/data/assets/fonts/MyriadPro-Regular.otf", 12);
	myraidFont.setLineHeight(20.0f);
	
	// Set text file path
	_textFile = _pathDirectory+"/data/text/textMessage.txt";
	
	// Set the default speech message
	_defaultMessage = "I like the bass bass bass, the buttery biscuit base";
	
	// Set the first voice
	voiceIncrementer = 0;
	
	// Setup the Controls Vector
	map<int, string> controlsMap;
	controlsMap[0] = "Play message [P]";
	controlsMap[1] = "Write to .aiff [W]";
	controlsMap[2] = "Load from txt file [L]";
	controlsMap[3] = "Switch voice [S]";
	controlsVector.push_back(controlsMap);
	currentControl = "";

}

//--------------------------------------------------------------
void osxVoiceOverApp::update(){
	
	// Set window width & height props
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	windowCenterX = windowWidth/2;
	windowCenterY = windowHeight/2;
}

//--------------------------------------------------------------
void osxVoiceOverApp::draw(){
	
	int i;
	int l;
	
	// Draw Gradient Background
	glBegin(GL_QUAD_STRIP);  
    glColor3f(250, 250, 250);  
    glVertex3f(0, 0, 0);  
    glVertex3f(windowWidth, 0, 0);  
	
	glColor3f(243, 243, 243);  
    glVertex3f( 0, windowHeight,0);  
    glVertex3f( windowWidth, windowHeight, 0);  
	glEnd(); 
	
	// Draw Play message text
	l = controlsVector[0].size();
	for (i = 0; i < l; i++) {
		
		string controls = controlsVector[0][i];
		
		if(strcmp(controlsVector[0][i].c_str(), currentControl.c_str())==0){
			ofSetColor(97, 160, 249);
		} else {
			ofSetColor(153, 153, 153);	
		}
		
		myraidFont.drawString(controls, (i * windowWidth/4)+25, windowHeight-25);
	}
	
	// Draw voices text
	int angle = 0;
	ofPoint vPoint;
	ofPoint lPoint;
	
	for (i =0; i < NUM_VOICES; i++) {
		
		angle = i * (360/NUM_VOICES);
				
		vPoint.x = windowCenterX + cos(ofDegToRad(angle)) * 140;
		vPoint.y = windowCenterY + sin(ofDegToRad(angle)) * 140;
		
		lPoint.x = windowCenterX + cos(ofDegToRad(angle)) * 120;
		lPoint.y = windowCenterY + sin(ofDegToRad(angle)) * 120;
		
		if(i == voiceIncrementer){
			ofSetColor(97, 160, 249);
		} else {
			ofSetColor(153, 153, 153);
		}
		
		ofLine(windowCenterX, windowCenterY, lPoint.x, lPoint.y);
		ofPushMatrix();
		ofTranslate(vPoint.x,vPoint.y,0);
		ofRotateZ(angle);
		myraidFont.drawString(voiceArray[i].c_str(), 0, 0);
		ofPopMatrix();
	}
	
	// Draw the Universal Access icon
	ofSetColor(255, 255, 255);
	ofEnableAlphaBlending();
	universalAccessIcon.draw(windowCenterX-(universalAccessIcon.width/2), windowCenterY-(universalAccessIcon.height/2));
	ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void osxVoiceOverApp::sayTextToSpeech(string wordstoSpeak, string voice){
	
	_wordstoSpeak = wordstoSpeak;
	_voice = voice;

	_speak = "osascript -e 'say \" " + _wordstoSpeak + "\" using \"" + _voice + "\" '&";
		
	const char * speakChar = _speak.c_str();
	
	system(speakChar);
}
//--------------------------------------------------------------
void osxVoiceOverApp::writeTextToSpeech(string wordstoSpeak, string voice){
	
	_wordstoSpeak = wordstoSpeak;
	_voice = voice;
	
	// Write to Desktop
	_speak = "say -o ~/Desktop/text-to-speech.aiff  '" + _defaultMessage + "' -v " + _voice + "&";
	//_speak = "say -o "+_pathDirectory + "/data/assets/sound/text-to-speech.aiff  '" + _wordstoSpeak + "' -v " + _voice + "&";
	
	const char * speakChar = _speak.c_str();
	
	system(speakChar);
}

//--------------------------------------------------------------
void osxVoiceOverApp::loadFromTextFile(string file, string voice){
	
	_file = file;
	_voice = voice;
	
	_speak = "say -f " + _file + " -v " + _voice + "&";
	
	const char * speakChar = _speak.c_str();
	
	system(speakChar);
}


//--------------------------------------------------------------
void osxVoiceOverApp::changeVoice(){
	voiceIncrementer = (voiceIncrementer + 1) % NUM_VOICES;
}

//--------------------------------------------------------------
void osxVoiceOverApp::keyPressed(int key){
	
	switch (key) {
		
		case 'p':
			
			this->sayTextToSpeech(_defaultMessage, voiceArray[voiceIncrementer]);
			currentControl = controlsVector[0][0];
			
			break;
			
		case 'w':
			
			this->writeTextToSpeech(_defaultMessage, voiceArray[voiceIncrementer]);
			currentControl = controlsVector[0][1];
			
			break;
			
		case 'l':
			
			this->loadFromTextFile(_textFile, voiceArray[voiceIncrementer]);
			currentControl = controlsVector[0][2];
			
			break;
			
		case 's':
			
			this->changeVoice();
			currentControl = controlsVector[0][3];
			
			break;
	}
}

//--------------------------------------------------------------
string osxVoiceOverApp::getAppPathDirectory(){
	
	// Get the path the correct apple way - returns path to inside .app directory
	CFURLRef mainRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
	CFStringRef macPath = CFURLCopyFileSystemPath(mainRef, kCFURLPOSIXPathStyle);
	const char *pathPtr = CFStringGetCStringPtr(macPath, CFStringGetSystemEncoding());
	string pathDirectory (pathPtr);
	
	size_t found;
	found=pathDirectory.find_last_of("/\\");
	pathDirectory = pathDirectory.substr(0,found+1);
	
	return pathDirectory;
}

//--------------------------------------------------------------
void osxVoiceOverApp::keyReleased(int key){
	currentControl = "";
}

//--------------------------------------------------------------
void osxVoiceOverApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void osxVoiceOverApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void osxVoiceOverApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void osxVoiceOverApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void osxVoiceOverApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void osxVoiceOverApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void osxVoiceOverApp::dragEvent(ofDragInfo dragInfo){ 
	
}