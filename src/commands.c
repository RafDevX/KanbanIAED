/*
 *	File: commands.c
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Handlers for all commands.
*/

/*** Include project header file ***/
#include "kanban.h"

void task(State *state)
{
	int duration, id;
	unsigned int i;
	char desc[MAX_TASK_DESC_SIZE];
	Task new;
	Activity actv;
	readInt(&duration);
	readString(desc, MAX_TASK_DESC_SIZE);

	if (duration <= 0) {
		printf(ERR_INVALID_DURATION);
		return;
	} else if (state->tasksSize + 1 >= MAX_TASKS) {
		printf(ERR_TOO_MANY_TASKS);
		return;
	}

	for (i = 0; i < state->tasksSize; i++) {
		if (strcmp(state->tasks[i].desc, desc) == 0) {
			printf(ERR_DUPLICATE_DESC);
			return;
		}
	}

	id = state->tasksSize + 1;
	state->tasksSize++;
	new = state->tasks[id - 1];
	getActivity(&actv, state->activities, state->activitiesSize, DEFAULT_ACTV_TODO);
	new.activity = actv;
	strcpy(new.desc, desc);
	new.duration = duration;
	new.id = id;
	new.start = 0;

	printf("task %d\n", new.id);
}

void list(State *state)
{
	int hadArgs = 0;
	unsigned int i, n = 0;
	Task task;
	char c;
	while (isOkChar(c = getchar())) {
		if (isdigit(c)) {
			hadArgs = 1;
			n = n * 10 + (c - '0');
		} else if (n != 0) {
			task.id = -1;
			getTask(&task, state->tasks, state->tasksSize, n);
			if ((int)task.id == -1) {
				printf(ERR_NO_SUCH_TASK);
				return;
			}
			printTask(task);
			n = 0;
		}
	}
	if (!hadArgs) {
		/* quick sort */
		for (i = 1; i <= state->tasksSize; i++) {
			printf("DESC: %s\n", state->tasks[i].desc);
			printTask(state->tasks[i]);
		}
	}
}

void step(State *state)
{
	printf("Step! %d\n", state->time);
}

void user(State *state)
{
	printf("User! %d\n", state->usersSize);
}

void move(State *state)
{
	printf("Move! %d\n", state->time);
}

void tina(State *state)
{
	printf("Tina! %d\n", state->time);
}

void actv(State *state)
{
	printf("Actv! %d\n", state->activitiesSize);
}