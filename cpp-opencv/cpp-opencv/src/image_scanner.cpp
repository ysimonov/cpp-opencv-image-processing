#define _USE_MATH_DEFINES

#include "../include/header.hpp"
#include <vector>
#include <cmath>

void pageScanner(const cv::Mat& image) {
	/*
		This function finds contour of the image
		that contains oriented page with some text
	*/

	// Edge detection
	cv::Mat edged;
	double threshold1 = 50.0;
	double threshold2 = 200.0;
	int apertureSize = 3;
	bool L2gradient = true;
	cv::Canny(image, edged, threshold1, threshold2, apertureSize, L2gradient);

	/*

	// Show Results
	cv::imshow("Canny Image", edged);

	// Wait Key
	cv::waitKey(0);
	cv::destroyAllWindows();

	*/

	// Standard Hough Line Transform
	std::vector<cv::Vec2f> lines;	// holds results of detection
	double rho = 1.0;
	double theta = M_PI / 180.0;
	int threshold = 150;
	double srn = 0.0;
	double stn = 0.0;
	cv::HoughLines(edged, lines, rho, theta, threshold, srn, stn);

	// Copy Edges to Image that will contain Hough Lines
	cv::Mat cdst;
	cv::cvtColor(edged, cdst, cv::COLOR_GRAY2BGR);

	// Draw Lines
	const auto lineType = cv::LINE_AA;
	const auto color = cv::Scalar(0, 0, 255);
	int thickness = 3;
	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0];
		float theta = lines[i][1];
		cv::Point pt1, pt2;
		double a = std::cos(theta);
		double b = std::sin(theta);
		double x0 = a * rho;
		double y0 = b * rho;
		pt1.x = int(std::round(x0 + 1000 * (-b)));
		pt1.y = int(std::round(y0 + 1000 * (a)));
		pt2.x = int(std::round(x0 - 1000 * (-b)));
		pt2.y = int(std::round(y0 - 1000 * (a)));
		cv::line(cdst, pt1, pt2, color, thickness, lineType);
	}

	// Show Results
	cv::imshow("Original Image", image);
	cv::imshow("Detected Hough Lines", cdst);

	// Wait Key
	cv::waitKey(0);
	cv::destroyAllWindows();

}