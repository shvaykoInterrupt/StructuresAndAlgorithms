#include "stdlib.h"
#include "iostream"

// queue on two stacks

#define MAX_STACK_SIZE 16

typedef struct Stack
{
	int stackTop = 0;
	int data[MAX_STACK_SIZE];
}Stack;

typedef struct Queue
{
	Stack inputStack;
	Stack outputStack;
	int count;
}Queue;


void push(Stack *stack,int value)
{
	stack->data[stack->stackTop++] = value;
}

int pop(Stack* stack)
{
	stack->stackTop--;
	return stack->data[stack->stackTop];
}

bool isEmpty(Stack *stack)
{
	return stack->stackTop ? false : true;
}

void enqueue(Queue *queue, int value)
{
	if (queue->inputStack.stackTop == MAX_STACK_SIZE)
	{
		// cannot push more
		exit(1);
	}
	push(&queue->inputStack, value);
	queue->count++;
}

bool isQueueEmpty(Queue* queue)
{
	return queue->count ? false : true;
}

int dequeue(Queue *queue)
{
	int result = 0;
	if (isQueueEmpty(queue))
	{
		fprintf(stdout, "queue empty\n");
		return INT_MIN;
	}
	if(isEmpty(&queue->outputStack))
	{
		// from is to os
		while (!isEmpty(&queue->inputStack))
		{
			push(&queue->outputStack,pop(&queue->inputStack));
		}
		result = pop(&queue->outputStack);
	}
	else
	{
		result =  pop(&queue->outputStack);
	}
	queue->count--;
	return result;
}

void initQueue(Queue *queue)
{
	queue->inputStack = {};
	queue->outputStack = {};
	queue->count = 0;
}

int main(int argc, char**argv)
{
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	initQueue(queue);

	enqueue(queue,5);
	enqueue(queue,8);
	enqueue(queue,9);

	fprintf(stdout,"Element :%d\n", dequeue(queue));
	fprintf(stdout,"Element :%d\n", dequeue(queue));
	fprintf(stdout,"Element :%d\n", dequeue(queue));
	fprintf(stdout,"Element :%d\n", dequeue(queue));

	return 0;
}