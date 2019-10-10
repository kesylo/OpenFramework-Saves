#include "ofApp.h"

// variables
ofImage image;
ofImage imageCopy;

//--------------------------------------------------------------
void ofApp::setup() {
	int h, s, b;

	image.load("Rainbow.jpg");
	// set imageCopy size and type. this does not copy the image content
	// it just reserve space in memory
	imageCopy.allocate(image.getWidth(), image.getHeight(), OF_IMAGE_COLOR);

	for (int y = 0; y < image.getHeight(); y++)
	{
		for (int x = 0; x < image.getWidth(); x++)
		{
			// get color RGB of each pixel a position xy
			ofColor rgbColor = image.getColor(x, y);

			// get hsb color vaues from rgb color
			h = rgbColor.getHueAngle();		// in degree
			s = (rgbColor.getSaturation() / 255) * 100;		// in percent %
			b = (rgbColor.getBrightness() / 255) * 100;		// in percent %

			//// For checking  
			//cout << "Hue: " << h << endl;
			//cout << "Saturation: " << s << endl;
			//cout << "Brightness: " << b << endl;

			// create hsb color
			ofColor newColor(h, s, b);

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
