//
//  list.h
//  hastable
//
//  Created by yuyi on 17/2/25.
//  Copyright © 2017年 yuyi. All rights reserved.
//

#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define TYPE_CHAR 1
#define TYPE_DOUBLE 2

typedef  struct _WLL  {
    int key_type;       //键类型
    char *key;          //键
    double double_key;  //键
    
    int data_type;      //值类型
    
    void *data;         //值
    double double_data; //值
    
    struct _WLL *next;  //指向下一个节点
    struct _WLL *prev;  //指向上一个节点
} WLL;


//遍历链表的回调函数指针
typedef void (*WllListMap)(WLL *) ;


//设置链表节点数据
int WllSetCharCharData(WLL **node, const char *key, char *data);
int WllSetDoubleCharData(WLL **node, const double key, char *data);

//初始化双向链表
void WllInit( WLL **wll );

//追加节点 key存在则覆盖
void WllPushCharChar(WLL **parent, const char *key, void *data );
void WllPushCharDouble(WLL **parent, const char *key, double data );
void WllPushDoubleChar(WLL **parent, const double key, char *data );
void WllPushDoubleDouble(WLL **parent, const double key, double data );

//遍历链表
void WllMap(WLL **node, WllListMap callback);

//查找节点
WLL *WllFindKey(WLL **wll,const char *key );
WLL *WllFindDoubleKey(WLL **wll,const double key );

//从链表首部弹出数据
void *WllLpop(WLL **wll);
//从链表尾部弹出数据
void *WllRpop(WLL **wll);
//获取指定位置的元素
void *WllGet(WLL **wll,int index);
//释放链表
void WllFree(WLL **wll);
//遍历链表回调函数


#endif /* list_h */
