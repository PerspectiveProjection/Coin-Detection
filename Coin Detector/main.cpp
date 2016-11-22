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
#include "Template.hpp"
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
    //greyscale original image
    //cvtColor(orig_image, orig_image, COLOR_BGR2GRAY);
    
    //read in the 710x710 templates and store them in an array
    Mat quarter_template = imread("../../Images/Templates/Quarter_Face.jpg");
    Mat penny_template = imread("../../Images/Templates/Penny_Face.jpg");
    Mat dime_template = imread("../../Images/Templates/Dime_Face.jpg");
    Mat nickel_template = imread("../../Images/Templates/Nickel_Face.jpg");
    
    //vector of templates, in order of least amount to greatest amount
    vector<Mat> orig_templates;
    vector<string> template_names;
    orig_templates.push_back(penny_template);
    template_names.push_back("Penny");
    orig_templates.push_back(nickel_template);
    template_names.push_back("Nickel");
    orig_templates.push_back(dime_template);
    template_names.push_back("Dime");
    orig_templates.push_back(quarter_template);
    template_names.push_back("Quarter");
    
    
    //the vector of grayscale templates to be used for template matching
    vector<Template> templates;
    for (int i = 0; i < orig_templates.size(); i++) {
        Mat temp_gray_image;
        cvtColor(orig_templates[i], temp_gray_image, CV_BGR2GRAY);
        Template temp_template(template_names[i], temp_gray_image);
        templates.push_back(temp_template);
    }
    
    if (!orig_image.data) {
        printf("No image data \n");
        return -1;
    }
    
	//assign labels to coins on a binary image
    vector<Coin> coin_vector = setCoinAttributes(orig_image);
    
    //greyscale original image
    //Mat gray_orig_image = orig_image;
    cvtColor(orig_image, orig_image, COLOR_BGR2GRAY);
    Mat transformed_image = circularHough(orig_image, &coin_vector);
    
    imwrite("origImage.jpg", orig_image);
    
    templateMatch(orig_image, coin_vector, templates);
    
    
	return 0;
}


