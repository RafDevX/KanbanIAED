/*
 *	File: commands.c
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Handlers for all commands.
*/

/*** Include project header file ***/
#include "kanban.h"

void cmdTask(State *state)
{
	int duration = -1;
	unsigned int i, size;
	char desc[MAX_TASK_DESC_SIZE];
	Task *new;
	Activity *actv;
	readInt(&duration);
	readPhrase(desc, MAX_TASK_DESC_SIZE);

	if (duration <= 0) {
		printf(ERR_INVALID_DURATION);
		return;
	} else if (state->tasksSize + 1 > MAX_TASKS) {
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
	actv = getActivity(state->activities, state->activitiesSize, DEFAULT_ACTV_TODO);
	new->activity = *actv;
	strcpy(new->desc, desc);
	new->duration = duration;
	new->id = size + 1;
	new->start = 0;

	printf("task %d\n", size + 1);
}

void cmdList(State *state)
{
	int hadArgs = 0;
	unsigned int i, n = 0;
	Task *task;
	char c;
	do {
		c = getchar();
		if (isdigit(c)) {
			hadArgs = 1;
			n = n * 10 + (c - '0');
		} else if (n != 0) {
			task = getTask(state->tasks, state->tasksSize, n);
			if (task == NULL) {
				printf(ERR_ID_NO_SUCH_TASK, n);
				return;
			}
			printTask(*task);
			n = 0;
		}
	} while (isOkChar(c));
	if (!hadArgs) {
		quickSortTasks(state->tasks, 0, state->tasksSize - 1, compareTasksByDesc);
		for (i = 0; i < state->tasksSize; i++) {
			printTask(state->tasks[i]);
		}
	}
}

void cmdStep(State *state)
{
	int duracao = -1;
	readInt(&duracao);
	discardRemaining();
	if (duracao < 0) {
		printf(ERR_INVALID_TIME);
		return;
	}
	printf("%u\n", state->time += duracao);
}

void cmdUser(State *state)
{
	unsigned int i = 0;
	char username[MAX_USER_SIZE];
	User *user;
	readWord(username, MAX_USER_SIZE);
	if (username[0] != '\0') {
		user = getUser(state->users, state->usersSize, username);
		if (user != NULL) {
			printf(ERR_USER_ALREADY_EXISTS);
			return;
		}
		if (state->usersSize + 1 > MAX_USERS) {
			printf(ERR_TOO_MANY_USERS);
			return;
		}

		strcpy(state->users[state->usersSize++].desc, username);
	} else {
		for (i = 0; i < state->usersSize; i++) {
			printf("%s\n", state->users[i].desc);
		}
	}
}

void cmdMove(State *state)
{
	int id, elapsed = 0, slack;
	char username[MAX_USER_SIZE], activity[MAX_ACTIVITY_SIZE];
	Task *task;
	User *user;
	Activity *actv;
	readInt(&id);
	readWord(username, MAX_USER_SIZE);
	readPhrase(activity, MAX_ACTIVITY_SIZE);

	task = getTask(state->tasks, state->tasksSize, id);
	if (task == NULL) {
		printf(ERR_NO_SUCH_TASK);
		return;
	}
	if (strcmp(activity, DEFAULT_ACTV_TODO) == 0) {
		printf(ERR_TASK_ALREADY_STARTED);
		return;
	}

	user = getUser(state->users, state->usersSize, username);
	if (user == NULL) {
		printf(ERR_NO_SUCH_USER);
		return;
	}

	actv = getActivity(state->activities, state->activitiesSize, activity);
	if (actv == NULL) {
		printf(ERR_NO_SUCH_ACTIVITY);
		return;
	}

	if (strcmp(task->activity.desc, actv->desc) != 0) {
		if (strcmp(actv->desc, DEFAULT_ACTV_DONE) == 0) {
			if (strcmp(task->activity.desc, DEFAULT_ACTV_TODO) != 0) {
				elapsed = state->time - task->start;
			}
			slack = elapsed - task->duration;
			printf("duration=%d slack=%d\n", elapsed, slack);
		} else if (task->start == 0) {
			task->start = state->time;
		}

		task->activity = *actv;
	}
}

void cmdTina(State *state)
{
	unsigned int i, size = 0;
	char activity[MAX_ACTIVITY_SIZE];
	Activity *actv;
	Task tasks[MAX_TASKS];
	readPhrase(activity, MAX_ACTIVITY_SIZE);
	actv = getActivity(state->activities, state->activitiesSize, activity);
	if (actv == NULL) {
		printf(ERR_NO_SUCH_ACTIVITY);
		return;
	}

	for (i = 0; i < state->tasksSize; i++) {
		if (strcmp(state->tasks[i].activity.desc, actv->desc) == 0) {
			tasks[size++] = state->tasks[i];
		}
	}

	quickSortTasks(tasks, 0, size - 1, compareTasksByStartThenDesc);

	for (i = 0; i < size; i++) {
		printf("%u %u %s\n", tasks[i].id, tasks[i].start, tasks[i].desc);
	}
}

void cmdActv(State *state)
{
	char activity[MAX_ACTIVITY_SIZE] = "";
	unsigned int i = 0;
	Activity *actv;
	readPhrase(activity, MAX_ACTIVITY_SIZE);
	if (activity[0] != '\0') {
		actv = getActivity(state->activities, state->activitiesSize, activity);
		if (actv != NULL) {
			printf(ERR_DUPLICATE_ACTIVITY);
			return;
		}
		while (isOkChar(activity[i])) {
			if (islower(activity[i++])) {
				printf(ERR_INVALID_DESCRIPTION);
				return;
			}
		}
		if (state->activitiesSize + 1 > MAX_ACTIVITIES) {
			printf(ERR_TOO_MANY_ACTIVITIES);
			return;
		}

		strcpy(state->activities[state->activitiesSize++].desc, activity);
	} else {
		for (i = 0; i < state->activitiesSize; i++) {
			printf("%s\n", state->activities[i].desc);
		}
	}
}