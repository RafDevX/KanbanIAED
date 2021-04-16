/*
 *	File: aux.c
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Auxiliary functions.
*/

/*** Include project header file ***/
#include "kanban.h"

/* Use MergeSort algorithm to sort tasks by start time */
void mergeSortTasksByStart(Task arr[], int left, int right)
{
	int m = (right + left) / 2;
	if (right <= left)
		return;

	mergeSortTasksByStart(arr, left, m);
	mergeSortTasksByStart(arr, m + 1, right);
	mergeTasksSubArrays(arr, left, m, right);
}

/* Merge two subarrays represented as independent sections in a single array
 * using start time for comparison. Aux function for mergeSortTasksByStart */
void mergeTasksSubArrays(Task arr[], int left, int m, int right)
{
	Task aux[MAX_TASKS];
	int i, j, k;

	for (i = m + 1; i > left; i--)
		aux[i - 1] = arr[i - 1];
	for (j = m; j < right; j++)
		aux[right + m - j] = arr[j + 1];
	for (k = left; k <= right; k++)
		if (aux[j].start < aux[i].start || i == m + 1)
			arr[k] = aux[j--];
		else
			arr[k] = aux[i++];
}

/* Since we're storing tasks alphabetically-sorted from the get go, move 
 * "larger" tasks to the right to make room and return new task's index */
unsigned int makeRoomForNewTask(Task arr[], unsigned int size, char desc[])
{
	int i;

	for (i = size - 1; i >= 0; i--)
		if (strcmp(desc, arr[i].desc) < 0)
			arr[i + 1] = arr[i];
		else
			return i + 1;

	return 0;
}

/* Checks whether a character is acceptable as input within a command */
int isOkChar(char c)
{
	return c != EOF && c != '\n' && c != '\0';
}

/* Discard input until a new command segment is reached */
void discardRemaining()
{
	char c;
	while (isOkChar(c = getchar())) {
		/* do nothing */
	};
}

/* Read an integer from standard input */
void readInt(int *i)
{
	scanf("%d", i);
}

/* Read a string of chars delimited by whitespace characters; strips left */
void readWord(char w[], int maxsize)
{
	int i = 0, inside = 0;
	char c;
	while (i < maxsize && isOkChar(c = getchar())) {
		if (!isspace(c)) {
			w[i++] = c;
			inside = 1;
		} else if (inside) {
			break;
		}
	}
	w[i] = '\0';
}

/* Read until the end of the line/input; strips left */
void readPhrase(char s[], int maxsize)
{
	int i = 0, stripping = 1;
	int c;
	while (i < maxsize && isOkChar(c = getchar())) {
		if (!isspace(c) || !stripping) {
			stripping = 0;
			s[i++] = c;
		}
	}
	s[i] = '\0';
	if (isOkChar(c))		/* if input was too long, a non-ASCII char took */
		discardRemaining(); /* up too much space; what didn't fit is ignored */
}

/* Fetch the activity with a given description from a list,
 * or NULL if it's not found */
Activity *getActivity(Activity list[], int listSize, char *desc)
{
	int i;
	for (i = 0; i < listSize; i++)
		if (strcmp(list[i].desc, desc) == 0)
			return &(list[i]);
	return NULL;
}

/* Fetch the task with a given ID from a list,
 * or NULL if it's not found */
Task *getTaskById(Task list[], int listSize, unsigned int id)
{
	int i;
	for (i = 0; i < listSize; i++)
		if (list[i].id == id)
			return &list[i];
	return NULL;
}

/* Fetch the task with a given description from a list,
 * or NULL if it's not found */
Task *getTaskByDesc(Task list[], int listSize, char desc[])
{
	int med, cmp, left = 0, right = listSize - 1;

	while (left <= right) {
		med = (left + right) / 2;
		cmp = strcmp(list[med].desc, desc);
		if (cmp == 0)
			return &list[med];
		else if (cmp < 0)
			left = med + 1;
		else
			right = med - 1;
	}
	return NULL;
}

/* Fetch the user with a given description from a list,
 * or NULL if it's not found */
User *getUser(User list[], int listSize, char desc[])
{
	int i;
	for (i = 0; i < listSize; i++)
		if (strcmp(list[i].desc, desc) == 0)
			return &list[i];
	return NULL;
}

/* Print a task in the correct format for the list command */
void printTask(Task task)
{
	printf(OUT_LIST_TASK, task.id, task.activity.desc, task.duration,
		   task.desc);
}

/* Initialize task values */
void initTask(Task *task, unsigned int id, char desc[], Activity *startActv,
			  unsigned int duration)
{
	task->activity = *startActv;
	strcpy(task->desc, desc);
	task->duration = duration;
	task->id = id;
	task->start = 0;
}

/* Returns whether a string has any lowercase letters */
int hasLowercaseLetters(char s[])
{
	int i = 0;
	while (isOkChar(s[i])) {
		if (islower(s[i++])) {
			return 1;
		}
	}
	return 0;
}

/* Read from input arguments to the move command, printing errors if necessary,
 * and fetching the specified task, user, and activity. Returns whether it was
 * sucessful */
int readAndSanitizeMoveArguments(State *state, Task **task, User **user,
								 Activity **actv)
{
	int id;
	char username[MAX_USER_SIZE], activity[MAX_ACTIVITY_SIZE];
	readInt(&id);
	readWord(username, MAX_USER_SIZE);
	readPhrase(activity, MAX_ACTIVITY_SIZE);

	*task = getTaskById(state->tasks, state->tasksSize, id);
	*user = getUser(state->users, state->usersSize, username);
	*actv = getActivity(state->activities, state->activitiesSize, activity);

	if (*task == NULL) {
		printf(ERR_NO_SUCH_TASK);
		return 0;
	} else if (strcmp(activity, DEFAULT_ACTV_TODO) == 0) {
		if (strcmp((*task)->activity.desc, DEFAULT_ACTV_TODO) != 0)
			printf(ERR_TASK_ALREADY_STARTED);
		return 0;
	} else if (*user == NULL) {
		printf(ERR_NO_SUCH_USER);
		return 0;
	} else if (*actv == NULL) {
		printf(ERR_NO_SUCH_ACTIVITY);
		return 0;
	}

	return 1;
}