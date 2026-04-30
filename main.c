#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "process.h"
#include "node.h"


/* Demonstration program for ICS 462. Project 2, RoundRobin Process Scheduler.
 * Simulates creation of process randomly every 5s
 * enqueues processes
 * pops top processes from queue
 * simulates run time using sleep
 * if processes need more execute than TIME_SLICE, requeue
 * Handles negative iteration numbers
 * Continues to execute even after reaching iterations requested if queue is not empty
 *
 * Joseph Murtha hw4546dw joseph.murtha@my.metrostate.edu
 * 4/29/2026
 *
 */
#define TIME_SLICE 3.0f

//pre-declare queue functions
bool enqueue(struct process p);
struct process dequeue();
bool isEmpty();
bool isFull();



pNode *head = NULL;
pNode *tail = NULL;

int count;
int iterations;
int pidCounter = 0;

//states
const char *getStateString(int state) {
	switch (state) {
		case FREE: return "FREE";
		case READY: return "READY";
		case RUNNING: return "RUNNING";
		default: return "UNKNOWN";
	}
}


int main(void) {
	//prompt user for duration
	//expect 200s
	long int iterations;
	int i;
	do {
		printf("Enter number of loop iterations (n):");
		i = scanf("%ld",&iterations);
		if (i != 1 || iterations <= 0) {
			printf("Invalid input\n");
		}
		char ch = getchar();
	}while (i !=1 || iterations <= 0);


	//create total timer
	clock_t start, end;

	start = clock();

	//Enter main loop
	count = 0;
	srand(time(0));
	while ((count < iterations) | !isEmpty() ) {
		printf("\n [INFO] Iteration %d",count + 1);
		//check if new process

		if (count < iterations) {
			int r = (rand() % 5) + 1;
			//generate random number between 1-5
			printf(" [INFO] Check process Arrival %d%s\n", r, r==5 ? "-> New Process" : "");
			if (r == 5) {
				//5 means new process
				//create new process node and PID
				//enqueue new process node into ready queue

				struct process newProcess;

				newProcess.pID =pidCounter++;
				snprintf(newProcess.name, sizeof(newProcess.name), "PROC%d", newProcess.pID);
				newProcess.pState = READY;
				newProcess.execTime = (float) (rand() % 10 + 1);

				//print out
				printf(" [CREATE] %s PID=%d State=%s ExecuteTime= %.0f s\n",
					newProcess.name, newProcess.pID, getStateString(newProcess.pState), newProcess.execTime);

				//add to queue
				enqueue(newProcess);
				printf(" [PUSH] %s added to ready queue.\n", newProcess.name);

			}
		}
		if (!isEmpty()) {
			/* dequeue process at front
			 * set and display state as Running state= 2
			 * Schedule process -> display process attributes (name, id, remaining time)
			 * simulate process execution (sleep 3s max)
			 * update process remaining exec time (t =t-3)
			 */

			//pop and display
			struct process currentProcess = dequeue();

			currentProcess.pState = RUNNING;
			printf(" [RUNNING] %s  PID=%d  State=%s  Remaining=%.0f s\n",
				   currentProcess.name, currentProcess.pID, getStateString(currentProcess.pState), currentProcess.execTime);

			//check how long we are going to execute
			float timeToRun = currentProcess.execTime <= TIME_SLICE ? currentProcess.execTime : TIME_SLICE;
			printf(" [EXEC] Running for %.0f s ...\n\n",timeToRun);

			sleep((unsigned int) timeToRun);

			//return, update remaining time

			currentProcess.execTime = currentProcess.execTime - timeToRun;

			if (currentProcess.execTime > 0.0f) {//re add to queue if time left
				currentProcess.pState = READY;
				printf(" [PUSH] %s re-queued. Remaining= %.0f s State=%s\n",
					currentProcess.name, currentProcess.execTime, getStateString(currentProcess.pState));
				enqueue(currentProcess);
			}else {//done with p
				currentProcess.pState = FREE;
				printf(" [FREE] %s PID=%d State=%s\n",
					currentProcess.name, currentProcess.pID, getStateString(currentProcess.pState));
				printf(" [INFO] PROCESS COMPLETE: %s",currentProcess.name);
			}


		}else {// queue empty
			printf(" [WAIT]  Queue empty. Sleeping for 1 s.\n");
			sleep(1);
		}

		count++;
		printf("\n");
	}

	end = clock();
	printf(" [INFO] COMPLETE. Total iterations %d Total processes %d Total time %lds.", count, pidCounter,end / 1000);


	return 0;
}


/*allocate node and append to tail
 */
bool enqueue(struct process p) {
	pNode *node = (pNode *)malloc(sizeof(pNode));

	if (node == NULL) {
		printf("malloc failed");
		return false;
	}

	node->data = p;
	node->next = NULL;

	if (tail == NULL) {//empty
		head = node;
		tail = node;
	}else {
		tail->next = node;
		tail = node;
	}

	return true;
}

//pop first process from queue
struct process dequeue() {
	pNode *temp = head;
	struct process p = temp->data;
	head = head->next;
	if (head==NULL) {
		tail = NULL;
	}
	free(temp);
	return p;
}

bool isEmpty() {
	return head == NULL;
}