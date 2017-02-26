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
typedef struct _Tree {} Tree;
typedef struct _TreeNode {} TreeNode;

Tree *Tree_Create();
void Tree_Destroy(Tree* tree);
void Tree_Clear(Tree* tree);
int Tree_Insert(Tree* tree, TreeNode* node, int pos);
TreeNode *Tree_Delete(Tree* tree, int pos);
TreeNode *Tree_Get(Tree* tree, int pos);
TreeNode *Tree_Root(Tree* tree);
int Tree_Height(Tree* tree);
int Tree_Count(Tree* tree);
int Tree_Degree(Tree* tree);

#endif /* tree_h */
