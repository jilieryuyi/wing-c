//
//  main.c
//  链表
//
//  Created by yuyi on 17/2/25.
//  Copyright © 2017年 yuyi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

//双向链表结构体
typedef  struct _WLL  {
    void *data;
    struct _WLL *next;
    struct _WLL *prev;
} WLL;

typedef void (*WllListMap)(WLL *) ;


//设置链表节点数据
int WllSetData(WLL **node, void *data){
    
    if( !data )
        return 0;
    
    unsigned long size = sizeof(data);
    if( size <= 0 )
        return 0 ;
    
    (*node)->data = malloc(size);
    if( !(*node)->data )
        return 0;
    
    memset((*node)->data,0,size);
    memcpy((*node)->data,data,size);
    
    return 1;
}

//初始化双向链表
void WllInit( WLL **wll,void *data ){
    *wll = (WLL*)malloc(sizeof(WLL));
    (*wll)->next = NULL;
    (*wll)->prev = NULL;
    WllSetData(wll, data);
}

//在最后面追加节点
void WllRPush(WLL **parent, void *data ){
    WLL *wll = NULL;
    WllInit(&wll,data);
    
    WLL *last_node = *parent;
    
    while(last_node->next!=NULL)
        last_node = last_node->next;
    
    last_node->next = wll;
    wll->prev = last_node;
}

//在前面追加节点
void WllLPush(WLL **parent, void *data ){
    WLL *wll = NULL;
    WllInit(&wll,data);
    
    WLL *last_node = *parent;
    
    while(last_node->prev!=NULL)
        last_node = last_node->prev;
    
    last_node->prev = wll;
    wll->next = last_node;
}

//遍历链表
void WllMap(WLL **node, WllListMap callback){
    WLL *current_node1 =*node;
    
    while( current_node1->prev!=NULL )
        current_node1 = current_node1->prev;
    
    while(current_node1->next != NULL ){
        (*callback)(current_node1);
        current_node1 = current_node1->next;
    }
    (*callback)(current_node1);
}


//从链表首部弹出数据
void *WllLpop(WLL **wll){
    
    WLL *current = *wll;
    
    while( current->prev != NULL )
        current = current->prev;
    
    void *data = current->data;
    
    WLL *c = current;
    current = current->next;
    
    current->prev = NULL;
    
    free(c);
    
    return data;
}

//从链表尾部弹出数据
void *WllRpop(WLL **wll){
    WLL *current = *wll;
    while( current->next != NULL )
    {
        current = current->next;
    }
    
    void *data = current->data;
    WLL *prev = current->prev;
   
    free(current);
    prev->next = NULL;
    return data;
    
}

//获取指定位置的元素
void *WllGet(WLL **wll,int index){

    WLL *current = *wll;
    
    while( current->prev != NULL )
        current = current->prev;
    
    int count = 0;
    if( index == count )
        return current->data;
    
    while( current->next != NULL ){
        current = current->next;
        count++;
        if( index == count )
            return current->data;
    }
    
    return NULL;
}

//释放链表
void WllFree(WLL **wll){
    WLL *prev = (*wll)->prev;
    WLL *next = *wll;
    
    
    while( next->next != NULL ){
        WLL *p = next->next;
        
         printf("释放内存next==>%s\r\n",next->data);
        
        if( next->data )
            free(next->data);
        
        free(next);
       
        next = p;
    }
    
    printf("释放内存next==>%s\r\n",next->data);
    if( next->data )
        free(next->data);
    free(next);
    
    if( prev ){
        while(prev->prev != NULL){
            WLL *n = prev->prev;
            
            printf("释放内存prev==>%s\r\n",prev->data);
            
            if( prev->data )
                free(prev->data);
            free(prev);
    

            prev = n;
        }
        
        printf("释放内存prev==>%s\r\n",prev->data);

        
        if( prev->data )
            free(prev->data);
        free(prev);
    

    }
    
    
}

//遍历链表回调函数
void wllmap(WLL *node){
    printf("==>%s\r\n",node->data);
}

//测试
int main(int argc, const char * argv[]) {
    
    WLL *wll = NULL;
    
    WllInit(&wll,"123");
    WllRPush(&wll, "456");
    WllRPush(&wll, "4561");
    WllLPush(&wll, "789");
    WllLPush(&wll, "7891");

    
    WllMap(&wll, &wllmap);
    
    printf("\r\n==============================\r\n");
   
    char *data = WllLpop(&wll);
    printf("lpop==>%s\r\n",data);
    
     WllMap(&wll, &wllmap);
    
    
    printf("\r\n==============================\r\n");
    
    char *data1 = WllRpop(&wll);
    printf("rpop==>%s\r\n",data1);
    
    WllMap(&wll, &wllmap);
    
    
    
    WllFree(&wll);
    
    return 0;
}
