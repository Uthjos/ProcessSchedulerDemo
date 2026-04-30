//
// Created by Owner on 4/24/2026.
//

#ifndef PROCESSSCHEDULERDEMO_PROCESS_H
#define PROCESSSCHEDULERDEMO_PROCESS_H

struct process {
	int pID;
	char name[];
	int pState;
	float execTime;
};

#endif //PROCESSSCHEDULERDEMO_PROCESS_H