/*
 *	File: kanban.c
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Main project file.
*/

/*** Include standard libraries ***/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*** Include project header file ***/
#include "kanban.h"

int main()
{

	Activity todo = {"TO DO"}, inprogress = {"IN PROGRESS"}, done = {"DONE"};

	State state;
	char cmd;

	state.activities[0] = todo;
	state.activities[1] = inprogress;
	state.activities[2] = done; /* cannot just assign arrays! passear variavel size ao lado */
	state.activitiesSize = 3;

	while ((cmd = getchar()) != QUIT_CMD) {
		switch (cmd) {
		case TASK_CMD:
			task(&state);
			break;
		case LIST_CMD:
			list(&state);
			break;
		case STEP_CMD:
			step(&state);
			break;
		case USER_CMD:
			user(&state);
			break;
		case MOVE_CMD:
			move(&state);
			break;
		case TINA_CMD: /* Tasks IN Activity */
			tina(&state);
			break;
		case ACTV_CMD: /* Activity */
			actv(&state);
			break;
		default: /* Unrecognized command */
			return -1;
		}
	}
	return 0;
}