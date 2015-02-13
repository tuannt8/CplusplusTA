//
//  primeFact.h
//  Excercise
//
//  Created by Tuan Nguyen Trung on 2/9/15.
//  Copyright (c) 2015 Tuan Nguyen Trung. All rights reserved.
//

#ifndef Excercise_primeFact_h
#define Excercise_primeFact_h

#include <iostream>

void primeFact(){
    int n;
 //   std::cout << "Input number: " ;
    std::cin >> n;
    
//    std::cout << std::endl << n << " = ";
    
    int N = n;
    
    for (int i = 2; i < N/2; i++) {
        //Check if i is prime
        bool isPrime = true;
        for (int j = 2; j < i/2; j++) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }
        
        if (!isPrime) {
            continue;
        }
        
//        if (n == i) {
//            std::cout << i;
//            break;
//        }
        
      //  std::cout << "Test i = " << i << std::endl;
        
        // Divide for i
        while (1) {
            if(n==i){
                n = 1;
                std::cout << i;
                break;
            }
            else if(n % i == 0){
                n = n/i;
                std::cout << i <<" * ";
            }
            else
                break;
        }
    }
    
    std::cout<<std::endl;
}

#endif
