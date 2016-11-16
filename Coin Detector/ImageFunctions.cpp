//
//  ImageFunctions.cpp
//  Coin Detector
//
//  Created by William Wu on 11/15/16.
//  Copyright © 2016 Perspective Projection. All rights reserved.
//

#include "ImageFunctions.hpp"
#include <opencv2/opencv.hpp>
#include "Coin.hpp"

using namespace std;
using namespace cv;

Mat GrayscaleAndLabelImage(Mat orig_image) {
	//convert the image to grayscale
    Mat gray_image;
    cvtColor(orig_image, gray_image, CV_BGR2GRAY);
    //blur the image to remove high frequencies and noise from dust particles
    GaussianBlur(gray_image, gray_image, Size(7, 7), 0);
    
    //threshold the image to convert it to binary
    Mat binary_image;
    binary_image = gray_image > 50; //threshold is 50
    
    //perform sequential labeling (connected components algorithm) to segment the coins
    Mat labeled_image;
    Mat stats, centroids;
    connectedComponentsWithStats(binary_image, labeled_image, stats, centroids, 8, CV_16U);
    
    //normalize the labels for better visibility
    normalize(labeled_image, labeled_image, 0, 255, NORM_MINMAX, CV_8U);

    cout << labeled_image << endl;
    cout << stats << endl;
    cout << centroids << endl;
    
    String window_name = "Display Image";
    imshow(window_name, labeled_image);
    namedWindow(window_name, WINDOW_NORMAL);
    imwrite("labeledImage.pgm", labeled_image);
    
    waitKey(0);
	return labeled_image;

}
