#pragma once

#include "ofMain.h"
#define NUM_VOICES 25

class osxVoiceOverApp : public ofBaseApp{

	public:
	
	//--------------------------------------------------------------
	/*
	 * Call Text to Speech
	 * @param {string} wordstoSpeak - Sentence  
	 * @param {string} voice - The voice to use
	 */
	void sayTextToSpeech(string wordstoSpeak, string voice);
	
	//--------------------------------------------------------------
	/*
	 * Write Text to Speech to an .aiff
	 * @param {string} wordstoSpeak - Sentence  
	 * @param {string} voice - The voice to use
	 */
	void writeTextToSpeech(string wordstoSpeak, string voice);
	
	//--------------------------------------------------------------
	/*
	 * Load message from a text file
	 * @param {string} file - The Text file  
	 * @param {string} voice - The voice to use
	 */
	void loadFromTextFile(string file, string voice);
	
	//--------------------------------------------------------------
	/*
	 * Change the voice
	 */
	void changeVoice();
	
	//--------------------------------------------------------------
	/*
	 * Get the Application Path Directory
	 * @return {string} pathDirectory
	 */
	string getAppPathDirectory();

	//--------------------------------------------------------------
	/*
	 * Default OF functions
	 *
	 */
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	//--------------------------------------------------------------
	int windowWidth;
	int windowHeight;
	int windowCenterX;
	int windowCenterY;

	string _pathDirectory;
	string _path;
	string _file;
	
	static string voiceArray[NUM_VOICES];
	vector<map<int, string> > controlsVector;
	
	ofImage universalAccessIcon;
	ofTrueTypeFont myraidFont;
	ofTrueTypeFont font;
	string _textFile;
	std::string _speak;
	string _defaultMessage;
	string _wordstoSpeak;
	string _voice;
	int voiceIncrementer;
	string currentControl;

};

// Voice constants
const string VOICE_BRUCE = "Bruce";
const string VOICE_FRED = "Fred";
const string VOICE_JUNIOR = "Junior";
const string VOICE_RALPH = "Ralph";
const string VOICE_ALEX = "Alex";

const string VOICE_AGNES = "Agnes";
const string VOICE_VICKI = "Vicki";
const string VOICE_VICTORIA = "Victoria";
const string VOICE_PRINCESS = "Princess";
const string VOICE_KATHY = "Kathy";

const string VOICE_HYSTERICAL = "Hysterical";
const string VOICE_CELLOS = "Cellos";
const string VOICE_TRINOIDS = "Trinoids";
const string VOICE_BOING = "Boing";
const string VOICE_DERANGED = "Deranged";
const string VOICE_WHISPER = "Whisper";
const string VOICE_ZARVOX = "Zarvox";
const string VOICE_GOOD_NEWS = "Good News";
const string VOICE_ALBERT = "Albert";
const string VOICE_BELLS = "Bells";
const string VOICE_BAHH = "Bahh";
const string VOICE_PIPE_ORGAN = "Pipe Organ";
const string VOICE_BUBBLES = "Bubbles";
const string VOICE_BAD_NEWS = "Bad News";
const string VOICE_LEKHA = "Lekha";