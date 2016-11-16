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

void setCoinProperties(vector<Coin> coinVector, Mat labeledImage);

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    
    String imageFile = argv[1]; //filename for the coin image
    Mat orig_image = imread(imageFile); //read the file
    resize(orig_image, orig_image, cvSize(378, 504)); //resize the image
    
    if (!orig_image.data) {
        printf("No image data \n");
        return -1;
    }
   
	//Assign labels to coins on a binary image
    Mat labeledImage = GrayscaleAndLabelImage(orig_image);

	vector<Coin> coinVector;
	setCoinProperties(coinVector, labeledImage);
	return 0;
}

void setCoinProperties(vector<Coin> coinVector, Mat labeledImage) {
	/*for(int i = 0; i < labeledImage.rows; i++) {
        int * p = labeledImage.ptr<int>(i);
        for(int j = 0; j < labeledImage.cols * labeledImage.channels() ; j++) {
            cout << p[j] << endl;
        }
	}*/
}
