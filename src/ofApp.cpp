#include "ofApp.h"

// variables
ofImage image;
ofImage imageCopy;

//--------------------------------------------------------------
void ofApp::setup() {
	int h, s, b;

	int treshold = 200;

	image.load("SinCity.jpg");
	// set imageCopy size and type. this does not copy the image content
	// it just reserve space in memory
	imageCopy.allocate(image.getWidth(), image.getHeight(), OF_IMAGE_COLOR);

	for (int y = 0; y < image.getHeight(); y++)
	{
		for (int x = 0; x < image.getWidth(); x++)
		{
			// get color RGB of each pixel a position xy
			ofColor rgbColor = image.getColor(x, y);

			// Convert to grayscale
			int grayScale = (rgbColor.r + rgbColor.g + rgbColor.b) / 3;

			// if less than treshold apply white
			if (grayScale < treshold)
			{
				// apply white
				ofColor blackColor(0, 0, 0);
				// set it on the new image
				imageCopy.setColor(x, y, blackColor);
			}
			else
			{
				// apply black
				ofColor whiteColor(255, 255, 255);
				// set it on the new image
				imageCopy.setColor(x, y, whiteColor);

			}
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
