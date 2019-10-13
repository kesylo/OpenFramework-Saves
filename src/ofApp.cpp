#include "ofApp.h"

ofImage image;
ofImage grayImage;
int grayAddedValue = 0;

//--------------------------------------------------------------
void ofApp::setup() {
	// create gui and add elements to it
	gui.setup();
	gui.add(intSlider.setup("Grayscale Slider", 0, 0, 255));
	
	// load original image
	image.load("hue.jpg");
}

//--------------------------------------------------------------
void ofApp::update() {
	

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetBackgroundColor(255);
	ofSetColor(255);
	image.draw(0, 0);
	grayImage.draw(image.getWidth() + 10, 0);
	
	// draw gui 
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == '1')
	{
		// Display gray version of Image
		image.load("hue.jpg");
		grayImage = getGrayScaledImageOf(image);
		draw();
	}
	if (key == OF_KEY_UP)
	{
		/*grayAddedValue += 10;
		grayImage = getGrayScaledImageOf(image);
		draw();*/
	}
}



//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

ofImage ofApp::getGrayScaledImageOf(ofImage originalImage) {
	int w = originalImage.getWidth();
	int h = originalImage.getHeight();
	ofImage imgCopy;
	ofColor grayColor;
	int grayLevel;
	int i;

	// get all pixels in array
	ofPixels_<unsigned char> listPixels = originalImage.getPixels();
	// create array for all pixels color
	ofColor* pixelColors = new ofColor[w * h];

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			// for loop in colors
			i = y * w + x;

			// get color of each pixel a position xy
			pixelColors[i] = listPixels.getColor(x, y);

			// easy get grey level
			grayLevel = pixelColors[i].getLightness();

			// create grey color
			grayColor = (grayLevel, grayLevel, grayLevel);

			// set it on pixel list
			listPixels.setColor(x, y, grayColor);
		}
	}
	// create image copy from edited pixel array 
	imgCopy.setFromPixels(listPixels);

	return imgCopy;
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
