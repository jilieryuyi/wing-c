//
//  map.c
//  hashmap
//
//  Created by yuyi on 17/3/4.
//  Copyright © 2017年 yuyi. All rights reserved.
//

#include "map.h"
#include "hash.h"
void initHashMap(unsigned long **map, int size){
    *map = (unsigned long*)malloc(sizeof(unsigned long)*size);
    int i = 0;
    for( i = 0; i < size; i++ ){
        WHASH *table = NULL;
        hashtableInit(&table, size);
        (*map)[i] = (unsigned long)table;
    }
}

void addToHashMap( unsigned long **map, const char *key, const char *hash_key, char *value ){
    int hash_code = getHasnCode(key, sizeof(key));
    WHASH *table = NULL;
    WHASH *table0 = NULL;
    
    table0 = (WHASH*)(*map)[0];
    table = (WHASH*)(*map)[hash_code%table0->size] ;
    
    addStrStrToHashTable(&table, hash_key, value);
}

char* getFromHashMap(unsigned long **map, const char *key, const char *hash_key){
    int hash_code = getHasnCode(key, sizeof(key));
    WHASH *table = NULL;
    WHASH *table0 = NULL;
    table0 = (WHASH*)(*map)[0];
    table = (WHASH*)(*map)[hash_code%table0->size] ;
    
    return getCharDataByKeyCharFromHashTable(&table, hash_key);
}

void freeHashMap(unsigned long **map){
    WHASH *table0 = NULL;
    WHASH *table = NULL;

    int size = 0;
    int i = 0;
    
    table0 = (WHASH*)(*map)[0];
    size = table0->size;
    
    for(i = 0; i < size; i++) {
        table = (WHASH*)(*map)[i];
        hashtableFree(&table);
    }
    
    free(*map);
    *map = NULL;
}
