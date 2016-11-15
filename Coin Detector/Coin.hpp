//
//  Coin.hpp
//  Coin Detector
//
//  Created by William Wu on 11/15/16.
//  Copyright © 2016 PerspectiveProjection. All rights reserved.
//

#ifndef Coin_hpp
#define Coin_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class Coin {
    public:
        Coin(int area = 0, int centerX = 0, int centerY = 0, double worth = 0);
		int getArea() const { return area; }
		int getCenterX() const { return centerX; }
		int getCenterY() const { return centerY; }
		double getWorth() const { return worth; }

    private:
        int area;
        int centerX;
        int centerY;
        double worth;
};
#endif /* Coin_hpp */
