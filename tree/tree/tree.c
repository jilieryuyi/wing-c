//
//  tree.c
//  tree
//
//  Created by yuyi on 17/2/26.
//  Copyright © 2017年 yuyi. All rights reserved.
//

#include "tree.h"

void wtreeCreate(WTREE **tree,const char *key, char *value){
    *tree = (WTREE *)malloc(sizeof(WTREE));
    memset(*tree,0,sizeof(WTREE));
    
    (*tree)->parent = NULL;
    (*tree)->node   = NULL;
    (*tree)->key    = (char*)malloc(sizeof(key));
    (*tree)->value  = (char*)malloc(sizeof(value));
    
    memset((*tree)->key, 0, sizeof(key));
    memcpy((*tree)->key, key, sizeof(key));
    
    memset((*tree)->value, 0, sizeof(value));
    memcpy((*tree)->value, value, sizeof(value));
    
}

//插入节点 根据root 和 key 找到目标节点 然后插入节点
WTREE *wtreeInsert(WTREE **tree, const char *tree_key, char *tree_value){
    
    WTREE *new_tree    = NULL;
    
    //创建一个新的节点
    wtreeCreate(&new_tree, tree_key, tree_value);
    new_tree->parent = *tree;
    
    TREENODE *node = (TREENODE*)malloc(sizeof(TREENODE));
    node->next = NULL;
    node->prev = NULL;
    node->tree = new_tree;
    
    TREENODE *last_node = (*tree)->node;
    
    //创建根节点
    if ((*tree)->node == NULL) {
        (*tree)->node = node;
        (*tree)->node->next = NULL;
        (*tree)->node->prev = NULL;
    }
    else {
        
        while (last_node->next != NULL )
            last_node = last_node->next;
        
        //追加节点
        last_node->next = node;
        node->prev = last_node;
    }
    return new_tree;
}


//根据key查找节点
WTREE *wtreeFind(WTREE **root_tree, const char *key){
    
    if (strcmp((*root_tree)->key, key) == 0)
        return *root_tree;
    
    WTREE *current_tree = *root_tree;
    WTREE *target       = NULL;
    
    TREENODE *current_node = current_tree->node;
    if (current_node == NULL)
        return NULL;
    
    while (current_node != NULL){
        while (current_node->next != NULL) {
           // printf("1find====%s\r\n",current_node->tree->key);
            target = wtreeFind(&current_node->tree, key);
            if (target != NULL)
                return target;
            current_node = current_node->next;
        }
        //printf("2find====%s\r\n",current_node->tree->key);
        target = wtreeFind(&current_node->tree, key);
        if (target != NULL)
            return target;
        else
            break;
    }
    
    return NULL;
}

void printTree(WTREE **root_tree, int index) {
   
    
    WTREE *current_tree    = *root_tree;
    WTREE *target          = NULL;
    TREENODE *current_node = current_tree->node;


    printf("%s=",(*root_tree)->key);
    printf("%s\r\n",(*root_tree)->value);
    
    while (current_node != NULL) {
        while (current_node->next != NULL) {
            printTree(&current_node->tree, index+6);
            
            current_node = current_node->next;
            
            printf("%s=",current_node->tree->key);
            
             printf("%s\r\n",current_node->tree->value);
        }
        printTree(&current_node->tree, index+6);
        if(current_node->next==NULL)break;
        else
            index = index-6;
    
    
    printf("%s=",current_node->tree->key);
    

    printf("%s\r\n",current_node->tree->value);
    }
    
    

}

//销毁树
void wtreeDestroy(WTREE **tree){
    free(*tree);
}
