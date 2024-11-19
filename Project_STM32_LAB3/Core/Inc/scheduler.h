/*
 * scheduler.h
 *
 *  Created on: Nov 19, 2024
 *      Author: phan thanh huy
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

typedef struct{
	void (*pTask)(void);
	uint32_t 	Delay;
	uint32_t 	Period;
	uint8_t		RunMe;
	uint32_t	TaskID;
}sTasks;

#define SCH_MAX_TASKS		40
#define TICH 				10

void SCH_Init(void);
void SCH_Add_Task(void (*pFuncion)(), uint32_t Delay, uint32_t Period);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
void SCH_Delete(uint32_t ID);

#endif /* INC_SCHEDULER_H_ */
