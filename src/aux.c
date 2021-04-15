/*
 *	File: aux.c
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Auxiliary functions.
*/

/*** Include project header file ***/
#include "kanban.h"

/* Since we're storing tasks alphabetically-sorted from the get go, move 
 * "larger" tasks to the right to make room and return new task's index */
unsigned int makeRoomForNewTask(Task arr[], unsigned int size, char desc[])
{
	int i;

	for (i = size - 1; i >= 0; i--) {
		if (strcmp(desc, arr[i].desc) < 0) {
			arr[i + 1] = arr[i];
		} else {
			return i + 1;
		}
	}
	return 0;
}

/* Sort tasks using the QuickSort algorithm (Hoare partition scheme) */
void quickSortTasks(Task arr[], int lo, int hi, int (*compf)(Task, Task))
{
	int pi;
	Task pivot;
	if (lo < hi) {
		pivot = chooseAndPlacePivot(arr, lo, hi, compf);
		pi = partialSort(arr, lo, hi, pivot, compf);

		arr[hi] = arr[pi]; /* put pivot back */
		arr[pi] = pivot;

		quickSortTasks(arr, lo, pi - 1, compf);
		quickSortTasks(arr, pi + 1, hi, compf);
	}
}

/* Aux for quickSortTasks: choose a pivot using the median of three method and
 * place it at the end, keeping the remaining two ordered */
Task chooseAndPlacePivot(Task arr[], int lo, int hi, int (*compf)(Task, Task))
{
	int pi;

	pi = (hi + lo) / 2;
	if (compf(arr[pi], arr[hi]) < 0)
		swapTasks(arr, hi, pi);
	if (compf(arr[hi], arr[lo]) < 0)
		swapTasks(arr, hi, lo);
	if (compf(arr[pi], arr[hi]) < 0)
		swapTasks(arr, hi, pi);
	return arr[hi];
}

/* Aux for quickSortTasks: partially sort and determine the correct position
 * for the pivot */
int partialSort(Task arr[], int lo, int hi, Task pivot, int (*compf)(Task, Task))
{
	int i, left, right, first = 1;
	do {
		if (!first)
			swapTasks(arr, left, right);
		first = 0;
		left = hi;
		right = lo;
		for (i = lo; i <= hi - 1; i++) {
			if (compf(arr[i], pivot) > 0) {
				left = i;
				break;
			}
		}
		for (i = hi - 1; i >= lo; i--) {
			if (compf(arr[i], pivot) < 0) {
				right = i;
				break;
			}
		}
	} while (left < right);
	return left;
}

/* Compare function to sort tasks by character code order of their descriptions
 * Negative if a comes before b, Positive if b comes before a, 0 otherwise */
int compareTasksByDesc(Task a, Task b)
{
	return strcmp(a.desc, b.desc);
}

/* Compare function to sort tasks by start time and then by description if
 * start times match. Negative if a < b, positive if a > b, 0 if a == b */
int compareTasksByStartThenDesc(Task a, Task b)
{
	int r = (a.start - b.start);
	return (r != 0) ? r : compareTasksByDesc(a, b);
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
	int i;
	for (i = 0; i < listSize; i++) {
		if (strcmp(list[i].desc, desc) == 0) {
			return &list[i];
		}
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
	printf(OUT_LIST_TASK, task.id, task.activity.desc, task.duration, task.desc);
}

/* Swap items in an array of tasks, given two indices */
void swapTasks(Task arr[], int i, int j)
{
	Task tmp;
	tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

/* Initialize task values */
void initTask(Task *task, unsigned int id, char desc[], Activity *startActv, unsigned int duration)
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
int readAndSanitizeMoveArguments(State *state, Task **task, User **user, Activity **actv)
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