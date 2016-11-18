//
//  ImageFunctions.hpp
//  Coin Detector
//
//  Created by William Wu on 11/15/16.
//  Copyright © 2016 Perspective Projection. All rights reserved.
//

#ifndef ImageFunctions_hpp
#define ImageFunctions_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Coin.cpp"
#include <vector>

using namespace cv;
using namespace std;

vector<Coin> setCoinAttributes(Mat orig_image);

void setCoins(vector<Coin> *coinVector, Mat image, Mat stats, Mat centroids);

Mat circularHough(Mat orig_image, vector<Coin> *coin_vector);

void templateMatch(Mat image, vector<Coin> coins);


#endif /* ImageFunctions_hpp */
