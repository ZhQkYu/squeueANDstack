#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bucketstack.h"

// 初始化栈
void initStack (int bucketSize, Stack **stack){
    // 申请栈空间
    *stack = (Stack*)malloc(sizeof(Stack));
    // 设置每个桶的大小
    (*stack)->bucketSize = bucketSize;
    // 初始化栈顶的桶的节点
    (*stack)->firstBucket = NULL;
    // 初始化栈顶元素的位置
    (*stack)->topElt = -1;
}

// 判断栈是否为空
bool isEmpty (const Stack *stack){
    // 如果栈顶的桶的节点为空，则栈为空
    return stack->firstBucket == NULL;
}

// 入栈操作
void push (char* val, Stack *stack){
    // 如果栈顶的桶的节点为空，或者栈顶的这个桶已经满了，则需要新建一个桶
    if (stack->topElt == stack->bucketSize - 1 || isEmpty(stack)){
        // 申请新的桶空间
        struct NodeBucket *newBucket = (struct NodeBucket*)malloc(sizeof(struct NodeBucket));
        // 将新的桶插入到栈顶
        newBucket->next = stack->firstBucket;
        // 更新栈顶的桶的节点
        stack->firstBucket = newBucket;
        // 更新栈顶元素的位置
        stack->topElt = -1;
        // 申请新存放元素的空间
        stack->firstBucket->val = (char**)malloc(sizeof(char*)*stack->bucketSize);
    }
    // 申请新的字符串空间
    char *newString = (char*)malloc(sizeof(char)*strlen(val) + 1);
    // 将字符串复制到新的空间
    strcpy(newString, val);
    // 将新的字符串入栈
    stack->firstBucket->val[++(stack->topElt)] = newString;
}

// 出栈
void pop(Stack *stack){
    // 如果栈为空，则直接返回
    assert (!isEmpty(stack));
    // 释放栈顶元素的空间
    free(stack->firstBucket->val[(stack->topElt)--]);
    // 如果栈顶的桶已经空了，则需要删除这个桶
    if (stack->topElt == -1){
        // 临时保存栈顶的桶的节点
        struct NodeBucket *temp = stack->firstBucket;
        // 更新栈顶的桶的节点
        stack->firstBucket = stack->firstBucket->next;
        // 释放栈顶的存放元素的空间
        free(temp->val);
        // 释放栈顶的桶的节点
        free(temp);
        // 更新栈顶元素的位置
        stack->topElt = stack->bucketSize - 1;
    }
}

// 获取栈的大小
int size (const Stack *stack){
    // 如果栈为空，则返回0
    if (isEmpty(stack)) return 0;
    // 临时保存栈顶的桶的节点
    struct NodeBucket *temp = stack->firstBucket;
    // 计数器
    int count = 0;
    // 遍历栈中的所有桶
    while (temp->next != NULL){
        // 计数器加1
        count += 1;
        // 更新临时保存的栈顶的桶的节点
        temp = temp->next;
    }
    // 返回栈的大小
    // 栈中满的桶的节点的个数*每个桶的大小 + 栈顶元素的位置 + 1
    return count*stack->bucketSize + stack->topElt + 1;
}

// 获取栈顶元素
char* top (const Stack *stack){
    // 如果栈为空，则直接返回
    assert (!isEmpty(stack));
    // 返回栈顶元素
    return stack->firstBucket->val[stack->topElt];
}

// 交换栈顶的两个元素
void swap (Stack *stack){
    // 如果栈为空或者栈中只有一个元素，则直接返回
    assert(size(stack) >= 2);
    // 交换栈顶的两个元素
    // 如果栈顶的桶中有两个元素，则直接交换
    // 具体来看就是当前元素的下标-1 依然在当前桶中，那么直接交换
    if (stack->topElt-1 >= 0){
        // 交换栈顶的两个元素
        // 临时保存栈顶元素的值
        char *temp = stack->firstBucket->val[stack->topElt];
        // 交换栈顶的两个元素
        stack->firstBucket->val[stack->topElt] = stack->firstBucket->val[stack->topElt-1];
        // 交换栈顶的两个元素
        stack->firstBucket->val[stack->topElt-1] = temp;
    }
    else{
        // 否则，需要将栈顶的元素和下一个桶的最后一个元素交换
        // 临时保存栈顶元素的值
        char *temp = stack->firstBucket->val[stack->topElt];
        // 将下一个桶的最后一个元素赋值给栈顶的元素
        stack->firstBucket->val[stack->topElt] = stack->firstBucket->next->val[stack->bucketSize-1];
        // 将栈顶的元素赋值给下一个桶的最后一个元素
        stack->firstBucket->next->val[stack->bucketSize-1] = temp;
    }
}

// 打印栈中的元素
void print (const Stack *stack){
    printf("stack is:\n");
    // 初始化临时保存栈顶的桶的节点
    struct NodeBucket *temp = stack->firstBucket;
    // 遍历栈中的所有桶
    while (temp != NULL){
        // 如果当前桶是栈顶的桶，则只需要从栈顶元素的位置开始遍历即可
        if (temp == stack->firstBucket){
            // 遍历栈顶的桶中的所有元素
            for (int i = stack->topElt; i >= 0; i--){
                // 打印栈顶的桶中的所有元素
                printf("\t%s\n", temp->val[i]);
            }
        }
        // 否则，需要遍历当前桶中的所有元素
        else{
            // 计数器从桶的大小-1开始
            for (int i = stack->bucketSize-1; i >= 0; i--){
                printf("\t%s\n", temp->val[i]);
            }
        }
        // 迭代临时保存的栈顶的桶的节点
        temp = temp->next;
    }
}

// 清空栈
void clear(Stack *stack){
    // 如果栈为空，则直接返回
    while (!isEmpty(stack)){
        // 执行出栈操作即可
        // 出栈操作已经实现了释放空间的操作
        pop(stack);
    }
}

// 销毁栈
void destroyStack(Stack **stack){
    // 先清空栈
    clear(*stack);
    // 释放栈的空间
    free(*stack);
    // 将栈的指针置为NULL
    *stack = NULL;
}