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
        Coin(int a = 0, int l = 0, int x = 0, int y = 0, double w = 0) : area(a), label(l), center_x(x),
            center_y(y), worth(w) {};
    
		int getArea() const { return area; }
        int getLabel() const { return label; }
		int getCenterX() const { return center_x; }
		int getCenterY() const { return center_y; }
		double getWorth() const { return worth; }
    
        void setWorth(int new_worth) { worth = new_worth; }
    private:
        int area;
        int label;
        int center_x;
        int center_y;
        double worth;
};
#endif /* Coin_hpp */
