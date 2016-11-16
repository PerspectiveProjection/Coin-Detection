//
//  main.cpp
//  Coin Detector
//
//  Created by William Wu on 11/14/16.
//  Copyright © 2016 war. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv ) {
    
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    
    String imageFile = argv[1]; //filename for the coin image
    Mat orig_image = imread(imageFile); //read the file
    resize(orig_image, orig_image, cvSize(378, 504)); //resize the image
    
    if ( !orig_image.data )
    {
        printf("No image data \n");
        return -1;
    }

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
    connectedComponents(binary_image, labeled_image, 8, CV_16U);
    //normalize the labels for better visibility
    normalize(labeled_image, labeled_image, 0, 255, NORM_MINMAX, CV_8U);
    
    String window_name = "Display Image";
    imshow(window_name, labeled_image);
    namedWindow(window_name, WINDOW_NORMAL);
    
    waitKey(0);
    
    return 0;
}
