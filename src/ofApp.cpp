#include "ofApp.h"
#include "ofxGrafica.h"

ofImage mainImage;
ofImage grayImage;
ofImage lutImage;
int grayAddedValue = 0;
bool drawMainImage = false; 
bool drawGrayImage = false;
bool drawLUT = false;

//--------------------------------------------------------------
void ofApp::setup() {
	// create gui and add elements to it
	gui.setup();
	gui.add(intSlider.setup("Grayscale Slider", 0, 0, 255));
	
	// load original image
	mainImage.load("SinCity.jpg");

	grayAddedValue = 3;

	if (grayAddedValue > 1 && grayAddedValue < 5)
	{
		cout << "yess";
	}

	//------------------------------------------------------------------------

	/*int arr[10] = { 3,4,1,2,4,5,6,5,4,5 };

	cout << countValueOccurences(5, arr, 10);*/
	

	

	
}

//--------------------------------------------------------------
void ofApp::update() {
	

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetBackgroundColor(255);
	ofSetColor(255);

	if (drawMainImage)
	{
		mainImage.draw(0, 0);
	}

	if (drawGrayImage)
	{
		grayImage.draw(mainImage.getWidth() + 10, 0);
	}

	if (drawLUT)
	{
		lutImage.draw(mainImage.getWidth() + 10, 0);
	}
	
	

	
	// display plot
	/*plot.setDim(500, 300);
	plot.setPos(mainImage.getWidth(), 0);
	plot.beginDraw();
	plot.drawBackground();
	plot.drawBox();
	plot.drawYAxis();
	plot.drawXAxis();
	plot.drawTitle();
	plot.drawHistograms();
	plot.endDraw();
	*/
	
	// draw gui 
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == '7')
	{
		drawMainImage = true;
		draw();
	}
	if (key == '1')
	{
		// Display gray version of Image
		mainImage.load("hue.jpg");
		grayImage = getGrayScaledImageOf(mainImage);
		draw();
	}
	if (key == OF_KEY_UP)
	{
		grayAddedValue += 50;
		grayImage = getGrayScaledImageOf(mainImage);
		draw();
	}
	if (key == 'd')
	{
		// show histogram of an image
		mainImage.load("SinCity.jpg");		// load image
		grayImage = getGrayScaledImageOf(mainImage);		// convert to gray
		showHistogramOf(grayImage);		// display histogram
	}
	if (key == 'b')
	{
		// draw LUT Black and White
		lutImage = LUTBlackAndWhite(mainImage);
		drawLUT = true;
		draw();
	}
	if (key == 'v')
	{
		// draw LUT Black and White
		lutImage = LUTVShape(mainImage);
		drawLUT = true;
		draw();
	}
}



//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

int ofApp::countValueOccurences(int num, int* arr, int length) {
	if (!length)
		return 0;
	int c = countValueOccurences(num, arr + 1, length - 1);
	return arr[0] == num ? c + 1 : c;
}

ofImage ofApp::getGrayScaledImageOf(ofImage image) {
	int w = image.getWidth();
	int h = image.getHeight();
	ofImage imgCopy;
	ofColor grayColor;
	int grayLevel;
	int i;

	// get all pixels in array
	ofPixels_<unsigned char> listPixels = image.getPixels();
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
			grayColor = (grayLevel , grayLevel, grayLevel);

			// set it on pixel list
			listPixels.setColor(x, y, grayColor);
		}
	}
	// create image copy from edited pixel array 
	imgCopy.setFromPixels(listPixels);

	return imgCopy;
}

ofImage ofApp::LUTBlackAndWhite(ofImage imageIn)
{
	int grayLevel;
	ofColor black = ofColor::black;
	ofColor white = ofColor::white;
	ofImage imageOut;
	imageOut.allocate(imageIn.getWidth(), imageIn.getHeight(), OF_IMAGE_COLOR);

	for (int y = 0; y < imageIn.getHeight(); y++)
	{
		for (int x = 0; x < imageIn.getWidth(); x++)
		{
			grayLevel = imageIn.getColor(x, y).getLightness();

			if (grayLevel <= 127)
			{
				imageOut.setColor(x, y, black);
			}
			else
			{
				imageOut.setColor(x, y, white);
			}
		}
	}
	imageOut.update();

	return imageOut;
}

ofImage ofApp::LUTVShape(ofImage imageIn)
{
	int grayLevel;
	int start = 0;
	int middleLeft = 65;
	int middleRight = 126;
	int end = 255;
	ofImage imageOut;
	ofColor black = ofColor::black;
	ofColor white = ofColor::white;
	imageOut.allocate(imageIn.getWidth(), imageIn.getHeight(), OF_IMAGE_COLOR);

	for (int y = 0; y < imageIn.getHeight(); y++)
	{
		for (int x = 0; x < imageIn.getWidth(); x++)
		{
			grayLevel = imageIn.getColor(x, y).getLightness();

			if (grayLevel >= start && grayLevel <= middleLeft || grayLevel >= middleRight && grayLevel <= end)
			{
				imageOut.setColor(x, y, white);
			}
			else if (grayLevel >= middleLeft && grayLevel <= middleRight)
			{
				imageOut.setColor(x, y, black);
			}
		}
	}
	imageOut.update();

	return imageOut;
}

void ofApp::drawPlotOnScreen(vector<ofxGPoint> points, string plotName, string xAxisName, string yAxisName, int plotHeight) {
	// Add the points
	plot.setPoints(points);

	// Set the plot title and the axis labels
	plot.setTitleText(plotName);
	plot.getXAxis().setAxisLabelText(xAxisName);
	plot.getYAxis().setAxisLabelText(yAxisName);
	plot.getTitle().setTextAlignment(GRAFICA_LEFT_ALIGN);
	plot.startHistograms(GRAFICA_VERTICAL_HISTOGRAM);
	plot.setYLim(0, plotHeight);
	plot.setXLim(1, 300);
	plot.getHistogram().setDrawLabels(true);
	plot.getHistogram().setRotateLabels(true);
	
	plot.getHistogram().setBgColors({ ofColor(0, 0, 255, 50), ofColor(0, 0, 255, 100), ofColor(0, 0, 255, 150), ofColor(0, 0, 255, 200) }); // Je définis la couleur des rectangles.

	// Set the plot position on the screen
}

void ofApp::showHistogramOf(ofImage grayImage) {
	int w = grayImage.getWidth();
	int h = grayImage.getHeight();

	// Prepare the points for the plot
	const int xAxisPoints = 256;
	vector<ofxGPoint> points;
	int histogram[xAxisPoints] = {0};

	// get all pixels in array
	ofPixels_<unsigned char> listPixels = grayImage.getPixels();

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			histogram [ listPixels.getColor(x, y).r ] +=1;
		}
	}

	for (int i = 0; i < xAxisPoints; i++)
	{
		points.emplace_back(i + 1, histogram[i]);
	}

	drawPlotOnScreen(points, "GrayScale Histogram", "x", "y", 40000);
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
