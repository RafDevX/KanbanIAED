/*
 *	File: aux.c
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Auxiliary functions.
*/

/*** Include project header file ***/
#include "kanban.h"

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

Task chooseAndPlacePivot(Task arr[], int lo, int hi, int (*compf)(Task, Task))
{
	int pi;
	Task tmp;
	/* use median of three to choose pivot, place it at the end */
	pi = (hi + lo) / 2;
	if (compf(arr[pi], arr[hi]) < 0) {
		tmp = arr[hi];
		arr[hi] = arr[pi];
		arr[pi] = tmp;
	}
	if (compf(arr[hi], arr[lo]) < 0) {
		tmp = arr[hi];
		arr[hi] = arr[lo];
		arr[lo] = tmp;
	}
	if (compf(arr[pi], arr[hi]) < 0) {
		tmp = arr[hi];
		arr[hi] = arr[pi];
		arr[pi] = tmp;
	}
	return arr[hi];
}

int partialSort(Task arr[], int lo, int hi, Task pivot, int (*compf)(Task, Task))
{
	int i, left, right, first = 1;
	Task tmp;
	do {
		if (!first) {
			tmp = arr[left];
			arr[left] = arr[right];
			arr[right] = tmp;
		}
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

int compareTasksByDesc(Task a, Task b)
{
	return strcmp(a.desc, b.desc);
}

int compareTasksByStartThenDesc(Task a, Task b)
{
	int r = (a.start - b.start);
	if (r == 0) {
		return compareTasksByDesc(a, b);
	}
	return r;
}

int isOkChar(char c)
{
	return c != EOF && c != '\n'; /* Possibly add more restrictions with ctype.h funcs */
}

void discardRemaining()
{
	char c;
	while (isOkChar(c = getchar())) {
		/* do nothing */
	};
}

void readInt(int *i)
{
	scanf("%d", i);
}

void readWord(char w[], int maxsize)
{
	int i = 0, inside = 0;
	char c;
	while (i < maxsize - 2 && isOkChar(c = getchar())) {
		if (!isspace(c)) {
			w[i++] = c;
			inside = 1;
		} else if (inside) {
			break;
		}
	}
	w[i] = '\0';
}

/* ....strips left */
void readString(char s[], int maxsize)
{
	int i = 0, stripping = 1;
	char c;
	while (i < maxsize - 2 && isOkChar(c = getchar())) {
		if (!isspace(c) || !stripping) {
			stripping = 0;
			s[i++] = c;
		}
	}
	s[i] = '\0';
}

Activity *getActivity(Activity list[], int listSize, char *desc)
{
	int i;
	for (i = 0; i < listSize; i++) {
		if (strcmp(list[i].desc, desc) == 0) {
			return &(list[i]);
		}
	}
	return NULL;
}

Task *getTask(Task list[], int listSize, unsigned int id) /* FIXME: dry */
{
	int i;
	for (i = 0; i < listSize; i++) {
		if (list[i].id == id) {
			return &list[i];
		}
	}
	return NULL;
}

User *getUser(User list[], int listSize, char desc[])
{
	int i;
	for (i = 0; i < listSize; i++) {
		if (strcmp(list[i].desc, desc) == 0) {
			return &list[i];
		}
	}
	return NULL;
}

void printTask(Task task)
{
	printf("%u %s #%u %s\n", task.id, task.activity.desc, task.duration, task.desc);
}