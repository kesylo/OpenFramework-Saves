#include "ofApp.h"
#include "ofxGrafica.h"
#include <iterator>
#include <numeric>
#include <algorithm>

// pour l'exam tu peux faire le plus, fois, divisé entre 2 images

#pragma region variables
ofImage main_image;
bool draw_main_image = false;

ofImage seven_diff_img_1;
ofImage seven_diff_img_2;
ofImage seven_diff_img_out;
bool draw_seven_diff_img = false;

ofImage main_image_clone;
bool draw_main_image_clone = false;

ofImage gray_image;
bool draw_gray_image = false;

ofImage lut_image;
bool draw_lut = false;

ofImage a_binarisation_image;
bool draw_a_bin_image = false;

// other variables
int gray_added_value = 0;












#pragma endregion


//--------------------------------------------------------------
void ofApp::setup() {
	// create gui and add elements to it
	gui.setup();
	gui.add(int_slider.setup("Grayscale Slider", 0, 0, 255));
	
	// load original image
	main_image.load("coins.jpg");

	// load images for subtract
	seven_diff_img_1.load("1.jpg");
	seven_diff_img_2.load("2.jpg");

	
}

//--------------------------------------------------------------
void ofApp::update() {
	

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetBackgroundColor(255);
	ofSetColor(255);

	if (draw_main_image)
	{
		main_image.draw(0, 0);
	}
	if (draw_main_image_clone)
	{
		main_image_clone.draw(main_image.getWidth() + 10, 0);
	}
	if (draw_gray_image)
	{
		gray_image.draw(main_image.getWidth() + 10, 0);
	}
	if (draw_lut)
	{
		lut_image.draw(main_image.getWidth() + 10, 0);
	}
	if (draw_a_bin_image)
	{
		a_binarisation_image.draw(main_image.getWidth() + 10, 0);
	}
	if (draw_seven_diff_img)
	{
		seven_diff_img_1.draw(0,0);
		seven_diff_img_2.draw(0,seven_diff_img_2.getHeight() + 2);
		seven_diff_img_out.draw(main_image.getWidth() + 10, 0);
	}
	
	//// display plot
	//plot.setDim(300, 300);
	//plot.setPos(0, 300);
	//plot.beginDraw();
	//plot.drawBackground();
	//plot.drawBox();
	//plot.drawYAxis();
	//plot.drawXAxis();
	//plot.drawTitle();
	//plot.drawHistograms();
	//plot.endDraw();
	
	// draw gui 
	gui.draw();
}

void ofApp::keyPressed(int key) {
	if (key == '7')
	{
		draw_main_image = true;
		draw();
	}
	if (key == 'r')
	{
		draw_main_image_clone = true;
		draw();
	}
	if (key == '1')
	{
		// Display gray version of Image
		gray_image = get_gray_scaled_image_of(main_image);
		draw();
	}
	if (key == OF_KEY_UP)
	{
		gray_added_value += 50;
		gray_image = get_gray_scaled_image_of(main_image);
		draw();
	}
	if (key == 'h')
	{
		// show histogram of an image
		gray_image = get_gray_scaled_image_of(main_image);
		show_histogram_of(gray_image);
	}
	if (key == 'b')
	{
		// draw LUT Black and White
		lut_image = lut_black_and_white(main_image, 127);
		draw_lut = true;
		draw();
	}
	if (key == 'v')
	{
		// draw LUT Black and White
		lut_image = lut_v_shape(main_image);
		draw_lut = true;
		draw();
	}
	if (key == 'a')
	{
		// Adaptive Binarisation
		a_binarisation_image = adaptive_binarisation(main_image);
		draw_a_bin_image = true;
		draw();
	}
	if (key == '-')
	{
		// subtract 2 images
		draw_seven_diff_img = true;
		seven_diff_img_out = subtract_images(seven_diff_img_1, seven_diff_img_2);
		draw();
	}
}



/*-----------------------------------------------------------------------------------------------------*/

ofImage ofApp::subtract_images(const ofImage& img_in1, const ofImage& img_in2)
{
	// variables
	const auto img1_Height = img_in1.getHeight();
	const auto img2_Height = img_in2.getHeight();
	const auto img1_Width = img_in1.getWidth();
	const auto img2_Width = img_in2.getWidth();
	ofImage img_out;
	const auto& list_pixels1 = img_in1.getPixels();
	const auto& list_pixels2 = img_in2.getPixels();
	auto list_pixels_out = list_pixels1;
	const auto pixelColors1 = new ofColor[img1_Height * img1_Width];
	const auto pixelColors2 = new ofColor[img2_Height * img2_Width];

	// check if the 2 images have the same size
	if (img1_Height == img2_Height && img1_Width == img2_Width)
	{
		// loop through both images
		for (auto y = 0; y < img1_Height; y++)
		{
			for (auto x = 0; x < img1_Width; x++)
			{
				const int i = y * img1_Width + x;

				// get each pixel from each image
				pixelColors1[i] = list_pixels1.getColor(x, y);
				pixelColors2[i] = list_pixels2.getColor(x, y);

				// subtract
				float color = (pixelColors1[i].getLightness()) - (pixelColors2[i].getLightness());
				if (color < 0)
				{
					color = color * (-1);
					ofColor gray_color(color);
					list_pixels_out.setColor(x, y, gray_color);
				}
				else if (color == 0 || color > 0)
				{
					ofColor gray_color(color);
					list_pixels_out.setColor(x, y, gray_color);
				}
			}
		}
		img_out.setFromPixels(list_pixels_out);
	}
	else
	{
		cout << "Not same size";
	}

	return img_out;
}

std::vector<int> ofApp::get_histogram_array(const ofImage& gray_image)
{
	const int w = gray_image.getWidth();
	const int h = gray_image.getHeight();

	// Prepare the points for the plot
	const auto x_axis_points = 256;
	vector<ofxGPoint> points;
	int histogram[x_axis_points] = { 0 };

	// get all pixels in array
	const auto& list_pixels = gray_image.getPixels();

	for (auto y = 0; y < h; y++)
	{
		for (auto x = 0; x < w; x++)
		{
			histogram[list_pixels.getColor(x, y).r] += 1;
		}
	}

	std::vector<int> histogram_v(histogram, histogram + 256);

	return histogram_v;
}

ofImage ofApp::resize_image(ofImage image_in, const float scale_down_value) {
	image_in.resize(image_in.getWidth() / scale_down_value, image_in.getHeight() / scale_down_value);
	return image_in;
}

ofImage ofApp::get_gray_scaled_image_of(ofImage image) {
	auto w = image.getWidth();
	auto h = image.getHeight();
	ofImage img_copy;
	ofColor gray_color;
	int gray_level;
	int i;

	// get all pixels in array
	ofPixels_<unsigned char> list_pixels = image.getPixels();
	// create array for all pixels color
	ofColor* pixelColors = new ofColor[w * h];

	for (auto y = 0; y < h; y++)
	{
		for (auto x = 0; x < w; x++)
		{
			// for loop in colors
			i = y * w + x;

			// get color of each pixel a position xy
			pixelColors[i] = list_pixels.getColor(x, y);

			// easy get grey level
			gray_level = pixelColors[i].getLightness();

			// create grey color
			gray_color = (gray_level , gray_level, gray_level);

			// set it on pixel list
			list_pixels.setColor(x, y, gray_color);
		}
	}
	// create image copy from edited pixel array 
	img_copy.setFromPixels(list_pixels);

	return img_copy;
}

ofImage ofApp::lut_black_and_white(const ofImage& image_in, const int threshold)
{
	int gray_level;
	auto black = ofColor::black;
	auto white = ofColor::white;
	ofImage image_out;
	image_out.allocate(image_in.getWidth(), image_in.getHeight(), OF_IMAGE_COLOR);

	for (auto y = 0; y < image_in.getHeight(); y++)
	{
		for (auto x = 0; x < image_in.getWidth(); x++)
		{
			gray_level = image_in.getColor(x, y).getLightness();

			if (gray_level <= threshold)
			{
				image_out.setColor(x, y, black);
			}
			else
			{
				image_out.setColor(x, y, white);
			}
		}
	}
	image_out.update();

	return image_out;
}

ofImage ofApp::lut_v_shape(const ofImage& image_in)
{
	int gray_level;
	auto start = 0;
	auto middle_left = 65;
	auto middle_right = 126;
	auto end = 255;
	ofImage image_out;
	auto black = ofColor::black;
	auto white = ofColor::white;

	image_out.allocate(image_in.getWidth(), image_in.getHeight(), OF_IMAGE_COLOR);

	for (auto y = 0; y < image_in.getHeight(); y++)
	{
		for (auto x = 0; x < image_in.getWidth(); x++)
		{
			gray_level = image_in.getColor(x, y).getLightness();

			if (gray_level >= start && gray_level <= middle_left || gray_level >= middle_right && gray_level <= end)
			{
				image_out.setColor(x, y, white);
			}
			else if (gray_level >= middle_left && gray_level <= middle_right)
			{
				image_out.setColor(x, y, black);
			}
		}
	}
	image_out.update();

	return image_out;
}

ofImage ofApp::adaptive_binarisation(const ofImage& image_in)
{
	ofImage out_image;

	// get vector array from histogram. size is 256 always
	auto histogram_values = get_histogram_array(image_in);

	// split in 2
	auto const half_size = histogram_values.size() / 2;
	std::vector<int> part_1(histogram_values.begin(), histogram_values.begin() + half_size);
	std::vector<int> part_2(histogram_values.begin() + half_size, histogram_values.end());

	// get the max value in each array
	const auto max_1 = * max_element(part_1.begin(), part_1.end());
	const auto max_2 = * max_element(part_2.begin(), part_2.end());

	// find element in in vector
	const auto it_1 = std::find(histogram_values.begin(), histogram_values.end(), max_1);
	const auto it_2 = std::find(histogram_values.begin(), histogram_values.end(), max_2);

	// Get index of element from iterator
	const auto index_1 = std::distance(histogram_values.begin(), it_1);
	const auto index_2 = std::distance(histogram_values.begin(), it_2);

	// make average to find interval right middle
	int avg = (index_2 + index_1) / 2;

	// show image values
	/*for (int v : histogram_values)
	{
		cout << v << " - ";
	}*/

	cout << " \n";
	cout << max_1 << " max 1 val \n";
	cout << max_2 << " max 2 \n";
	cout << index_1 << " pos max 1 \n";
	cout << index_2 << " pos max 2 \n";
	cout << avg << " avg of indexes between both max \n";

	// set grayscale threshold to 
	out_image = lut_black_and_white(image_in, avg);

	return out_image;
}

void ofApp::draw_plot_on_screen(const vector<ofxGPoint>& points, const string& plot_name, const string& x_axis_name,
                                const string& y_axis_name, const int plot_height)
{
	// Add the points
	plot.setPoints(points);

	// Set the plot title and the axis labels
	plot.setTitleText(plot_name);
	plot.getXAxis().setAxisLabelText(x_axis_name);
	plot.getYAxis().setAxisLabelText(y_axis_name);
	plot.getTitle().setTextAlignment(GRAFICA_LEFT_ALIGN);
	plot.startHistograms(GRAFICA_VERTICAL_HISTOGRAM);
	plot.setYLim(0, plot_height);
	plot.setXLim(1, 300);
	plot.getHistogram().setDrawLabels(true);
	plot.getHistogram().setRotateLabels(true);
	
	plot.getHistogram().setBgColors({ ofColor(0, 0, 255, 50), ofColor(0, 0, 255, 100), ofColor(0, 0, 255, 150), ofColor(0, 0, 255, 200) }); // Je définis la couleur des rectangles.

	// returns void
}

void ofApp::show_histogram_of(ofImage gray_image) {
	int w = gray_image.getWidth();
	int h = gray_image.getHeight();

	// Prepare the points for the plot
	const int xAxisPoints = 256;
	vector<ofxGPoint> points;
	int histogram[xAxisPoints] = {0};

	// get all pixels in array
	ofPixels_<unsigned char> listPixels = gray_image.getPixels();

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

	draw_plot_on_screen(points, "GrayScale Histogram", "x", "y", 40000);
}



/*-----------------------------------------------------------------------------------------------------*/