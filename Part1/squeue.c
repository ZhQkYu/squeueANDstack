#include "squeue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// 初始化一个空的队列
void initSqueue (Squeue ** squeue){
    // 为队列分配内存
    *squeue = (Squeue*)malloc(sizeof(Squeue));
    // 初始化队列的头尾指针
    (*squeue)->first = NULL;
    (*squeue)->last = NULL;
}

// 判空
bool isEmpty (const Squeue *squeue){
    // 如果队列的头指针为空，则队列为空
    if(squeue->first == NULL){
        return true;
    }
    return false;
}

// 向队列头部添加元素
void addFront (Squeue *squeue, char* val){
    // 为新节点分配内存
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));
    // 为新节点的值分配内存
    char* newVal = (char*)malloc(sizeof(char)*strlen(val) + 1);
    // 将val的值复制到newVal中
    strcpy(newVal, val);
    // 将newVal的值赋给新节点
    new->val = newVal;
    // 将新节点的next指针指向原队列的头节点
    new->next = squeue->first;
    // 将新节点的prev指针指向NULL
    new->prev = NULL;
    // 判断原队列是否为空
    if (squeue->first != NULL){
        // 如果不为空，则将原队列的头节点的prev指针指向新节点
        squeue->first->prev = new;
    }
    // 将新节点赋值给队列的头指针
    squeue->first = new;
    // 判断原队列是否为空
    if (squeue->last == NULL){
        // 如果为空，则将新节点赋值给队列的尾指针
        squeue->last = new;
    }
}

// 向队列尾部添加元素
void addBack (Squeue *squeue, char* val){
    // 为新节点分配内存
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));
    // 为新节点的值分配内存
    char* newVal = (char*)malloc(sizeof(char)*strlen(val) + 1);
    // 将val的值复制到newVal中
    strcpy(newVal, val);
    // 将newVal的值赋给新节点
    new->val = newVal;
    // 将新节点的next指针指向NULL
    new->next = NULL;
    // 将新节点的prev指针指向原队列的尾节点
    new->prev = squeue->last;
    // 判断原队列是否为空
    if (squeue->last != NULL){
        // 如果不为空，则将原队列的尾节点的next指针指向新节点
        squeue->last->next = new;
    }
    // 将新节点赋值给队列的尾指针
    squeue->last = new;
    // 判断原队列是否为空
    if (squeue->first == NULL){
        // 如果为空，则将新节点赋值给队列的头指针
        squeue->first = new;
    }
}

// 从队列头部删除元素
void leaveFront (Squeue *squeue){
    // 判断队列是否为空
    assert (!isEmpty(squeue));
    // 保存原队列的头节点
    struct Node* temp = squeue->first;
    // 将原队列的头节点的next指针赋值给队列的头指针
    squeue->first = squeue->first->next;
    // 判断原队列的头节点的next指针是否为空
    if (squeue->first != NULL){
        // 如果不为空，则将原队列的头节点的next指针的prev指针指向NULL
        squeue->first->prev = NULL;
    }
    // 释放原队列的头节点的值的内存
    free(temp->val);
    // 释放原队列的头节点的内存
    free(temp);
    // 判断队列的头指针是否为空
    if (squeue->first == NULL){
        // 如果为空，则将队列的尾指针也赋值为NULL
        squeue->last = NULL;
    }
}

// 返回队列尾部的元素
char* peekBack (const Squeue *squeue){
    // 判断队列是否为空
    assert (!isEmpty(squeue));
    // 返回队列的尾节点的值
    return squeue->last->val;
}

// 从队列尾部删除元素
// 与从队列头部删除元素类似
void leaveBack (Squeue *squeue){
    assert (!isEmpty(squeue));
    struct Node* temp = squeue->last;
    squeue->last = squeue->last->prev;
    if (squeue->last != NULL){
        squeue->last->next = NULL;
    }
    free(temp->val);
    free(temp);
    if (squeue->last == NULL){
        squeue->first = NULL;
    }
}

// 返回队列头部的元素
// 与返回队列尾部的元素类似
char* peekFront (const Squeue *squeue){
    assert (!isEmpty(squeue));
    return squeue->first->val;
}

// 打印队列
void print (const Squeue *squeue, char direction){
    // 判断方向是否合法
    if (direction != 'f' && direction != 'r'){
        // 如果不合法，则打印错误信息
        fprintf(stderr, "Error, illegal direction %c\n", direction);
        return;
    }else if (direction == 'f'){
        // 如果合法，则根据方向打印队列
        // 如果方向为f，则从头部开始打印
        printf("squeue is:\n");
        // 从头部开始遍历队列
        struct Node* temp = squeue->first;
        // 判断当前节点是否为空
        while (temp != NULL){
            // 如果不为空，则打印当前节点的值
            printf("\t%s\n", temp->val);
            // 将当前节点的next指针赋值给当前节点
            temp = temp->next;
        }
    }else{
        // 如果方向为r，则从尾部开始打印
        printf("squeue is:\n");
        // 从尾部开始遍历队列
        struct Node* temp = squeue->last;
        // 判断当前节点是否为空
        while (temp != NULL){
            // 如果不为空，则打印当前节点的值
            printf("\t%s\n", temp->val);
            // 将当前节点的prev指针赋值给当前节点
            temp = temp->prev;
        }
    }
}

// 清空队列
void nuke (Squeue *squeue){
    // 从头部开始遍历队列
    while (!isEmpty(squeue)){
        // 从头部删除元素
        leaveFront(squeue);
    }
    // 循环退出的条件是队列为空
}

// 检测元素是否大于两个，这个是为了后面的合并操作做准备
bool isGreaterTwo(Squeue *squeue){
    // 计数器
    int count = 0;
    // 从头部开始遍历队列
    struct Node* temp = squeue->first;
    // 判断当前节点是否为空
    while (temp != NULL){
        // 如果不为空，则计数器加一
        count++;
        // 将当前节点的next指针赋值给当前节点
        temp = temp->next;
        // 判断计数器是否大于等于2
        if (count >= 2){
            // 如果大于等于2，则返回true
            return true;
        }
    }
    // 如果循环结束，计数器仍然小于2，则返回false
    return false;
}

// 合并队列头部的两个元素
void mergeFront(Squeue *squeue, char direction ){
    // 判断队列中元素是否大于两个
    assert (isGreaterTwo(squeue));
    // 判断方向是否合法
    if (direction != 'f' && direction != 'r'){
        // 如果不合法，则打印错误信息
        fprintf(stderr, "Error, illegal direction %c\n", direction);
        return;
    }else{
        // 如果合法，则合并队列头部的两个元素
        // 将原队列的头节点的next指针赋值给临时变量
        struct Node* temp = squeue->first->next;
        // 为新的字符串分配内存
        // 长度为原队列头节点的值的长度加上原队列头节点的next指针指向的节点的值的长度加一
        // 加一是为了存放字符串结束符'\0'
        char* newString = (char*)malloc(sizeof(char) * (strlen(squeue->first->val) + strlen(temp->val) + 1));
        // 如果方向为f，则将原队列头节点的值和原队列头节点的next指针指向的节点的值拼接起来
        if (direction == 'f'){
            // 将原队列头节点的值拷贝到新的字符串中
            strcpy(newString, squeue->first->val);
            // 将原队列头节点的next指针指向的节点的值拼接到新的字符串中
            strcat(newString, temp->val);
        }else{
            // 如果方向为r，则将原队列头节点的next指针指向的节点的值和原队列头节点的值拼接起来
            // 将原队列头节点的next指针指向的节点的值拷贝到新的字符串中
            strcpy(newString, temp->val);
            // 将原队列头节点的值拼接到新的字符串中
            strcat(newString, squeue->first->val);
        }
        // 释放原队列头节点的值的内存
        free(squeue->first->val);
        // 将新的字符串赋值给原队列头节点的值
        squeue->first->val = newString;
        // 将原队列头节点的next指针指向的节点的next指针赋值给原队列头节点的next指针
        squeue->first->next = temp->next;
        // 如果原队列头节点的next指针指向的节点的next指针不为空
        if (temp->next != NULL){
            // 将原队列头节点的next指针指向的节点的next指针指向的节点的prev指针赋值给原队列头节点的next指针指向的节点的prev指针
            temp->next->prev = squeue->first;
        }else{
            // 如果原队列头节点的next指针指向的节点的next指针为空
            squeue->last = squeue->first;
        }
        // 释放原队列头节点的next指针指向的节点的内存
        free(temp->val);
        // 释放原队列头节点的next指针指向的节点的内存
        free(temp);
    }
}

// 合并队列尾部的两个元素
// 与合并队列头部的两个元素的操作类似
void mergeBack(Squeue *squeue, char direction){
    assert (isGreaterTwo(squeue));
    if (direction != 'f' && direction != 'r'){
        fprintf(stderr, "Error, illegal direction %c\n", direction);
        return;
    }else{
        struct Node* temp = squeue->last->prev;
        char* newString = (char*)malloc(sizeof(char) * (strlen(squeue->last->val) + strlen(temp->val) + 1));
        if (direction == 'f'){
            strcpy(newString, squeue->last->val);
            strcat(newString, temp->val);
        }else{
            strcpy(newString, temp->val);
            strcat(newString, squeue->last->val);
        }
        free(squeue->last->val);
        squeue->last->val = newString;
        squeue->last->prev = temp->prev;
        if (temp->prev != NULL){
            temp->prev->next = squeue->last;
        }else{
            squeue->first = squeue->last;
        }
        free(temp->val);
        free(temp);
    }
}

// 反转队列
void reverse(Squeue *squeue){
    // 申请一个临时变量，指向队列的头节点
    struct Node* begin = squeue->first;
    // 申请一个临时变量，指向队列的尾节点
    struct Node* end = squeue->last;
    // 如果头节点和尾节点不相等，且头节点的prev指针不等于尾节点
    // 如果头节点和尾节点相等，或者头节点的prev指针等于尾节点，则说明已经遍历到了中间节点
    // 如果遍历到了中间节点，则不需要再进行反转
    while (begin != end && begin->prev != end){
        // 将头节点的值赋值给临时变量
        char* temp = begin->val;
        // 将尾节点的值赋值给头节点的值
        begin->val = end->val;
        // 将临时变量的值赋值给尾节点的值
        end->val = temp;
        // 迭代begin
        begin = begin->next;
        // 迭代end
        end = end->prev;
    }
}

// 销毁队列
void destroySqueue(Squeue **squeue){
    // 首先将队列清空，使用上面定义的nuke函数
    nuke(*squeue);
    // 释放队列的内存
    free(*squeue);
    // 将队列指针指向NULL
    *squeue = NULL;
}