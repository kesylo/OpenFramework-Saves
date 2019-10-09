#include "ofApp.h"

// variables
ofImage image;
ofImage imageCopy;

//--------------------------------------------------------------
void ofApp::setup() {

	image.load("Rainbow.jpg");
	// set imageCopy size and type. this does not copy the image content
	// it just reserve space in memory
	imageCopy.allocate(image.getWidth(), image.getHeight(), OF_IMAGE_COLOR_ALPHA);

	for (int y = 0; y < image.getHeight(); y++)
	{
		for (int x = 0; x < image.getWidth(); x++)
		{
			// get color RGBA of each pixel a position xy
			ofColor imageColor = image.getColor(x, y);

			// turn rgb pixel to grayScale
			// eg: pixel: [122, 23, 67] becomes [70.6, 70.6, 70.6]
			int grayScale = (imageColor.r + imageColor.g + imageColor.b) / 3;

			// create grayscaled color
			ofColor newColor(grayScale, grayScale, grayScale);

			// set it on the new image
			imageCopy.setColor(x, y, newColor);
		}
	}
	// update edited image
	imageCopy.update();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetBackgroundColor(255, 255, 255);		// set windows BG white

	ofSetColor(255, 255, 255);		// display image with color

	image.draw(0, 0);		// draw image in canvas at position 0, 0

	imageCopy.draw(image.getWidth() + 10, 0);		// print next to the edited image
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
