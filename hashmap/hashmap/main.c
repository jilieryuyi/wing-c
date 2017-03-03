//
//  main.c
//  hashmap
//
//  Created by yuyi on 17/3/4.
//  Copyright © 2017年 yuyi. All rights reserved.
//

#include <stdio.h>
#include "list.h"
#include "hash.h"
#include "map.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    //printf("Hello, World!\n");
    
    unsigned long *map = NULL;
    
    initHashMap(&map,8);
    addToHashMap(&map, "a", "b", "000000c");
    
    char *c = getFromHashMap(&map, "a", "b");
    printf("%s\n",c);
    
    freeHashMap(&map);
    return 0;
}
