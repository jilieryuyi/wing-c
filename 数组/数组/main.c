//
//  main.c
//  数组
//
//  Created by yuyi on 17/2/25.
//  Copyright © 2017年 yuyi. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    
    int *start = a;
    
    printf("%d\r\n",*(start+9));
    
    char *b[2] = {"abc0000","123999999"};
    
    char *c = "123";
    
    char *d[2] = {"111","222"};
    
    
    printf("%s\r\n",*(d));
    
    
    return 0;
}
