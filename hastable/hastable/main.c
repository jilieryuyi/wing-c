//
//  main.c
//  hastable
//
//  Created by yuyi on 17/2/25.
//  Copyright © 2017年 yuyi. All rights reserved.
//

#include <stdio.h>
#include "list.h"
#include "hash.h"


void hashMap(WLL *node){
   
    if( node->key_type == TYPE_DOUBLE )
        printf("%f",node->double_key);
    
    
    if( node->key_type == TYPE_CHAR )
        printf("%s",node->key);
    
    if( node->data_type == TYPE_DOUBLE )
        printf("====>%f\r\n",node->double_data);
    
    if( node->data_type == TYPE_CHAR )
        printf("====>%s\r\n",node->data);
    
}
int main(int argc, const char * argv[]) {
    
    //声明hastable
    WHASH *table = NULL;
    //初始化容量为8
    hashtableInit(&table, 8);
   
    //网table中添加变量
    addStrStrToHashTable(&table, "a", "abc");
    
    //测试覆盖
    addStrStrToHashTable(&table, "a", "abc1");
    
    addStrDoubleToHashTable(&table, "d1", (double)(123) );
    addStrDoubleToHashTable(&table, "d1", (double)(123456) );
    

    char *data = getCharDataByKeyCharFromHashTable( &table, "a" );
    printf("从hastable中获取%s的值=%s\r\n","a",data);
    
    double d1 = (double)getDoubleDataByKeyCharFromHashTable( &table, "d1" );
    printf("从hastable中获取d1的值=%f\r\n",d1);
    
    addDoubleStrToHashTable(&table, 1, "hahahahah");
    char *s1 = getCharDataByKeyDoubleFromHashTable(&table, 1);
    printf("从hastable中获取 1 的值=%s\r\n", s1 );
    
    addDoubleDoubleToHashTable(&table, 1, 1 );
    double s2 = getDoubleDataByKeyDoubleFromHashTable(&table, 1);
    printf("从hastable中获取 1 的值=%f\r\n", s2 );
    
    s1 = getCharDataByKeyDoubleFromHashTable(&table, 1);
    printf("从hastable中获取 1 的值=%s（被覆盖了所以为null）\r\n", s1 );
    
    
    addDoubleDoubleToHashTable(&table, 2, 1222 );
    addStrStrToHashTable(&table, "hhh", "heiheiheihei");
    WhashMap(&table, &hashMap);
    
    reHash(&table, 16);
    
    printf("\r\n\r\n==========================================\r\n\r\n");
    
    data = getCharDataByKeyCharFromHashTable( &table, "a" );
    printf("从hastable中获取%s的值=%s\r\n","a",data);
    
     d1 = (double)getDoubleDataByKeyCharFromHashTable( &table, "d1" );
    printf("从hastable中获取d1的值=%f\r\n",d1);
    
    addDoubleStrToHashTable(&table, 1, "hahahahah");
     s1 = getCharDataByKeyDoubleFromHashTable(&table, 1);
    printf("从hastable中获取 1 的值=%s\r\n", s1 );
    
    addDoubleDoubleToHashTable(&table, 1, 1 );
     s2 = getDoubleDataByKeyDoubleFromHashTable(&table, 1);
    printf("从hastable中获取 1 的值=%f\r\n", s2 );
    
    s1 = getCharDataByKeyDoubleFromHashTable(&table, 1);
    printf("从hastable中获取 1 的值=%s（被覆盖了所以为null）\r\n", s1 );
    
    
    addDoubleDoubleToHashTable(&table, 2, 1222 );
    addStrStrToHashTable(&table, "hhh", "heiheiheihei");
    WhashMap(&table, &hashMap);
    
    hashtableFree(&table);
    return 0;
}
