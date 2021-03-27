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
	char desc[MAX_TASK_DESC_SIZE];
	Task new;
	Activity actv;
	readInt(&duration);
	discardSeparator();
	readString(desc, MAX_TASK_DESC_SIZE);

	if (duration <= 0) {
		printf(ERR_INVALID_DURATION);
		return;
	}

	id = state->tasksSize + 1;
	state->tasksSize++;
	new = state->tasks[id - 1];
	getActivity(&actv, state->activities, state->activitiesSize, "TO DO");
	new.activity = actv;
	strcpy(new.desc, desc);
	new.estDuration = duration;
	new.id = id;
	new.startTime = 0;

	printf("task %d\n", new.id);
}

void list(State *state)
{
	printf("List! %d\n", state->tasksSize);
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