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
#include "Template.hpp"
#include <vector>
#include <string>

using namespace std;
using namespace cv;

/**
 * Function that blurs then grayscales the image, converts it to binary, and labels the objects 
 using the connected components method. The resulting images from the connected components method contain
 information about the object's label and centroid in the for of a matrix (image), which are the passed 
 into the setCoins method.
 * orig_image is the input image of coins.
 * Returns a vector of Coin objects computed by the setCoins method.
 **/
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

/**
 * Function that creates a Coin object using the computed center x,y coordinates, area, and label. 
 The objects are then pushed into a vector of type Coin.
 * coin_vector is the vector of Coin objects.
 * labled_image is the image with labeled/segmented coin objects
 * stats is the matrix computed from the connected components method
 * centroids is the matrix computed from the connected components method
 **/
void setCoins(vector<Coin> *coin_vector, Mat labeled_image, Mat stats, Mat centroids) {
    //navigate through objects, skipping 0 since it's background
    for(int i = 1; i < stats.cols; i++) {
        //grab x, y of center then the label at that point
        int center_x = centroids.at<double>(i, 0);
        int center_y = centroids.at<double>(i, 1);
        int label = labeled_image.at<uchar>(center_y, center_x);

        //create a new coin and push back into vector
        Coin new_coin(stats.at<int>(i, CC_STAT_AREA), label,
                     center_x,
                     center_y,
                     0);
        
        coin_vector -> push_back(new_coin);
    }
}

/**
 * Function that converts an image to grayscale and performs a circular Hough transform to detect the 
 cirlces, their contours, and their centers.
 * orig_image is the input image of coins.
 * Returns the original image with the centers and outlines of the detected circles drawn on.
 **/
Mat circularHough(Mat orig_image, vector<Coin> *coin_vector) {
    Mat grey_image;
    vector<Vec3f> circles;
    
    //greyscale image
    cvtColor(orig_image, grey_image, COLOR_BGR2GRAY);
    //blur image and save to grey_image
    GaussianBlur(grey_image, grey_image, Size(7,7), 0);

    //circular hough transform, save [x-coord, y-coord, radius] in circles vector
    //4 numbers at end control, upper threshold for canny, threshold for center,
    //min and max radius to be detected, 0 is default.
    HoughCircles(grey_image, circles, HOUGH_GRADIENT, 1, grey_image.rows/8, 150, 50, 0, 0);
    
    //go through circles vector
    for(int i = 0; i < circles.size(); i++) {
        //get (x, y) coordinates and radius
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        double radius = cvRound(circles[i][2]);
        //set radius from circles
        coin_vector -> at(i).setRadius(radius);
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

//TODO implement template matching
void templateMatch(Mat orig_image, vector<Coin> coin_vector, vector<Template> templates) {
    //string for the filename
    string name = "";
    //new vector of resized templates
    vector<Template> resized_templates;
    
    for (int i = 0; i < templates.size(); i++) {
        Mat temp_blur_image;
        //corcle vector for the hough transform
        vector<Vec3f> temp_circles;
        
        name = "template" + to_string(i+1);
        imwrite(name + ".jpg", templates[i].getTemplate());
        //blur the template
        GaussianBlur(templates[i].getTemplate(), temp_blur_image, Size(7,7), 0);
        
        name = "template_blur" + to_string(i+1);
        imwrite(name + ".jpg", temp_blur_image);
        
        //circular hough transform, save [x-coord, y-coord, radius] in circles vector
        //4 numbers at end control, upper threshold for canny, threshold for center,
        //min and max radius to be detected, 0 is default.
        HoughCircles(temp_blur_image, temp_circles, HOUGH_GRADIENT, 1, temp_blur_image.rows/8, 150, 100, 0, 0);
        //loop through circles vector to obtain the center points and radius
        for(int k = 0; k < temp_circles.size(); k++) {
            //get (x, y) coordinates and radius
            Point center(cvRound(temp_circles[k][0]), cvRound(temp_circles[k][1]));
            double radius = cvRound(temp_circles[k][2]);
            //set radius from circles
            templates[i].setRadius(radius);
            //check
            //draw circle centers
            circle(templates[i].getTemplate(), center, 3, Scalar(0, 255, 0), -1, 8, 0);
            //draw circle outlines
            circle(templates[i].getTemplate(), center, radius, Scalar(0, 0, 255), 3, 8, 0);
            
        }
        //clear circles vector to reuse
        temp_circles.clear();
        
        name = "template_hough" + to_string(i+1);
        imwrite(name + ".jpg", templates[i].getTemplate());
    }
    //resize the templates
    for (int j = 0; j < templates.size(); j++) {
        Mat temp_resize_image;
        //scale factor
        double scale = templates[j].getRadius() /  coin_vector[j].getRadius();
        int rows = templates[j].getTemplate().rows;
        int cols = templates[j].getTemplate().cols;
        //scale the template down
        int new_rows = rows/scale;
        int new_cols = cols/scale;
        //check
        cout << rows << " " << cols << endl;
        cout << new_rows << " " << new_cols << endl;
        
        resize(templates[j].getTemplate(), temp_resize_image, cvSize(new_rows, new_cols));
        //templates[j].getTemplate() = temp_resize_image; -->did not work
        
        //create new Template object with the template name and rescaled template
        Template resized_template(templates[j].getName(), temp_resize_image);
        //push into the resized template vector
        resized_templates.push_back(resized_template);
        
        name = "template_resize" + to_string(j+1);
        imwrite(name + ".jpg", resized_templates[j].getTemplate());
    }
    /*
    //TODO rotate each template via loop and perform matchTemplate at each iteration for each template
    Mat matched_image;
    
    //matchTemplate(orig_image, resized_templates[j].getTemplate(), matched_image, TM_SQDIFF_NORMED);
    imwrite("matchedImage.jpg", matched_image);
    */
    
    //check
    for (int i = 0; i < coin_vector.size(); i++) {
        cout << "Coin " << i+1 << endl;
        cout << "Area " << coin_vector[i].getArea() << endl;
        cout << "Label " << coin_vector[i].getLabel() << endl;
        cout << "Radius " << coin_vector[i].getRadius() << endl;
        cout << "x center " << coin_vector[i].getCenterX() << endl;
        cout << "y center " << coin_vector[i].getCenterY() << endl;
        cout << endl;
    }
    
    //check
    for (int i = 0; i < templates.size(); i++) {
        cout << "Template " << templates[i].getName() << endl;
        cout << "Radius " << templates[i].getRadius() << endl;
        cout << endl;
    }
}
