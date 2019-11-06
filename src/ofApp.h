#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxGrafica.h"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;

		void keyPressed(int key) override;

		// my Methods

		static ofImage subtract_images(const ofImage& img_in1, const ofImage& img_in2);

		static ofImage get_gray_scaled_image_of(ofImage image);

		static ofImage lut_black_and_white(const ofImage& image_in, int threshold);

		static ofImage lut_v_shape(const ofImage& image_in);

		static ofImage adaptive_binarisation(const ofImage& image_in);

		static ofImage resize_image(ofImage image_in, float scale_down_value);

		void show_histogram_of(ofImage gray_image);

		static std::vector<int> get_histogram_array(const ofImage& gray_image);

		void draw_plot_on_screen(const vector<ofxGPoint>& points, const string& plot_name, const string& x_axis_name,
		                         const string& y_axis_name, const int plot_height);

		// Gui
		ofxPanel gui;
		ofxIntSlider int_slider;
		ofxGPlot plot;

		// keep code
		/*
		// find max element in array
		auto max2 = * max_element(histogram_values.begin(), histogram_values.end());

		// find max element position in array
		cout << distance(val2.begin(), max_element(val2.begin(), val2.end()));

		// sum values. if you want to sum float values, use 0.0 at end
		const auto sum_of_elems = std::accumulate(histogram_values.begin()+ index_1, histogram_values.end() - index_2, 0);

		*/
		
		
};
