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

/*** Include project header files ***/
#include "commands.h"
#include "constants.h"

int main()
{
	Task tasks[MAX_TASKS] = {0};
	User users[MAX_USERS] = {0};

	Activity todo = {"TO DO"}, inprogress = {"IN PROGRESS"}, done = {"DONE"};
	Activity activities[MAX_ACTIVITIES] = {0};

	State state;
	char cmd;

	activities[0] = todo;
	activities[1] = inprogress;
	activities[2] = done;

	state.activities = activities; /* cannot just assign arrays! */
	state.tasks = tasks;
	state.users = users;

	while ((cmd = getchar()) != QUIT_CMD) {
		switch (cmd) {
		case TASK_CMD:
			task(state);
			break;
		case LIST_CMD:
			list(state);
			break;
		case STEP_CMD:
			step(state);
			break;
		case USER_CMD:
			user(state);
			break;
		case MOVE_CMD:
			move(state);
			break;
		case TINA_CMD: /* Tasks IN Activity */
			tina(state);
			break;
		case ACTV_CMD: /* Activity */
			actv(state);
			break;
		default: /* Unrecognized command */
			return -1;
		}
	}
	return 0;
}