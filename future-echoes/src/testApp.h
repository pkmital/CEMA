#pragma once

#include "ofMain.h"

#define USE_CAMERA

const int W = 320;
const int H = 240;
const float cameraWidth = W;
const float cameraHeight = H;
const int WINDOW_WIDTH = W;
const int WINDOW_HEIGHT = H;
const int numchannels = 6;
const int maxNarratives = 8;
#include "ofVideoGrabber.h"
#include "pkmBlobTracker.h"
#include "maximilian.h"
#include "limiter.h"
enum states {
	fade_in,
	fade_out,
	no_fade
};
class testApp : public ofBaseApp, public ofCvBlobListener {
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
	void audioRequested(float *buf, int size, int ch);

	void blobOn( int x, int y, int id, int order );
	void blobMoved( int x, int y, int id, int order );
	void blobOff( int x, int y, int id, int order );
	
	class player
	{
	public:
		
		int idx,	// sound index in the list of all sounds
			blobId, // the vector index in the blob tracker's assignments
			myId;	// the vector index in my list of blob assignments
		
		states state;
	};
	
	int						channel, sampleRate, bufferSize;
	double					*quad;
	float					*output, *fade_in_buffer, *fade_out_buffer;
	ofSoundPlayer			myMusic;
	maxiFilter				myFilter;
	maxiDelayline			myDelay;
	maxiMix					myMixer;
	vector<maxiMix>			myAmbisonic;
	
	Limiter					limiter;
	
#ifndef USE_CAMERA
	ofVideoPlayer			vidPlayer;
#else
	ofVideoGrabber			vidGrabber;
#endif
	pkmBlobTracker			orientationTracker;
	
	vector<float>			velocities;
	vector<int>				px;
	vector<int>				py;
	map<int, int>			narrativeMapping;
	map<int, int>			soundMapping;
	map<int, int>			velocityMapping;
	
	vector<int>				currentFadeInSounds;
	vector<int>				currentFadeOutSounds;
	vector<player>			currentPlayingSounds;
	vector<ofPoint>			currentSoundPositions;
	vector<ofPoint>			previousSoundPositions;
	vector<float>			currentSoundSpeeds;
	
	int						numNarrativesAssigned;
	
	vector<maxiSample *>	soundFiles;				// contains every folders sound files
	vector<maxiSample *>	musicFiles;				// contains every folders sound files
	vector<int>				narrativeSizes;			// size of each folder of narratives
	vector<int>				narrativeOffsets;		// offset of where the sounds begin for each narrative
	vector<int>				narratives;				// vector of ints for the possible narratives
	
	bool bMusicPlaying;
};
