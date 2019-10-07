#include "ofApp.h"

// variables
ofImage image;
ofImage imageCopy;

//--------------------------------------------------------------
void ofApp::setup(){
	image.loadImage("githubLogo.png");
	imageCopy.allocate(image.getWidth(), image.getHeight(), OF_IMAGE_COLOR_ALPHA);

	ofPixels & data = image.getPixels();

	// set component value according to image type
	// OF_IMAGE_COLOR_ALPHA = 4		OF_IMAGE_COLOR = 3		OF_IMAGE_GRAYSCALE = 1
	int component = 4;

	// modify image
	for (int y = 0; y < image.getHeight(); y++)			// vertical loop
	{
		for (int x = 0; x < image.getWidth(); x++)		// horizontal loop
		{
			// read each pixel color
			int index = component * (x + image.getWidth() * y);		// static
			// for one pixel int the array, this is his original color composition
			int red = data[index];
			int green = data[index + 1];
			int blue = data[index + 2];

			// you can edit the colors here to have different effect
			// in this case we will invert the color. that is reduce 255 on every color
			int newRed = 255 - red;
			int newGreen = 255 - green;
			int newBlue = 255 - blue;

			// edit the array
			data[index] = newRed;
			data[index + 1] = newGreen;
			data[index + 2] = newBlue;

			// even as we have alpha we don't touch it
		}
	}

	// apply changes to image
	image.update();
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(255, 255, 255);

	ofSetColor(255, 255, 255);		// display image with color

	image.draw(0, 0);		// draw image in canvas at position 0, 0

	imageCopy.draw(image.getWidth() + 10, 0);		// print next to the edited image
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
