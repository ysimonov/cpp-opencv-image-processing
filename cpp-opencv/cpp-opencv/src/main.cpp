// main.cpp : Defines the entry point for the application.

#include "../include/header.hpp"
#include <string>
#include <regex>


int main() {

	std::string imagePath;
	std::cout << "Please specify image path: ";
	std::cin >> imagePath;

	// substitute single backslashes with double backslashes
	imagePath = std::regex_replace(
		imagePath,
		std::regex(R"(\\)"),
		R"(\\)"
	);

	// remove double or single quote
	imagePath = std::regex_replace(
		imagePath,
		std::regex(R"([\"'])"),
		R"()"
	);

	cv::Mat image = cv::imread(imagePath);

	if (!image.data) {
		std::cout << "No image data" << std::endl;
		return EXIT_FAILURE;
	}

	std::string displayName = "Display Image";
	cv::namedWindow(displayName, cv::WINDOW_KEEPRATIO);

	int newWidth = 700;
	int newHeight = int(double(newWidth) * image.size().height / image.size().width);
	std::cout << "New Height: " << newHeight << std::endl;

	cv::resizeWindow(displayName, newWidth, newHeight);

	cv::imshow("Display Image", image);
	cv::waitKey(0);
	cv::destroyAllWindows();

	// page scanner using Hough Transform
	pageScanner(image);

	return EXIT_SUCCESS;
}