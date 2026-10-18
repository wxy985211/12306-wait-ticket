#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//候补订单结构体
typedef struct Order{
    int id;             //订单号
    char name[20];      //乘客姓名
    struct Order *next;
}Order;

//队列结构体（链表实现）
typedef struct Queue{
    Order *front;
    Order *rear;
}Queue;

//初始化队列
void InitQueue(Queue *q){
    q->front = q->rear = NULL;
}

//入队：添加候补订单
int EnQueue(Queue *q, int id, char *name){
    Order *newNode = (Order*)malloc(sizeof(Order));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->next = NULL;

    if(q->rear == NULL){
        q->front = q->rear = newNode;
    }else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
    return 1;
}

//出队：抢到票，处理排在最前面的人
int DeQueue(Queue *q, Order *out){
    if(q->front == NULL){
        printf("候补队列为空！\n");
        return 0;
    }
    Order *p = q->front;
    *out = *p;
    q->front = q->front->next;
    if(q->front == NULL){
        q->rear = NULL;
    }
    free(p);
    return 1;
}

//遍历打印所有候补订单
void PrintQueue(Queue *q){
    Order *p = q->front;
    if(p == NULL){
        printf("当前候补队列无订单\n");
        return;
    }
    printf("=====候补购票名单=====\n");
    while(p != NULL){
        printf("订单号：%d，乘客：%s\n",p->id, p->name);
        p = p->next;
    }
    printf("======================\n");
}

int main(){
    Queue q;
    InitQueue(&q);
    Order temp;

    //添加候补订单
    EnQueue(&q,1001,"张三");
    EnQueue(&q,1002,"李四");
    EnQueue(&q,1003,"王五");

    printf("添加候补订单后：\n");
    PrintQueue(&q);

    //有票放出，处理第一位候补用户
    if(DeQueue(&q,&temp)){
        printf("\n抢到车票：订单%d，乘客%s\n",temp.id,temp.name);
    }

    printf("\n处理完之后候补队列：\n");
    PrintQueue(&q);

    return 0;
}
