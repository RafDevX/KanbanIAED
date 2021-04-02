/*
 *	File: commands.c
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Handlers for all commands.
*/

/*** Include project header file ***/
#include "kanban.h"

/* Add a new task */
void cmdTask(State *state)
{
	int duration = -1;
	unsigned int size;
	char desc[MAX_TASK_DESC_SIZE];
	Activity *actv;
	readInt(&duration);
	readPhrase(desc, MAX_TASK_DESC_SIZE);

	if (state->tasksSize + 1 > MAX_TASKS) {
		printf(ERR_TOO_MANY_TASKS);
		return;
	}

	if (getTaskByDesc(state->tasks, state->tasksSize, desc) != NULL) {
		printf(ERR_DUPLICATE_DESC);
		return;
	}

	if (duration <= 0) {
		printf(ERR_INVALID_DURATION);
		return;
	}

	size = state->tasksSize++;
	actv = getActivity(state->activities, state->activitiesSize, DEFAULT_ACTV_TODO);
	initTask(&state->tasks[size], size + 1, desc, actv, duration);

	printf(OUT_ADD_TASK, size + 1);
}

/* List tasks with ID, or all if no ID provided */
void cmdList(State *state)
{
	int i, id, hadArgs = 0;
	Task *task;

	while (scanf("%d", &id)) {
		hadArgs = 1;
		task = id > 0 ? getTaskById(state->tasks, state->tasksSize, (unsigned int)id) : NULL;
		if (task == NULL)
			printf(ERR_ID_NO_SUCH_TASK, id);
		else
			printTask(*task);
	}

	if (!hadArgs) {
		quickSortTasks(state->tasks, 0, state->tasksSize - 1, compareTasksByDesc);
		for (i = 0; i < (int)state->tasksSize; i++)
			printTask(state->tasks[i]);
	}
}

/* Increment time by specified amount */
void cmdStep(State *state)
{
	int duracao = -1;

	readInt(&duracao);
	discardRemaining();
	if (duracao < 0) {
		printf(ERR_INVALID_TIME);
		return;
	}
	printf(OUT_STEP, state->time += duracao);
}

/* Create a user or list existing */
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
		} else if (state->usersSize + 1 > MAX_USERS) {
			printf(ERR_TOO_MANY_USERS);
			return;
		}

		strcpy(state->users[state->usersSize++].desc, username);
	} else {
		for (i = 0; i < state->usersSize; i++)
			printf(OUT_LIST_USER, state->users[i].desc);
	}
}

/* Move a task from one activity to another */
void cmdMove(State *state)
{
	int elapsed, slack;
	Task *task = NULL;
	User *user = NULL;
	Activity *actv = NULL;

	if (!readAndSanitizeMoveArguments(state, &task, &user, &actv)) {
		return;
	}

	task->user = *user;

	if (strcmp(task->activity.desc, actv->desc) != 0) {
		if (strcmp(task->activity.desc, DEFAULT_ACTV_TODO) == 0)
			task->start = state->time;

		if (strcmp(actv->desc, DEFAULT_ACTV_DONE) == 0) {
			elapsed = state->time - task->start;
			slack = elapsed - task->duration;
			printf(OUT_MOVE_TASK_TO_DONE, elapsed, slack);
		}

		task->activity = *actv;
	}
}

/* List all [T]asks [IN] a specified [A]ctivity */
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

	for (i = 0; i < state->tasksSize; i++)
		if (strcmp(state->tasks[i].activity.desc, actv->desc) == 0)
			tasks[size++] = state->tasks[i];

	quickSortTasks(tasks, 0, size - 1, compareTasksByStartThenDesc);

	for (i = 0; i < size; i++)
		printf(OUT_LIST_TINA, tasks[i].id, tasks[i].start, tasks[i].desc);
}

/* Create a new activity or list existing */
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
		} else if (hasLowercaseLetters(activity)) {
			printf(ERR_INVALID_DESCRIPTION);
			return;
		} else if (state->activitiesSize + 1 > MAX_ACTIVITIES) {
			printf(ERR_TOO_MANY_ACTIVITIES);
			return;
		}

		strcpy(state->activities[state->activitiesSize++].desc, activity);
	} else {
		for (i = 0; i < state->activitiesSize; i++)
			printf(OUT_LIST_ACTIVITY, state->activities[i].desc);
	}
}