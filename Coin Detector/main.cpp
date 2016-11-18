//
//  main.cpp
//  Coin Detector
//
//  Created by Elizabeth Kelly and William Wu on 11/14/16.
//  Copyright © 2016 PerspectiveProjection. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Coin.hpp"
#include "ImageFunctions.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    
    String image_file = argv[1]; //filename for the coin image
    Mat orig_image = imread(image_file); //read the file
    resize(orig_image, orig_image, cvSize(378, 504)); //resize the image to 1/8th it's original size
    
    if (!orig_image.data) {
        printf("No image data \n");
        return -1;
    }
   
	//assign labels to coins on a binary image
    vector<Coin> coin_vector = setCoinAttributes(orig_image);

    Mat transformed_image = circularHough(orig_image);
    
    //templateMatch(orig_image, coin_vector);
    
    
	return 0;
}


