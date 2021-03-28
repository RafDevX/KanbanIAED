/*
 *	File: aux.c
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Auxiliary functions.
*/

/*** Include project header file ***/
#include "kanban.h"

int isOkChar(char c)
{
	return c != EOF && c != '\n'; /* Possibly add more restrictions with ctype.h funcs */
}

void quickSort(void *base, unsigned int size, int (*cmpfunc)(void *, void *))
{
	/* TODO: this */
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