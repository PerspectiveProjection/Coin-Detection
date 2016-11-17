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
#include <vector>

using namespace std;
using namespace cv;

vector<Coin> setCoinAttributes(Mat orig_image) {
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

    //pass labeled image to coin creation function
    vector<Coin> coin_vector;
    setCoins(&coin_vector, labeled_image, stats, centroids);

    //return vector of coins
    return coin_vector;
}

void setCoins(vector<Coin> *coin_vector, Mat labeled_image, Mat stats, Mat centroids) {
    //navigate through objects, skipping 0 since it's background
    for(int i = 1; i < stats.cols; i++) {
        //grab x, y of center then the label at that point
        int center_x = centroids.at<double>(i, 0);
        int center_y = centroids.at<double>(i, 1);
        int label = labeled_image.at<uchar>(center_y, center_x);

        //create a new coin and push back into vector
        Coin new_coin(stats.at<int>(i, CC_STAT_AREA), label,
                     centroids.at<double>(i, 0),
                     centroids.at<double>(i, 1),
                     0);
        
        coin_vector -> push_back(new_coin);
    }
}

Mat circularHough(Mat orig_image) {
    Mat grey_image;
    vector<Vec3f> circles;
    
    //greyscale image
    cvtColor(orig_image, grey_image, COLOR_BGR2GRAY);
    //blur image and save to grey_image
    GaussianBlur(grey_image, grey_image, Size(9,9), 2, 2);
    
    //circular hough transform, save [x-coord, y-coord, radius] in circles vector
    //4 numbers at end control, upper threshold for canny, threshold for center,
    //min and max radius to be detected, 0 is default.
    HoughCircles(grey_image, circles, HOUGH_GRADIENT, 1, grey_image.rows/8, 150, 50, 0, 0);
    
    //go through circles vector
    for(int i = 0; i < circles.size(); i++) {
        //get (x, y) coordinates and radius
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        //draw circle centers
        circle(orig_image, center, 3, Scalar(0, 255, 0), -1, 8, 0);
        //draw circle outlines
        circle(orig_image, center, radius, Scalar(0, 0, 255), 3, 8, 0);
    }
    
    //display image
    namedWindow("Hough Demo", WINDOW_AUTOSIZE);
    imshow("Hough Demo", orig_image);
    //save image
    imwrite("houghImage.jpg", orig_image);
    waitKey(0);
    
    return orig_image;
}
