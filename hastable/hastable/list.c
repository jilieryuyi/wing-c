//
//  list.c
//  hastable
//
//  Created by yuyi on 17/2/25.
//  Copyright © 2017年 yuyi. All rights reserved.
//

#include "list.h"



int WllSetCharDoubleData(WLL **node, const char *key, double data){
    
    if( !key )
        return 0;
    
    unsigned long size = 0;
    
    if( (*node)->key )
    {
        free((*node)->key);
        (*node)->key = NULL;
    }
    
    if( (*node)->data )
    {
        free((*node)->data);
        (*node)->data = NULL;
    }
    
    (*node)->data        = NULL;
    (*node)->double_data = data;
    (*node)->key         = NULL;
    
    (*node)->key_type  = TYPE_CHAR;
    (*node)->data_type = TYPE_DOUBLE;
    
    
    size = sizeof(key);
    if( size <= 0 )
        return 0 ;
        
    (*node)->key = malloc(size);
    if( !(*node)->key )
        return 0;
        
    memset((*node)->key,0,size);
    memcpy((*node)->key,key,size);
    
    return 1;
}

int WllSetDoubleCharData(WLL **node, const double key, char *data){
    unsigned long size = 0;
    
    if( (*node)->key )
    {
        free((*node)->key);
        (*node)->key = NULL;
    }
    
    if( (*node)->data )
    {
        free((*node)->data);
        (*node)->data = NULL;
    }
    
    (*node)->data = NULL;
    (*node)->key  = NULL;
    (*node)->double_key = key;
    
    (*node)->key_type  = TYPE_DOUBLE;
    (*node)->data_type = TYPE_CHAR;
    
    if( data )
    {
        
        size = sizeof(data);
        if( size <= 0 )
            return 0 ;
        
        
        
        (*node)->data = malloc(size);
        if( !(*node)->data )
            return 0;
        
        memset((*node)->data,0,size);
        memcpy((*node)->data,data,size);
    }
    
    return 1;
}


int WllSetDoubleDoubleData(WLL **node, double key, double data){
    
    if( (*node)->key )
    {
        free((*node)->key);
        (*node)->key = NULL;
    }
    
    if( (*node)->data )
    {
        free((*node)->data);
        (*node)->data = NULL;
    }
    
    (*node)->data = NULL;
    (*node)->key  = NULL;
    
    (*node)->key_type  = TYPE_DOUBLE;
    (*node)->data_type = TYPE_DOUBLE;
    
    
    (*node)->double_key  = key;
    (*node)->double_data = data;
    
    return 1;
}

//设置链表节点数据
int WllSetCharCharData(WLL **node, const char *key, char *data){
    
    unsigned long size = 0;
    
    if( (*node)->data )
    {
        free((*node)->data);
        (*node)->data = NULL;
    }
    
    if( (*node)->key )
    {
        free((*node)->key);
        (*node)->key = NULL;
    }
    
    (*node)->data = NULL;
    (*node)->key  = NULL;
    
    (*node)->key_type  = TYPE_CHAR;
    (*node)->data_type = TYPE_CHAR;
    
    if( data )
    {
    
        size = sizeof(data);
        if( size <= 0 )
            return 0 ;
        
        
    
        (*node)->data = malloc(size);
        if( !(*node)->data )
            return 0;
    
        memset((*node)->data,0,size);
        memcpy((*node)->data,data,size);
    }
    
    if( key )
    {
        
        size = sizeof(key);
        if( size <= 0 )
            return 0 ;
        
        (*node)->key = malloc(size);
        if( !(*node)->key )
            return 0;
        
        memset((*node)->key,0,size);
        memcpy((*node)->key,key,size);
    }
    
    return 1;
}

//初始化双向链表
void WllInit( WLL **wll ){
    *wll = (WLL*)malloc(sizeof(WLL));
    (*wll)->next = NULL;
    (*wll)->prev = NULL;
    (*wll)->data = NULL;
    (*wll)->key  = NULL;
    (*wll)->key_type   = 0;
    (*wll)->data_type  = 0;
    (*wll)->double_key = 0;
}

//在前面追加节点 存在则覆盖
void WllPushCharChar(WLL **parent, const char *key, void *data ){
    WLL *wll = WllFindKey( parent, key );
    
    if( !wll )
    {
        WllInit(&wll);
    
        WLL *last_node = *parent;
    
        while(last_node->next!=NULL)
            last_node = last_node->next;
    
        last_node->next = wll;
        wll->prev = last_node;
    }
    
    WllSetCharCharData( &wll, key, data);
    
}

void WllPushDoubleDouble(WLL **parent, const double key, double data ){
    WLL *wll = WllFindDoubleKey( parent, key );
    
    if( !wll )
    {
        WllInit(&wll);
        
        WLL *last_node = *parent;
        
        while(last_node->next!=NULL)
            last_node = last_node->next;
        
        last_node->next = wll;
        wll->prev = last_node;
    }
    
    WllSetDoubleDoubleData( &wll, key, data);
}

void WllPushCharDouble(WLL **parent, const char *key, double data ){
    WLL *wll = WllFindKey( parent, key );
    
    if( !wll )
    {
        WllInit(&wll);
        
        WLL *last_node = *parent;
        
        while(last_node->next!=NULL)
            last_node = last_node->next;
        
        last_node->next = wll;
        wll->prev = last_node;
    }
    
    WllSetCharDoubleData( &wll, key, data);
}

void WllPushDoubleChar(WLL **parent, const double key, char *data ){
    WLL *wll = WllFindDoubleKey( parent, key );
    
    if( !wll )
    {
        WllInit(&wll);
        
        WLL *last_node = *parent;
        
        while( last_node->next != NULL )
            last_node = last_node->next;
        
        last_node->next = wll;
        wll->prev = last_node;
    }
    
    WllSetDoubleCharData( &wll, key, data);
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

//查找数字key
WLL *WllFindDoubleKey(WLL **wll,const double key ){
    
    WLL *current = *wll;
    
    if( current->double_key == key )
        return current;
    
    
    while( current->prev != NULL )
    {
        current = current->prev;

        if( current->double_key == key )
            return current;
    }
    if( current->double_key == key )
        return current;
    
    while( current->next != NULL ){
        current = current->next;
        if( current->double_key == key )
            return current;
    }
    
    if( current->double_key == key )
        return current;
    
    return NULL;
}



//查找节点
WLL *WllFindKey(WLL **wll,const char *key ){
    
    WLL *current = *wll;

    if( key == NULL && current->key == NULL )
        return current;
    
    if( key && current->key )
    {
        if( strcmp((char*)key,(char*)current->key) == 0 )
        return current;
    }
    
    
    while( current->prev != NULL )
    {
        current = current->prev;
        if( key && current->key )
        {
            if( strcmp((char*)key,(char*)current->key) == 0 )
                return current;
        }
        
        if( key == NULL && current->key == NULL )
            return current;
    }
    
    if( key && current->key )
    {
        if( strcmp((char*)key,(char*)current->key) == 0 )
            return current;
    }
    
    if( key == NULL && current->key == NULL )
        return current;
    
    
    while( current->next != NULL ){
        current = current->next;
        if( key && current->key )
        {
            if( strcmp((char*)key,(char*)current->key) == 0 )
                return current;
        }
        if( key == NULL && current->key == NULL )
            return current;
    }
    
    if( key && current->key )
    {
        if( strcmp((char*)key,(char*)current->key) == 0 )
            return current;
    }
    
    if( key == NULL && current->key == NULL )
        return current;
    
    return NULL;
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
        {
            free(next->data);
            next->data = NULL;
        }
        printf("释放内存next-key==>%s\r\n",next->key);

        if( next->key )
        {
            free(next->key);
            next->key = NULL;
        }
        
        free(next);
        
        next = p;
    }
    
    
    if( next->data )
    {
        printf("释放内存next==>%s\r\n",next->data);
        free(next->data);
        next->data = NULL;
    }
    

    if( next->key )
    {
        printf("释放内存next-key==>%s\r\n",next->key);
        free(next->key);
        next->key = NULL;
    }
    
    free(next);
    next = NULL;
    
    if( prev ){
        while(prev->prev != NULL){
            WLL *n = prev->prev;
            
            printf("释放内存prev==>%s\r\n",prev->data);
            
            if( prev->data )
            {
                free(prev->data);
                prev->data = NULL;
            }
            
            printf("释放内存prev-key==>%s\r\n",prev->key);
            
            if( prev->key )
            {
                free(prev->key);
                prev->data = NULL;
            }
            free(prev);
            
            prev = n;
        }
        
        printf("释放内存prev==>%s\r\n",prev->data);
        
        
        if( prev->data )
        {
            free(prev->data);
            prev->data = NULL;
        }
        printf("释放内存prev-key==>%s\r\n",prev->key);

        if( prev->key )
        {
            free(prev->key);
            prev->key = NULL;
        }
        free(prev);
        prev = NULL;
        
    }
    
    
}

//遍历链表回调函数
void wllmap(WLL *node){
    printf("==>%s\r\n",node->data);
}

