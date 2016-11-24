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
    void setArea(double area) {area_ = area;}
    void setWorth(double worth) {worth_ = worth;}

    Mat getTemplate() {return template_;}
    double getRadius() {return radius_;}
    double getArea() {return area_;}
    string getName() {return name_;}
    double getWorth() {return worth_;}
    
private:
    string name_;
    Mat template_;
    double radius_;
    double area_;
    double worth_;
};

#endif /* Template_hpp */
