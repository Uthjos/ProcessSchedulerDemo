//
// Created by owner on 4/29/2026.
//

#ifndef PROCESSSCHEDULERDEMO_NODE_H
#define PROCESSSCHEDULERDEMO_NODE_H
#include "process.h"
typedef struct pNode {
    struct process data;
    struct pNode *next;
}pNode;
#endif //PROCESSSCHEDULERDEMO_NODE_H