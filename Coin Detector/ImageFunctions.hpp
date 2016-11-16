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

Mat GrayscaleAndLabelImage(Mat orig_image);

vector<Coin> setCoins(Mat image, Mat stats, Mat centroids);

#endif /* ImageFunctions_hpp */
