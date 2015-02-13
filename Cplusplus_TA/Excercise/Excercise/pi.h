//
//  pi.h
//  Excercise
//
//  Created by Tuan Nguyen Trung on 2/9/15.
//  Copyright (c) 2015 Tuan Nguyen Trung. All rights reserved.
//

#ifndef Excercise_pi_h
#define Excercise_pi_h

#include <iostream>

double pi(int n){
    int sign = 1;
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        double cur = (double)sign / (2*i + 1);
        sign = -sign;
        result += cur;
    }
    
    return result*4;
}

#endif
