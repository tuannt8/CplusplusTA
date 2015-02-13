//
//  g_sum.h
//  Excercise
//
//  Created by Tuan Nguyen Trung on 2/9/15.
//  Copyright (c) 2015 Tuan Nguyen Trung. All rights reserved.
//

#ifndef Excercise_g_sum_h
#define Excercise_g_sum_h


#include <iostream>

void g_sum(){
    std::cout << "Input size n: ";
    int n;
    std::cin >> n;
    
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    
    std::cout << "Gaussian sum is: " << sum << std::endl;
}

void sum2(){
    std::cout << "Input size n: ";
    int n;
    std::cin >> n;
    
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if(i%2 == 0)
            sum += i;
    }
    
    std::cout << "Gaussian sum is: " << sum << std::endl;
}

#endif
