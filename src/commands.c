/*
 *	File: commands.c
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Handlers for all commands.
*/

/*** Include project header file ***/
#include "kanban.h"

void task(State *state)
{
	int duration = -1;
	unsigned int i, size;
	char desc[MAX_TASK_DESC_SIZE];
	Task *new;
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

	size = state->tasksSize++;
	new = &state->tasks[size];
	getActivity(&actv, state->activities, state->activitiesSize, DEFAULT_ACTV_TODO);
	new->activity = actv;
	strcpy(new->desc, desc);
	new->duration = duration;
	new->id = size + 1;
	new->start = 0;

	printf("task %d\n", size + 1);
}

void list(State *state)
{
	int hadArgs = 0;
	unsigned int i, n = 0;
	Task task;
	char c;
	do {
		c = getchar();
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
	} while (isOkChar(c));
	if (!hadArgs) {
		quickSortTasks(state->tasks, 0, state->tasksSize - 1);
		for (i = 0; i < state->tasksSize; i++) {
			printTask(state->tasks[i]);
		}
	}
}

void step(State *state)
{
	int duracao = -1;
	readInt(&duracao);
	discardRemaining();
	if (duracao < 0) {
		printf(ERR_INVALID_TIME);
	}
	printf("%u\n", state->time += duracao);
}

void user(State *state)
{
	unsigned int i, len = 0;
	char c, user[MAX_USER_SIZE];
	while (isOkChar(c = getchar())) {
		if (!isspace(c)) {
			user[len++] = c;
		}
	}
	user[len] = '\0';
	if (strcmp(user, "") != 0) {
		for (i = 0; i < state->usersSize; i++) {
			if (strcmp(state->users[i].desc, user) == 0) {
				printf(ERR_USER_ALREADY_EXISTS);
				return;
			}
		}
		if (state->usersSize + 1 >= MAX_USERS) {
			printf(ERR_TOO_MANY_USERS);
			return;
		}

		strcpy(state->users[state->usersSize++].desc, user);
	} else {
		for (i = 0; i < state->usersSize; i++) {
			printf("%s\n", state->users[i].desc);
		}
	}
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