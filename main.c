#include <stdio.h>
#include "process.h"

#define nProcess 10//size of process queue

//circular array of size nProcess
struct process processQueue[nProcess];
int front = 0;
int rear = 0;

//pre-declare queue functions
bool pushProcess(struct process p);
bool deQueueProcess();



int main(void) {



	printf("Hello, World!\n");
	return 0;
}

bool pushProcess(struct process p) {
	processQueue[rear++] = p;
	return true;
}

void *popProcess() {
	if (front == rear) {
		return NULL;//queue is empty
	}
	return &processQueue[front++];
}