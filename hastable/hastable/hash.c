//
//  hash.c
//  hastable
//
//  Created by yuyi on 17/2/25.
//  Copyright © 2017年 yuyi. All rights reserved.
//

#include "hash.h"

#define _HASH(table,i) ((WHASH *)(*table +i))

/**
 * 获取字符串的hash code
 * @return unsigned int
 */
unsigned int getHasnCode(const char *str,unsigned int len)
{
    unsigned int hash = 0;
    unsigned int x    = 0;
    unsigned int i    = 0;
    for(i = 0; i < len; str++, i++)
    {
        hash = (hash << 4) + (*str);
        if((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }
        hash &= ~x;
    }
    return hash;
}

/**
 * 初始化hastable 自动分配内存
 */
void hashtableInit(WHASH **table,int initialCapacity){
    *table = (WHASH*)malloc(sizeof(WHASH)*initialCapacity);

    int  i = 0;
    for( i = 0; i < initialCapacity; i++ )
    {
        _HASH(table, i)->size = initialCapacity;
        WllInit(&_HASH(table, i)->data );
    }
}

/**
 * 添加字符串key 字符串值到hastable
 */
void addStrStrToHashTable(WHASH **table, const char *key, char *value ){
    unsigned int hash_code = getHasnCode(key, sizeof(key));
    
    int size  = _HASH(table,0)->size;
    int index = hash_code%size;
    
    WllPushCharChar(&_HASH(table,index)->data,key,value);
}

/**
 * 添加字符串key 数字值到hastable
 */
void addStrDoubleToHashTable(WHASH **table, const char *key, double value ){
    unsigned int hash_code = getHasnCode(key, sizeof(key));
    
    int size  = _HASH(table,0)->size;
    int index = hash_code%size;
    
    WllPushCharDouble(&_HASH(table,index)->data,(void*)key,value);
}

void addStrPVoidToHashTable(WHASH **table, const char *key, void *value ){

}

void addDoubleStrToHashTable(WHASH **table, const double key, char *value ){
    
    int size  = _HASH(table,0)->size;
    int index = (long)key%size;
    
    WllPushDoubleChar(&_HASH(table,index)->data,key,value);
}
void addDoubleDoubleToHashTable(WHASH **table, const double key, double value ){
    int size  = _HASH(table,0)->size;
    int index = (long)key%size;
    
    WllPushDoubleDouble(&_HASH(table,index)->data,key,value);
}
void addDoublePVoidToHashTable(WHASH **table, const double key, void *value ){

}



double getDoubleDataByKeyCharFromHashTable(WHASH **table,const char* key){
    unsigned int hash_code = getHasnCode(key, sizeof(key));
    
    int size  = _HASH(table,0)->size;
    int index = hash_code%size;
    
    WLL *wll = WllFindKey(&_HASH(table,index)->data,(const char*)key);
    if( wll )
        return wll->double_data;
    
    return 0.0;
}
void *getPVoidDataByKeyCharFromHashTable(WHASH **table,const char* key){
    return NULL;
}
char *getCharDataByKeyCharFromHashTable(WHASH **table,const char* key){
    unsigned int hash_code = getHasnCode(key, sizeof(key));
    
    int size  = _HASH(table,0)->size;
    int index = hash_code%size;
    
    WLL *wll = WllFindKey(&_HASH(table,index)->data,(const char*)key);
    if( wll )
        return wll->data;
    return NULL;
}

double getDoubleDataByKeyDoubleFromHashTable(WHASH **table,const double key){
    int size  = _HASH(table,0)->size;
    int index = (long)key%size;
    
    WLL *wll = WllFindDoubleKey(&_HASH(table,index)->data,key);
    if( wll )
        return wll->double_data;
    return 0;
}
void *getPVoidDataByKeyDoubleFromHashTable(WHASH **table,const double key){
    return NULL;
}
char *getCharDataByKeyDoubleFromHashTable(WHASH **table,const double key){
   
    int size  = _HASH(table,0)->size;
    int index = (long)key%size;
    
    WLL *wll = WllFindDoubleKey(&_HASH(table,index)->data,key);
    if( wll )
        return wll->data;
    return NULL;
}

void hashtableFree(WHASH **table){
    int size = _HASH(table,0)->size;
    int i    = 0;
    
    for( i = 0; i < size; i++ ){
        WllFree(&_HASH(table,i)->data);
    }
    
    free((*table));
}

void WhashMap( WHASH **table, WllListMap callback ){
    int size = _HASH(table, 0)->size;
    int i = 0;
    for( i=0;i<size;i++){
        WHASH *node = _HASH(table, i);
        WllMap(&node->data,callback);
       // (*callback)(node->data);
    }
}


void rePush( WHASH **table, WLL *node ){
    
    if( node->key_type == TYPE_CHAR ){
        if( node->data_type == TYPE_CHAR )
            addStrStrToHashTable( table, node->key, node->data );
        if( node->data_type == TYPE_DOUBLE )
            addStrDoubleToHashTable( table, node->key, node->double_data );
    }
    
    if( node->key_type == TYPE_DOUBLE ){
        if( node->data_type == TYPE_CHAR )
            addDoubleStrToHashTable( table, node->double_key, node->data );
        if( node->data_type == TYPE_DOUBLE )
            addDoubleDoubleToHashTable( table, node->double_key, node->double_data );
    }
    
}

void reHash( WHASH **table, int new_size ){
    
    WHASH *new_hash = NULL;
    hashtableInit( &new_hash, new_size );
    
    int size = _HASH(table, 0)->size;
    int i = 0;
    for( i=0;i<size;i++){
        WLL *node = _HASH(table, i)->data;

        while( node->prev!=NULL )
            node = node->prev;
        
        while(node->next != NULL ){
            //处理
            rePush( &new_hash, node );
            node = node->next;
        }
        
        //处理
        rePush( &new_hash, node );
    }
    
    hashtableFree( table );
    *table = new_hash;
    
    size = _HASH(table, 0)->size;
    printf("====>new size==================== == %d\r\n",size);
}

//void HashtableInit(){}
//void HashtableInitFromHashTable(const WHASH *hastable){}
