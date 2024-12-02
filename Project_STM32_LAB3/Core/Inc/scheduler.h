/*
 * scheduler.h
 *
 *  Created on: Nov 19, 2024
 *      Author: phan thanh huy
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct{
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint32_t RunMe;
	uint32_t TaskID;
} sTask;

struct Node{
	sTask data;
	struct Node *next;
};

#define TICH	10

struct Node *createNode(sTask data);
void AddTask(struct Node **head, sTask data);
void DeleteTaskID(struct Node **head, uint32_t taskID);
void DeleteTask(struct Node **head);

void SCH_Init();
void SCH_Add_Task(void (*pTask)(), uint32_t Delay, uint32_t Period);
void SCH_Dispatch_Tasks(void);
void SCH_Update(void);
void SCH_Delete_Task(uint32_t taskID);

#endif /* INC_SCHEDULER_H_ */
