//
//  tree.h
//  tree
//
//  Created by yuyi on 17/2/26.
//  Copyright © 2017年 yuyi. All rights reserved.
//

#ifndef tree_h
#define tree_h

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


/*
树的一些常用操作
->创建树
->销毁树
->清空树
->插入结点
->删除结点
->获取结点
->获取根结点
->获取树的结点数
->获取树的高度
->获取树的度
树在程序中表现为一种特殊的数据类型
树的操作在程序中的表现为一组函数
 */
typedef struct _treeNode TREENODE;
typedef struct _Tree {
    char *key;
    char *value;
    struct _Tree *parent; //父亲节点 如果父节点为null则说明为根节点
    TREENODE *node;
} WTREE;

typedef struct _treeNode {
    struct _treeNode *next;
    struct _treeNode *prev;
    WTREE *tree;
};


void   wtreeCreate(WTREE **tree, const char *key, char *value);
void   wtreeDestroy(WTREE **tree);
WTREE *wtreeInsert(WTREE **tree, const char *tree_key, char *tree_value);
WTREE *wtreeFind(WTREE **tree, const char *key);
void   printTree(WTREE **tree, int index);

/*void Tree_Clear(Tree* tree);
int Tree_Height(Tree* tree);
int Tree_Count(Tree* tree);
int Tree_Degree(Tree* tree);*/

#endif /* tree_h */
