/*
 *	File: kanban.c
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Main project file.
*/

/*** Include project header file ***/
#include "kanban.h"

/* Master logic: starts up, reads a command key and sends it to triage */
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

	while ((cmd = getchar()) != QUIT_CMD && cmd != EOF) {
		if (!triage(&state, cmd)) {
			return RETCODE_UNKNOWN_CMD;
		}
	}
	return RETCODE_OK;
}

/* Call the appropriate function for a command. Returns whether it succeeded. */
int triage(State *state, char cmd) /* #lizard forgives long function TODO: remove this */
{
	switch (cmd) {
	case TASK_CMD:
		cmdTask(state);
		break;
	case LIST_CMD:
		cmdList(state);
		break;
	case STEP_CMD:
		cmdStep(state);
		break;
	case USER_CMD:
		cmdUser(state);
		break;
	case MOVE_CMD:
		cmdMove(state);
		break;
	case TINA_CMD: /* Tasks IN Activity */
		cmdTina(state);
		break;
	case ACTV_CMD: /* Activity */
		cmdActv(state);
		break;
	default: /* Unknown command */
		return 0;
	}
	return 1;
}