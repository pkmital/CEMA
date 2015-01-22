/*
 *  pkmBlobTracker.h
 *  Created by Parag K. Mital - http://pkmital.com 
 *  Contact: parag@pkmital.com
 *
 
 Copyright (C) 2011 Parag K. Mital
 
 The Software is and remains the property of Parag K Mital
 ("pkmital") The Licensee will ensure that the Copyright Notice set
 out above appears prominently wherever the Software is used.
 
 The Software is distributed under this Licence: 
 
 - on a non-exclusive basis, 
 
 - solely for non-commercial use in the hope that it will be useful, 
 
 - "AS-IS" and in order for the benefit of its educational and research
 purposes, pkmital makes clear that no condition is made or to be
 implied, nor is any representation or warranty given or to be
 implied, as to (i) the quality, accuracy or reliability of the
 Software; (ii) the suitability of the Software for any particular
 use or for use under any specific conditions; and (iii) whether use
 of the Software will infringe third-party rights.
 
 pkmital disclaims: 
 
 - all responsibility for the use which is made of the Software; and
 
 - any liability for the outcomes arising from using the Software.
 
 The Licensee may make public, results or data obtained from, dependent
 on or arising out of the use of the Software provided that any such
 publication includes a prominent statement identifying the Software as
 the source of the results or the data, including the Copyright Notice
 and stating that the Software has been made available for use by the
 Licensee under licence from pkmital and the Licensee provides a copy of
 any such publication to pkmital.
 
 The Licensee agrees to indemnify pkmital and hold them
 harmless from and against any and all claims, damages and liabilities
 asserted by third parties (including claims for negligence) which
 arise directly or indirectly from the use of the Software or any
 derivative of it or the sale of any products based on the
 Software. The Licensee undertakes to make no liability claim against
 any employee, student, agent or appointee of pkmital, in connection 
 with this Licence or the Software.
 
 
 No part of the Software may be reproduced, modified, transmitted or
 transferred in any form or by any means, electronic or mechanical,
 without the express permission of pkmital. pkmital's permission is not
 required if the said reproduction, modification, transmission or
 transference is done without financial return, the conditions of this
 Licence are imposed upon the receiver of the product, and all original
 and amended source code is included in any transmitted product. You
 may be held legally responsible for any copyright infringement that is
 caused or encouraged by your failure to abide by these terms and
 conditions.
 
 You are not permitted under this Licence to use this Software
 commercially. Use for which any financial return is received shall be
 defined as commercial use, and includes (1) integration of all or part
 of the source code or the Software into a product for sale or license
 by or on behalf of Licensee to third parties or (2) use of the
 Software or any derivative of it for research with the final aim of
 developing software products for sale or license to a third party or
 (3) use of the Software or any derivative of it for research with the
 final aim of developing non-software products for sale or license to a
 third party, or (4) use of the Software to provide any service to an
 external organisation for which payment is received. If you are
 interested in using the Software commercially, please contact pkmital to
 negotiate a licence. Contact details are: parag@pkmital.com
 
 
*/


#pragma once


#include "ofxOpenCv.h"

#include "pkmPixelBackgroundGMM.h"
#include "ofCvBlobTracker.h"
#include "ofMain.h"

class pkmBlobTracker : public ofCvBlobListener
{
public:
	pkmBlobTracker(int width = 320, int height = 240)
	{
		W = width;
		H = height;
		
		center_x = center_y = width = height = 0;
		orientation = 0;
		initOrientation = 0;
		bInit = false;
		
		initializeLKFlow(W, H);
		
		colorImg.allocate(W,H);
		grayImage.allocate(W,H);
		warpedImage.allocate(W,H);
		
		// Background model variables
		grayBg.allocate(W,H);
		grayDiff.allocate(W,H);
		
		pGMM=cvCreatePixelBackgroundGMM(W,H);
		pGMMTiming = 2000.0;
		pGMM->fAlphaT = 1. / pGMMTiming;
		pGMM->fTb = 5*4;
		pGMM->fSigma = 30;
		pGMM->bShadowDetection = true;
		bLearnBackground = true;
		threshold = 150;
		block_size = 9;
		
		low_threshold = 16;	frame_num = 0;
		
		bLearnBackground = true;
		option1 = true;	// learn a background once
		
		inImage = new unsigned char[W*H*3];
		outImage = new unsigned char[W*H*3];
		
		blobTracker.setListener( this );
		listener = NULL;
		orientation = 0.0f;
		
		bBlob = false;
	}
	
	~pkmBlobTracker()
	{
		cvReleaseImage(&cvPrevGrayImage);
		cvReleaseImage(&cvGrayImage);
		//cvReleaseImage(prevGrayImagePyr);
		//cvReleaseImage(grayImagePyr);
	}
	
	void setListener(ofCvBlobListener* _listener)
	{
		listener = _listener;
//		blobTracker.setListener(_listener);
	}
	
	void initializeLKFlow(int width, int height)
	{
		cvPrevGrayImage = cvCreateImage(cvSize(width, height), 8, 1);
		cvGrayImage = cvCreateImage(cvSize(width, height), 8, 1);
		
		cvZero(cvPrevGrayImage);
		cvZero(cvGrayImage);
		
		//prevGrayImagePyr = cvCreateImage(cvSize(width, height), 8, 1);
		//grayImagePyr = cvCreateImage(cvSize(width, height), 8, 1);
		
		gridSize = 4;													// Size of the grid for feature points A
		levels = 2;														// Number of levels in the pyramid
		winSize = cvSize(2,2);											// Size of the search window
		int type = CV_TERMCRIT_ITER|CV_TERMCRIT_EPS;
		eps = 0.01;
		iter = 10;
		crit = cvTermCriteria(type,iter,eps);
		internal_flags = 0;
	}
	
	void updateImage(const IplImage *img)
	{
		swap(cvPrevGrayImage, cvGrayImage);
		
		cvCopyImage(img, cvGrayImage);
	}
	
	void update(unsigned char *pixels, int w, int h)
	{
		//inImage = pixels;
		colorImg.setFromPixels(pixels, w, h);
		grayImage = colorImg;
		updateImage(grayImage.getCvImage());
		
		if (bLearnBackground){
			cvUpdatePixelBackgroundGMM(pGMM, colorImg.getPixels(), outImage);
			grayDiff.setFromPixels(outImage, w, h);
		}
		else {
			cvPixelBackgroundGMMSubtraction(pGMM, colorImg.getPixels(), outImage);
			grayDiff.setFromPixels(outImage, w, h);
			
		}
		
		grayBg = grayDiff;
		
		// subtraction and threshold
		grayDiff.blur( block_size );
		grayDiff.threshold( threshold );
		
		// blob tracking
		contourFinder.findContours(grayDiff, 150, w*h/3, 4, false);
		blobTracker.trackBlobs( contourFinder.blobs );
	}
	
	void draw(int x, int y)
	{
		ofEnableAlphaBlending();
		ofEnableBlendMode(OF_BLENDMODE_SCREEN);
		ofSetColor(255, 255, 255,100);
		colorImg.draw(0,0);
		ofSetColor(0,255,131,100);
		grayBg.draw(0, 0);
		ofDisableAlphaBlending();
		
		/*
		ofSetColor(255, 255, 255);
		colorImg.draw(20,20);
		
		grayDiff.draw(20+W+20+W+20,20);	
		
		// debug text output
		ofSetColor(0,255,131);
		char buf[256];
		if (bLearnBackground) {
			sprintf(buf, "learning background...\n['+'] or ['-'] to change threshold: %d\n", threshold);
		}
		else {
			sprintf(buf, "['space'] to learn background\n['+'] or ['-'] to change threshold: %d\n", threshold);
		}
		ofDrawBitmapString( buf, 20,290 );
		
		grayBg.draw(20+W+20, 20);
		ofSetColor(0,255,131);
		sprintf(buf, "['9'] or ['0'] to change gmm timing: %f\n['['] or [']'] to change block size: %d", pGMMTiming, block_size);
		ofDrawBitmapString( buf, 20,316 );
		
		
		// blob drawing
		blobTracker.draw(20+W+20+W+20, 20);
		
		if (bBlob) {
			ofSetColor(200, 20, 20);
			ofNoFill();
			ofPushMatrix();
			ofCircle(x + center_x, y + center_y, height/2.0f);
			ofTranslate(x+center_x, y+center_y, 0);
			ofRotate(orientation * 180.0f / PI, 0, 0, 1);
			ofLine(0, 0, height/2.0f, 0);
			ofPopMatrix();
		}
		*/
	}
	
	void reInit()
	{
		bInit = false;
	}
	
	float getOrientation(ofCvTrackedBlob &blob);
	
	
	//--------------------------------------------------
	void blobOn( int x, int y, int id, int order ) {
		
		//printf("blobOn() - id:%d\n", id);
		blobLocations[id] = trackedBlobs.size();
		trackedBlobs.push_back(blobTracker.getById(id));
		
		bBlob = true; 
		
		if (listener != NULL) {
			listener->blobOn(x, y, id, order);
		}
	}
	
	void blobMoved( int x, int y, int id, int order) {
		//printf("blobMoved() - id:%d\n", id);
		
		// full access to blob object ( get a reference)
		ofCvTrackedBlob blob = blobTracker.getById( id );
		
		orientation = getOrientation(blob) * 180.0f / PI;
		trackedBlobs[blobLocations[id]].orientation =  orientation;
		
		//printf("ori: %f\n", orientation);
		/*
		ofxOscMessage m;
		m.setAddress("/listener/position");
		blob_x = (x / (float)W - 0.5) * 5.0f;
		blob_y = (y / (float)H - 0.5) * 5.0f;
		printf("%f, %f\n", blob_x, blob_y);
		m.addFloatArg(blob_x);
		m.addFloatArg(blob_y);
		m.addFloatArg(1.0f);
		sender.sendMessage(m);
		*/
		bBlob = true;
		
		if (listener != NULL) {
			listener->blobMoved(x, y, id, order);
		}
	}
	
	void blobOff( int x, int y, int id, int order ) 
	{
		bBlob = false; 
		int sub = blobLocations[id];
		blobLocations.erase(id);
		trackedBlobs.erase(trackedBlobs.begin() + sub);
		map<int,int>::iterator it = blobLocations.begin();
		while (it != blobLocations.end()) {
			if (it->second > sub) {
				assert(it->second > 0);
				it->second--;
			}
			it++;
		}
		//printf("blobOff() - id:%d\n", id);
		
		
		if (listener != NULL) {
			listener->blobOff(x, y, id, order);
		}
	}
	
	void keyPressed(int key) {
	
		switch (key) {
			case ' ':
				bLearnBackground = !bLearnBackground;
				break;
			case '=': case '+':
				threshold ++;
				if (threshold > 255) threshold = 255;
				break;
			case '-':
				threshold --;
				if (threshold < 0) threshold = 0;
				break;
			case '9':
				pGMMTiming -= 1.0;
				pGMMTiming = MAX(5,pGMMTiming);
				pGMM->fAlphaT = 1. / pGMMTiming;
				break;
			case '0':
				pGMMTiming += 1.0;
				pGMMTiming = MIN(320.0,pGMMTiming);
				pGMM->fAlphaT = 1. / pGMMTiming;
				break;
			case '[':
				block_size = MAX(5,block_size-=2);
				break;
			case ']':
				block_size = MIN(53,block_size+=2);
				break;
		}
	}
	
	
	IplImage				*cvPrevGrayImage, *cvGrayImage, 
							*prevGrayImagePyr, *grayImagePyr;
	CvTermCriteria			crit;
	int						levels;
	int						gridSize;
	int						type;
	double					eps;
	int						iter;
	int						internal_flags;
	CvSize					winSize;
	
	float					orientation, initOrientation;
	float					center_x, center_y, width, height;
	bool					bInit;
	
	// ----------------------------------------------------------
	
	map<int,int>			blobLocations;
	vector<ofCvTrackedBlob>	trackedBlobs;
	
	ofCvBlobListener		*listener;
	
	ofxCvColorImage			colorImg;
	ofxCvGrayscaleImage 	grayImage;
	ofxCvGrayscaleImage 	warpedImage;
	
	
	ofxCvGrayscaleImage		grayBg;
	ofxCvGrayscaleImage		grayDiff;
	CvPixelBackgroundGMM	*pGMM;
	int						threshold;
	int						low_threshold, high_threshold, block_size;
	double					pGMMTiming;
	unsigned long			frame_num;
	bool					option1;
	
	ofCvContourFinder		contourFinder;		
	ofCvBlobTracker			blobTracker;	
	float					blob_x, blob_y;
	
	bool					bLearnBackground;
	unsigned char			*inImage;
	unsigned char			*outImage;
	
	int W,H;
	
	 
	bool bBlob;
	
};