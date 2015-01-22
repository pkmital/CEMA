#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup()
{	
#ifndef USE_CAMERA
	vidPlayer.loadMovie("test.mov");
	vidPlayer.setLoopState(OF_LOOP_NORMAL);
	vidPlayer.play();
#else
	vidGrabber.initGrabber(W,H);
#endif
	
	ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
	ofSetFrameRate(120);
	ofSetBackgroundAuto(true);
	ofBackground(0,0,0);
	
	orientationTracker.setListener(this);
	
	// move to next file in directory
	// fade in and fade out
	
	vector<string> directories;
	directories.push_back("1");
	directories.push_back("2");
	directories.push_back("3");
	directories.push_back("4");
	directories.push_back("5");
	directories.push_back("6");
	directories.push_back("7");
	directories.push_back("8");
	
	int offset = 0;
	for (int i = 0; i < directories.size(); i++) {
		// load the samples in each directory
		ofDirectory dir;
		int numFiles = dir.listDir(ofToDataPath(directories[i]));
		printf("found %d files in directory %s\n", numFiles, directories[i].c_str());
		for (int j = 0; j < numFiles; j++) {
			maxiSample *sample = new maxiSample();
			string file = dir.getFile(j).getAbsolutePath();
			printf("loading %s\n", file.c_str());
			sample->load(file);
			soundFiles.push_back(sample);
		}
		
		// load the music files
		
		maxiSample *music = new maxiSample();
		char buf[256];
		sprintf(buf, "%d.wav", i+1);
		music->load(ofToDataPath(buf));
		musicFiles.push_back(music);
		
		// keep the offsets
		narrativeOffsets.push_back(offset);
		offset += dir.numFiles();
		narrativeSizes.push_back(dir.numFiles());
		narratives.push_back(i);
		printf("narrative %d loaded with %d sound files\n", i+1, narrativeSizes[i]);
	}
	
	printf("[OK] loaded %d narratives and a total of %d sound files\n", narratives.size(), soundFiles.size());
	
	myMusic.loadSound(ofToDataPath("music.wav"), true);
	myMusic.setLoop(true);
	bMusicPlaying = false;
	
	myAmbisonic.resize(maxNarratives);
	numNarrativesAssigned = 0;
	channel = 0;
	quad = new double[4];
	// center 0
	// sub 1
	// FR - FL 2,3
	// SR - SL 4,5
	
	// setup the sound
	sampleRate = 48000;
	limiter.Setup(5, 500, sampleRate);
	bufferSize = 1024;
	output = new float[bufferSize*numchannels];
	
	fade_in_buffer = new float[bufferSize];
	fade_out_buffer = new float[bufferSize];
	memset(fade_in_buffer, 1, sizeof(float)*bufferSize);
	memset(fade_out_buffer, 1, sizeof(float)*bufferSize);
	int fadeLength = 1024;
	for (int i = 0; i < bufferSize; i++) {
		float fade = MIN(1,sqrtf((float)i /  (float)fadeLength));

		fade_in_buffer[i] = fade;
		fade_out_buffer[bufferSize - i - 1] = fade;
	}
	
	
	ofSoundStreamSetup(numchannels,		// output channels
					   1,				// input channels
					   sampleRate,		// how many samples (readings) per second
					   bufferSize,		// size of each copy of audio
					   4);				// latency of audio
	
}
//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(0,0,0);
#ifndef USE_CAMERA
	vidPlayer.update();
	if (vidPlayer.isFrameNew()) {
		orientationTracker.update(vidPlayer.getPixels(), W, H);
	}
#else
	vidGrabber.update();
	if (vidGrabber.isFrameNew()) {
		orientationTracker.update(vidGrabber.getPixels(), W, H);

	}
#endif
	////printf("sounds playing: %d\n", currentPlayingSounds.size());
		
	if (currentPlayingSounds.size() > 0) 
	{
		if (!bMusicPlaying) {
			bMusicPlaying = true;
			myMusic.play();
		}
	}
	else {
		bMusicPlaying = false;
		myMusic.stop();
	}

}
	
//--------------------------------------------------------------
void testApp::draw(){
	orientationTracker.draw(0, 0);
	/*
	float width_step = (float)ofGetWindowWidth() / (float)bufferSize;
	float amplitude = 80.0f;
	for (int j = 0; j < numchannels; j++) {
		for (int i = 1; i < bufferSize; i++) 
		{
			ofLine((i-1) * width_step, output[numchannels*(i-1) + j] * amplitude + j*60 + 60, 
				   i * width_step, output[numchannels*(i) + j] * amplitude + j*60 + 60);
		}
	}
	*/
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	switch (key){
#ifdef USE_CAMERA
		case 's':
			vidGrabber.videoSettings();
			break;
#endif
		case 'f':
			ofToggleFullscreen();
			break;
		default:
			orientationTracker.keyPressed(key);
			break;
	}
	
}

void testApp::audioRequested(float *buf, int size, int ch)
{
	memset(buf, 0, sizeof(float)*numchannels*size);
	
	if (currentPlayingSounds.size() > 0) 
	{
		vector<player>::iterator iter = currentPlayingSounds.begin();
		while (iter != currentPlayingSounds.end())
		{
			for (int i = 0; i < size; i++) 
			{
				int narrativeNumber = narrativeMapping[iter->blobId];
				float musicSample = musicFiles[ narrativeNumber ]->play();
				
				float sample = soundFiles[ iter->idx ]->play( currentSoundSpeeds[iter->myId] );
				if (soundFiles[ iter->idx ]->bFinished) {
					soundFiles[ iter->idx ]->bFinished = false;
					
					printf("%d: finished %d ", iter->blobId, iter->idx);
					
					if(iter->idx + 1 >= narrativeOffsets[narrativeNumber] +							// get the index in the vector of all sounds of the ones defining this narrative
										narrativeSizes[narrativeMapping[iter->blobId]] )			// and pick the next one from the list of all narratives
						iter->idx = narrativeOffsets[narrativeNumber];
					else {
						iter->idx++;
					}

					printf("assigning to %d\n", iter->idx);
				}
				
				
				// mix with character music
				sample = 0.717*sample + 0.717*musicSample;
				/*
				if (iter->state == fade_in) {
					sample *= fade_in_buffer[i];

				}
				else if(iter->state == no_fade) {
					//sample = soundFiles[ iter->idx ]->play( currentSoundSpeeds[iter->myId] ) * 1.0;
				}
				else if(iter->state == fade_out) {
					sample *= fade_out_buffer[i];
				}
				*/
				limiter.Process<float, 1>(1, &sample);
				
				quad = myAmbisonic[iter->myId].quad(sample, 
										quad, 
										currentSoundPositions[iter->myId].x/cameraWidth , 
										currentSoundPositions[iter->myId].y/cameraHeight );
				buf[i*numchannels + 0] += sample / 1.0;
				buf[i*numchannels + 2] += quad[0];
				buf[i*numchannels + 3] += quad[1];
				buf[i*numchannels + 4] += quad[2];
				buf[i*numchannels + 5] += quad[3];
			}
			if (iter->state == fade_in) {
				iter->state = no_fade;
			}
			
			if (iter->state == fade_out) {
				printf("%d: erasing sound %d\n", iter->blobId, iter->idx);
				currentSoundSpeeds.erase(currentSoundSpeeds.begin() + iter->myId);
				currentSoundPositions.erase(currentSoundPositions.begin() + iter->myId);
				previousSoundPositions.erase(previousSoundPositions.begin() + iter->myId);
				
				map<int, int>::iterator iter2 = soundMapping.begin();
				while (iter2 != soundMapping.end()) {
					if (iter2->second > iter->myId) {
						iter2->second--;
					}
					iter2++;
				}
				
				vector<player>::iterator iter3 = currentPlayingSounds.begin();
				while (iter3 != currentPlayingSounds.end()) {
					if (iter3->myId > iter->myId) {
						iter3->myId--;
					}
					iter3++;
				}
				
				iter = currentPlayingSounds.erase(iter);
			}
			else {
				iter++;
			}
		}
		/*
		for (int i = 0; i < size; i++) 
		{
			// mix with ambient music
			float ratio = 1.0 / sqrtf(currentPlayingSounds.size());
			buf[i*numchannels + 0] = ratio*buf[i*numchannels + 0];
			buf[i*numchannels + 2] = ratio*buf[i*numchannels + 2];
			buf[i*numchannels + 3] = ratio*buf[i*numchannels + 3];
			buf[i*numchannels + 4] = ratio*buf[i*numchannels + 4];
			buf[i*numchannels + 5] = ratio*buf[i*numchannels + 5];
		}
		*/
		
	}

	
	memcpy(output, buf, sizeof(float)*numchannels*size);
}

void testApp::blobOn( int x, int y, int id, int order )
{
	
	//printf("blob on\n");
	
	// choose a narrative

	if (numNarrativesAssigned >= maxNarratives) {
		soundMapping[id] = -1;
		return;
	}
	int narrative_idx = random() % narratives.size();			// pick a random narrative
	narrativeMapping[id] = narratives[narrative_idx];			// assign this blob to the random narrative
	narratives.erase(narratives.begin() + narrative_idx);		// remove the assigned narrative from the list of possible narratives
	
	// get the starting sound
	maxiSample *sound;
	int currentSoundIdx = narrativeOffsets[ narrativeMapping[id] ] +			// get the index in the vector of all sounds of the ones defining this narrative
							random() % narrativeSizes[ narrativeMapping[id] ];	// and randomly pick one from the list of all narratives

	soundMapping[id] = currentPlayingSounds.size();		// sound mapping for this blob to the vector index in currentPlayingSounds
	player p;											// player object holds the 
	p.idx = currentSoundIdx;							// sound index in the list of all sounds
	p.myId = soundMapping[id];							// the vector index in the list of blob assignments
	p.state = fade_in;									// the state for the sound
	p.blobId = id;
	currentPlayingSounds.push_back(p);
	printf("%d: ON\n", id);
	
	printf("%d: assigning to narrative %d and sound %d\n", id, narrativeMapping[id], currentSoundIdx);
	
	currentSoundSpeeds.push_back(1.0);
	currentSoundPositions.push_back(ofPoint(x,y));
	previousSoundPositions.push_back(ofPoint(x,y));
	numNarrativesAssigned++;
}

void testApp::blobMoved( int x, int y, int id, int order )
{
	if (soundMapping[id] == -1) {
		return;
	}
	//printf("blob moved\n");	
	//currentPlayingSounds[soundMapping[id]].state = no_fade;
	ofPoint previous = previousSoundPositions[soundMapping[id]];
	
	float speed = abs( sqrtf( (x - previous.x)*(x - previous.x) + (y - previous.y)*(y - previous.y) ) ) * 0.8;
	
	previousSoundPositions[soundMapping[id]] = ofPoint(x,y);
	currentSoundSpeeds[soundMapping[id]] = 0.9 * currentSoundSpeeds[soundMapping[id]] + 0.1 * speed;	
	currentSoundPositions[soundMapping[id]] = ofPoint(x,y);
	
	//printf("%f\n", currentSoundSpeeds[soundMapping[id]]);
}

void testApp::blobOff( int x, int y, int id, int order )
{
	if (soundMapping[id] == -1) {
		return;
	}
	printf("%d: OFF\n", id);
	currentPlayingSounds[soundMapping[id]].state = fade_out;
	
	//printf("blob off\n");
	narratives.push_back(narrativeMapping[id]);
	printf("adding narrative %d\n", narrativeMapping[id]);
	//currentPlayingSounds.erase(currentPlayingSounds.begin() + soundMapping[id]);
	//currentSoundSpeeds.erase(currentSoundSpeeds.begin() + soundMapping[id]);
	//currentSoundPositions.erase(currentSoundPositions.begin() + soundMapping[id]);
	//previousSoundPositions.erase(previousSoundPositions.begin() + soundMapping[id]);

	numNarrativesAssigned--;
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


