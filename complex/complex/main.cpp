//
//  main.cpp
//  complex
//
//  Created by yuyi on 17/1/19.
//  Copyright © 2017年 yuyi. All rights reserved.
//

#include <iostream>
#include <complex>

using namespace std;

int main(int argc, const char * argv[]) {
    
    complex<double> a=1;
    complex<double> b{1,2.1};
    complex<double> c={1,2};
    // insert code here...
    std::cout << a << endl << b << endl << (c+b) << endl<<
    
    c.real()<<endl<<c.imag()<<endl;
    return 0;
}
