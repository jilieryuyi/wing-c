//
//  hash.h
//  hastable
//
//  Created by yuyi on 17/2/25.
//  Copyright © 2017年 yuyi. All rights reserved.
//

#ifndef hash_h
#define hash_h

#include <stdio.h>
#include "list.h"

typedef struct _WHASH {
    WLL *data;
    int size;
} WHASH;

//获取key对应的hash code
unsigned int getHasnCode(const char *key,unsigned int length);

//初始化hastable
void hashtableInit(WHASH **table,int initialCapacity);

//添加到hastable
void addStrStrToHashTable(WHASH **table, const char *key, char *value );
void addStrDoubleToHashTable(WHASH **table, const char *key, double value );
void addStrPVoidToHashTable(WHASH **table, const char *key, void *value );
void addDoubleStrToHashTable(WHASH **table, const double key, char *value );
void addDoubleDoubleToHashTable(WHASH **table, const double key, double value );
void addDoublePVoidToHashTable(WHASH **table, const double key, void *value );

//释放hashtable
void hashtableFree(WHASH **table);
//重置hashtable
void reHash( WHASH **table, int new_size );

//查找hashtable
double getDoubleDataByKeyCharFromHashTable(WHASH **table,const char* key);
void  *getPVoidDataByKeyCharFromHashTable(WHASH **table,const char* key);
char  *getCharDataByKeyCharFromHashTable(WHASH **table,const char* key);
double getDoubleDataByKeyDoubleFromHashTable(WHASH **table,const double key);
void  *getPVoidDataByKeyDoubleFromHashTable(WHASH **table,const double key);
char  *getCharDataByKeyDoubleFromHashTable(WHASH **table,const double key);

//判断key是否存在
int isCharKeyExists(WHASH **table,const char *key );

//迭代器
void WhashMap( WHASH **table, WllListMap callback );

#endif /* hash_h */
