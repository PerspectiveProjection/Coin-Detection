//
//  Coin.hpp
//  Coin Detector
//
//  Created by William Wu and Elizabeth Kelly on 11/15/16.
//  Copyright © 2016 PerspectiveProjection. All rights reserved.
//

#ifndef Coin_hpp
#define Coin_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class Coin {
    public:
        Coin(int a = 0, int l = 0, int x = 0, int y = 0, double w = 0) : area(a), label(l), centerX(x),
            centerY(y), worth(w) {};
    
		int getArea() const { return area; }
		int getCenterX() const { return centerX; }
		int getCenterY() const { return centerY; }
		double getWorth() const { return worth; }
    
    private:
        int area;
        int label;
        int centerX;
        int centerY;
        double worth;
};
#endif /* Coin_hpp */
