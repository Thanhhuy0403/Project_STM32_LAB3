/*
 * scheduler.c
 *
 *  Created on: Nov 19, 2024
 *      Author: phan thanh huy
 */

#include "scheduler.h"

// Linked List
struct Node *createNode(sTask data){
	struct Node *newNode = malloc(sizeof(struct Node));
	if(!newNode) return NULL;

	newNode->data.pTask = data.pTask;
	newNode->data.Delay = data.Delay;
	newNode->data.Period = data.Period;
	newNode->data.TaskID = data.TaskID;
	newNode->data.RunMe = data.RunMe;
	newNode->next = NULL;
	return newNode;
}

void AddTask(struct Node **head, sTask data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node *current = *head;

    if (newNode->data.Delay < current->data.Delay) {
        current->data.Delay -= newNode->data.Delay;
        newNode->next = current;
        *head = newNode;
        return;
    }

    newNode->data.Delay -= current->data.Delay;
    while (current->next != NULL && current->next->data.Delay <= newNode->data.Delay) {
        newNode->data.Delay -= current->next->data.Delay;
        current = current->next;
    }

    if (current->next != NULL) {
        current->next->data.Delay -= newNode->data.Delay;
    }
    newNode->next = current->next;
    current->next = newNode;
}


void DeleteTaskID(struct Node **head, uint32_t taskID) {
    struct Node *current = *head;
    struct Node *prev = NULL;

    while (current != NULL && current->data.TaskID != taskID) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return;

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
}

void DeleteTask(struct Node **head){
	if(*head == NULL) return;
	struct Node *current = *head;
	*head = current->next;
	free(current);
}

// Scheduler
static int id = 0;
static struct Node* head = NULL;

void SCH_Init(){
	head = NULL;
	id = 0;
}

void SCH_Add_Task(void (*pTask)(), uint32_t  Delay, uint32_t Period){
	sTask data;
	data.pTask = pTask;
	data.Delay = Delay/TICH;
	data.Period = Period/TICH;
	data.TaskID = id++;
	data.RunMe = 0;
	AddTask(&head, data);
}

void SCH_Dispatch_Tasks(void){
	if(head == NULL){
		return;
	}
	if(head->data.RunMe == 1){
		(*(head->data.pTask))();
		if(head->data.Period == 0){
			DeleteTask(&head);
		}else{
			sTask renewTask;
			renewTask.pTask = head->data.pTask;
			renewTask.Delay = head->data.Period;
			renewTask.Period = head->data.Period;
			renewTask.RunMe = 0;
			renewTask.TaskID = head->data.TaskID;
			DeleteTask(&head);
			AddTask(&head, renewTask);
		}
	}
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

void SCH_Update(void){
	if(head == NULL) return;
	if(head->data.Delay > 0) head->data.Delay--;
	else head->data.RunMe = 1;
}

void SCH_Delete_Task(uint32_t taskID){
	 DeleteTaskID(&head, taskID);
}
