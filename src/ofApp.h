#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxGrafica.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// my Methods
		ofImage getGrayScaledImageOf(ofImage image);

		ofImage LUTBlackAndWhite(ofImage imageIn);

		ofImage LUTVShape(ofImage imageIn);

		void showHistogramOf(ofImage grayImage);

		int countValueOccurences(int num, int* arr, int length);

		void drawPlotOnScreen(vector<ofxGPoint> points, string plotName, string xAxisName, string yAxisName, int plotHeight);

		// Gui
		ofxPanel gui;
		ofxIntSlider intSlider;
		ofxGPlot plot;
		
};
