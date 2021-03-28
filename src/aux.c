/*
 *	File: aux.c
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Auxiliary functions.
*/

/*** Include project header file ***/
#include "kanban.h"

void quickSortTasks(Task arr[], int lo, int hi)
{
	int pi;
	Task pivot;
	if (lo < hi) {
		pivot = chooseAndPlacePivot(arr, lo, hi);
		pi = partialSort(arr, lo, hi, pivot);

		arr[hi] = arr[pi]; /* put pivot back */
		arr[pi] = pivot;

		quickSortTasks(arr, lo, pi - 1);
		quickSortTasks(arr, pi + 1, hi);
	}
}

Task chooseAndPlacePivot(Task arr[], int lo, int hi)
{
	int pi;
	Task tmp;
	/* use median of three to choose pivot, place it at the end */
	pi = (hi + lo) / 2;
	if (strcmp(arr[pi].desc, arr[hi].desc) < 0) {
		tmp = arr[hi];
		arr[hi] = arr[pi];
		arr[pi] = tmp;
	}
	if (strcmp(arr[hi].desc, arr[lo].desc) < 0) {
		tmp = arr[hi];
		arr[hi] = arr[lo];
		arr[lo] = tmp;
	}
	if (strcmp(arr[pi].desc, arr[hi].desc) < 0) {
		tmp = arr[hi];
		arr[hi] = arr[pi];
		arr[pi] = tmp;
	}
	return arr[hi];
}

int partialSort(Task arr[], int lo, int hi, Task pivot)
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
			if (strcmp(arr[i].desc, pivot.desc) > 0) {
				left = i;
				break;
			}
		}
		for (i = hi - 1; i >= lo; i--) {
			if (strcmp(arr[i].desc, pivot.desc) < 0) {
				right = i;
				break;
			}
		}
	} while (left < right);
	return left;
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

void getActivity(Activity *actv, Activity list[], int listSize, char *desc)
{
	int i;
	for (i = 0; i < listSize; i++) {
		if (strcmp(list[i].desc, desc) == 0) {
			*actv = list[i];
			break;
		}
	}
}

void getTask(Task *task, Task list[], int listSize, unsigned int id) /* FIXME: dry */
{
	int i;
	for (i = 0; i < listSize; i++) {
		if (list[i].id == id) {
			*task = list[i];
			break;
		}
	}
}

void printTask(Task task)
{
	printf("%u %s #%u %s\n", task.id, task.activity.desc, task.duration, task.desc);
}

int compareTaskDescs(void *a, void *b)
{
	return ((*(Task *)a).desc - (*(Task *)b).desc);
}