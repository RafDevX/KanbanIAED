/*
 *	File: kanban.c
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Main project file.
*/

/*** Include project header file ***/
#include "kanban.h"

int main()
{

	Activity todo = {DEFAULT_ACTV_TODO},
			 inprogress = {DEFAULT_ACTV_IPRG},
			 done = {DEFAULT_ACTV_DONE};
	State state;
	char cmd;

	state.activities[0] = todo;
	state.activities[1] = inprogress;
	state.activities[2] = done;
	state.activitiesSize = 3;
	state.usersSize = 0;
	state.tasksSize = 0;
	state.time = INITIAL_TIME;

	while ((cmd = getchar()) != QUIT_CMD) {
		switch (cmd) {
		case TASK_CMD:
			cmdTask(&state);
			break;
		case LIST_CMD:
			cmdList(&state);
			break;
		case STEP_CMD:
			cmdStep(&state);
			break;
		case USER_CMD:
			cmdUser(&state);
			break;
		case MOVE_CMD:
			cmdMove(&state);
			break;
		case TINA_CMD: /* Tasks IN Activity */
			cmdTina(&state);
			break;
		case ACTV_CMD: /* Activity */
			cmdActv(&state);
			break;
		default: /* Unrecognized command */
			return -1;
		}
	}
	return 0;
}