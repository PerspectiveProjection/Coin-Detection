//
//  Template.hpp
//  Coin Detector
//
//  Created by Elizabeth Kelly on 11/19/16.
//  Copyright © 2016 Perspective Projection. All rights reserved.
//

#ifndef Template_hpp
#define Template_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Template {
public:
    Template(string name, Mat image) : name_(name), template_(image) {};
    void setRadius(double radius) {radius_ = radius;}
    
    Mat getTemplate() {return template_;}
    double getRadius() {return radius_;}
    string getName() {return name_;}
    
private:
    string name_;
    Mat template_;
    double radius_;
};

#endif /* Template_hpp */
