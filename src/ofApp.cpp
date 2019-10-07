#include "ofApp.h"
#include <cstdlib>

// variables
ofImage image;
int w = 512;
int h = 512;



//--------------------------------------------------------------
void ofApp::setup(){
}

//--------------------------------------------------------------
void ofApp::update(){

	// array of pixels to be filled in our image
	// An image total pixel count = width * height
	// we multiply * 4 because we want to use the for channels OF_IMAGE_COLOR_ALPHA
	unsigned char *data = new unsigned char[w * h * 4];

	// loop through and fill array
	for (int y = 0; y < h; y++)			// vertical loop
	{
		for (int x = 0; x < w; x++)		// horizontal loop
		{
			// set any value for each channel 
			int red = rand() % 256;		// red is in the range 0 to 255;
			int green = rand() % 256;
			int blue = rand() % 256;
			int alpha = 255;

			// add every color to their position in array [r, g, b, a]
			int index = 4 * (x + w * y);		// Static
			data[index] = red;
			data[index + 1] = green;
			data[index + 2] = blue;
			data[index + 3] = alpha;
		}
	}

	// load array into image
	image.setFromPixels(data, w, h, OF_IMAGE_COLOR_ALPHA);

	// delete array to free memory
	delete[] data;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(255, 255, 255);

	ofSetColor(255, 255, 255);		// display image with color

	image.draw(0, 0);		// draw image in canvas at position 0, 0
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
