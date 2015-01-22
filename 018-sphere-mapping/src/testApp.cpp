#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
    // we'll always use a 320x240 window, but we can reshape it
    ofSetWindowShape(320, 240);
	
    // load a movie
    video1.loadMovie("pingu.mov");
    video1.setVolume(0);
    video1.play();
	
    // load a second movie
    video2.loadMovie("beatit.mov");
    video2.setVolume(0);
    video2.play();
	
    // this is how we setup our projection mapper
    // we give it our windows dimensions, and a starting x, y (0,0)
    myMapper1.initialize(320, 240,  0,  0);
    // similarly, for our second projection mapper, we give it another
    myMapper2.initialize(320, 240, 40, 40);
	
    // set our frame rate
    ofSetFrameRate(30);
	
    // this changes our drawing rate to match our screen's refresh rate
    ofSetVerticalSync(true);
	
    // needed for textures to work with gluSphere
    ofDisableArbTex(); 
	
    //prepare quadric for sphere
    quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricNormals(quadric, GLU_SMOOTH);
	
    bDrawBoxes = true;
}

//--------------------------------------------------------------
void testApp::update(){
	
    // we have to update everything
    video1.update();
    video2.update();
    myMapper1.update();
    myMapper2.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	
    // we are going to use 3D for our sphere
    glEnable(GL_DEPTH_TEST);
	
    // give us a black background
    ofBackground(0);
    ofSetColor(255, 255, 255);
	
    // this is how we start our mapping
    myMapper1.startMapping();
	
	ofTranslate(160, 120, 0);
	//rotate sphere over time
	ofRotateY(ofGetFrameNum());
	ofRotateX(-90); //north pole facing up
	
	//bind and draw texture to texture a sphere
	ofImage image1;
	image1.allocate(320, 240, OF_IMAGE_COLOR);
	image1.setFromPixels(video1.getPixels(), 320, 240, OF_IMAGE_COLOR);
	image1.resize(256, 256);
	image1.getTextureReference().bind();
	
	// draw a sphere
	gluSphere(quadric, 200, 100, 100);
	
	//      video1.draw(0, 0, 320, 240);
	
    // now we are done with the projection mapping
    myMapper1.stopMapping();
	
    // again for another projection surface, we create another mapper
    myMapper2.startMapping();
	
	// and any drawing commands inside here are remapped
	video2.draw(0, 0, 320, 240);
	
    // done remapping
    myMapper2.stopMapping();
	
    // we are done with 3D drawing now
    glDisable(GL_DEPTH_TEST);
	
    // we can draw the bounding boxes around the projection mapper
    if (bDrawBoxes) {
        myMapper1.drawBoundingBox();
        myMapper2.drawBoundingBox();
    }
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
    // we have interaction for 2 key strokes
	
    // if the keyboard is pressed with b
    if (key == 'b') {
        // we start/stop drawing bounding boxes
        bDrawBoxes = !bDrawBoxes;
    }
	
    // we can also make our window fullscreen by pressing 'f'
    else if(key == 'f') {
        ofToggleFullscreen();
		
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
    myMapper1.mouseDragged(x, y);
    myMapper2.mouseDragged(x, y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    myMapper1.mousePressed(x, y);
    myMapper2.mousePressed(x, y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    myMapper1.mouseReleased(x, y);
    myMapper2.mouseReleased(x, y);
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