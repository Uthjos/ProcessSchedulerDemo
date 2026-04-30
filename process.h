//
// Created by Owner on 4/24/2026.
//

#ifndef PROCESSSCHEDULERDEMO_PROCESS_H
#define PROCESSSCHEDULERDEMO_PROCESS_H

//define for state
#define FREE 0
#define READY 1
#define RUNNING 2

struct process {
	int pID;
	char name[32];
	int pState;
	float execTime;
};

#endif //PROCESSSCHEDULERDEMO_PROCESS_H