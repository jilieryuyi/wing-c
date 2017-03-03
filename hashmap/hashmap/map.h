//
//  map.h
//  hashmap
//
//  Created by yuyi on 17/3/4.
//  Copyright © 2017年 yuyi. All rights reserved.
//

#ifndef map_h
#define map_h

#include <stdio.h>
void initHashMap(unsigned long **map, int size);
void addToHashMap(unsigned long **map, const char *key, const char *hash_key, char *value);
char* getFromHashMap(unsigned long **map, const char *key, const char *hash_key);
void freeHashMap(unsigned long **map);
#endif /* map_h */
