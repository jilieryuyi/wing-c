//
//  main.c
//  tree
//
//  Created by yuyi on 17/2/26.
//  Copyright © 2017年 yuyi. All rights reserved.
//

#include <stdio.h>
#include "tree.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, Trees!\n");
    
    WTREE *root_tree = NULL;
    
    wtreeCreate(&root_tree,"root","01111");
    
    printf("%s=>%s\r\n",root_tree->key,root_tree->value);
    
    WTREE *target = wtreeFind(&root_tree, "root");
    
    if (target != NULL) {
        WTREE *node   = wtreeInsert(&target, "1", "1-value");
        
        if (node != NULL)
            printf("%s=>%s\r\n",node->key,node->value);
        node = wtreeInsert(&target, "2", "2-value");
        
        if (node != NULL)
            printf("%s=>%s\r\n",node->key,node->value);
        node = wtreeInsert(&target, "3", "3-value");
        
        if (node != NULL)
            printf("%s=>%s\r\n",node->key,node->value);
    
        
        
        target = wtreeFind(&root_tree, "1");
        printf("target === %s=>%s\r\n",target->key,target->value);
        
        target = wtreeFind(&root_tree, "2");
        printf("target === %s=>%s\r\n",target->key,target->value);
       
        target = wtreeFind(&root_tree, "3");
        printf("target === %s=>%s\r\n",target->key,target->value);
        
        
        wtreeInsert(&target, "33", "33-valueeee");
        target = wtreeFind(&root_tree, "33");
        printf("target === %s=>%s\r\n",target->key,target->value);
        
        
        wtreeInsert(&target, "333", "333-value");
        target = wtreeFind(&root_tree, "333");
        printf("target === %s=>%s\r\n",target->key,target->value);
        /*
        target = wtreeFind(&root_tree, "1");
        
        node = wtreeInsert(&target, "11", "11-value");
        if (node != NULL)
            printf("%s=>%s\r\n",node->key,node->value);
        
        target = wtreeFind(&root_tree, "11");
        printf("target === %s=>%s\r\n",target->key,target->value);*/

    }
    
    printTree(&root_tree, 1);
    
    wtreeDestroy(&root_tree);
    return 0;
}
