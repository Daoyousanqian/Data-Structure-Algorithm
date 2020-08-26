#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 10
#define FALSE 0
#define TRUE 1
typedef int Status;
typedef int ElemType;

// Here shows the linear queue with limited number 
// and there two pointers, one is front and one is rear
// rear is the tail, and front is the head. 
// rear could be in front of head. 



typedef struct
{
	ElemType data[MAXSIZE];
	int front;
	int rear;
	
}SQueue, *SQueueptr;


Status InitQueue(SQueue *Q1)
{
	Q1->front = 0;
	Q1->rear =0; 
	return TRUE;
}

int QueueLength(SQueue Q)
{
	return (Q.rear-Q.front + MAXSIZE)%MAXSIZE;
}

Status EnterQueue(SQueue *Q, ElemType e)
{
	if ((Q->rear+1)%MAXSIZE == Q->front)
		return FALSE;
	Q->data[Q->rear] = e;
	
	// if the it is the last one then 
	// will continue to the front of the queue
	Q->rear = (Q->rear +1)%MAXSIZE;
	return TRUE;
}


// put the queue value into the e;
Status DeQueue(SQueue *Q, ElemType *e)
{
	// if the queue is empty 
	// then return error
	if(Q->front == Q->rear)
		return FALSE;
	
	// queue should remove from front
	*e = Q->data[Q->front];
	Q-> front = (Q->front + 1)%MAXSIZE;
	
	return TRUE;
}


// here is to test the array queue 
void test01()
{
	// declare one struct
	SQueue bank_Waiting;
	
	//declare the struct waitinglist pointer
	//SQueueptr bank_WaitList;
	// need input the pointer of Queue;
	
	SQueue *pt = &bank_Waiting;
	
	InitQueue(&bank_Waiting);
	//InitQueue(bank_WaitList);
	
	EnterQueue(&bank_Waiting, 10);
	//EnterQueue(bank_WaitList, 55);
	printf("the data in %d\n", bank_Waiting.rear);
	//printf("the data in %d\n", bank_WaitList->rear);
}

// here we introduce the linked queue 
// it has the single direction 
// from head to tail

// here is to declare the 
typedef struct QNode
{
	ElemType data;
	struct QNode *next;
	
}QNode, *QNodeptr;

// declare the linked queue 


// this struct is used to maintain the 
// pointers in the Queue;
typedef struct
{
	// declare the head and tail;
	QNodeptr front, rear;
	
}LinkedQueue, *LinkedQueueptr;

Status InitLinkedQueue(LinkedQueue *LinkedQ)
{
	QNodeptr HeadNode = (QNodeptr) malloc(sizeof(QNode));
	if(HeadNode == NULL)
		return FALSE;
	//printf("the address is %p", HeadNode);
	LinkedQ->front = HeadNode;
	LinkedQ->rear = HeadNode;
	HeadNode->data = 888;
	return TRUE;
}
// the funtion to enter the queue
Status EnterLinkedQueue(LinkedQueue *LinkedQ, ElemType e)
{
	// memory allocation for the new node
	QNodeptr newQueueNode = (QNodeptr) malloc(sizeof(QNode));
	if(newQueueNode == NULL)
		return FALSE;
	newQueueNode->data = e;
	
	// linked the nodes
	LinkedQ->rear->next = newQueueNode;
	LinkedQ->rear = newQueueNode;
	
	return TRUE;
}

// the function to be out of queue
// start from the header of the queue
Status DeLinkedQueue(LinkedQueue *LinkedQ, ElemType *eLinkedQueue)
{
	QNodeptr p;
	// if the queue is empty;
	if(LinkedQ->front == LinkedQ->rear)
	{
		printf("it is empty\n");
		return FALSE;

	}
	*eLinkedQueue = LinkedQ->front->next->data;
	p =  LinkedQ->front->next; 
	LinkedQ->front->next = p->next;
	
	//if the rear is the only one 
	if(LinkedQ-> rear == p )
		LinkedQ->rear = LinkedQ->front;
	
	free(p);
	return TRUE;
}

// this function is used to test the operation on linked queue
void test02()
{
	ElemType number_Out;
	LinkedQueue WaitingQueue1; 
	//
	//InitLinkedQueue(&WaitingQueue1);
	InitLinkedQueue(&WaitingQueue1);
	EnterLinkedQueue(&WaitingQueue1,10);
	EnterLinkedQueue(&WaitingQueue1,100);
	printf("the queue 1 is %d\n", (WaitingQueue1.front)->next->next->data);
	DeLinkedQueue(&WaitingQueue1,&number_Out);
	printf("the queue 1 is %d\n", (WaitingQueue1.front)->next->data);
	printf("the number out of queue is %d\n", number_Out);
	DeLinkedQueue(&WaitingQueue1,&number_Out);
	DeLinkedQueue(&WaitingQueue1,&number_Out);
	
}

int main()

{
	//test01();
	test02();
	return TRUE;
	
}
