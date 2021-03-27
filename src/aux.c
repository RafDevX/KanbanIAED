/*
 *	File: aux.c
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Auxiliary functions.
*/

/*** Include project header file ***/
#include "kanban.h"

/* Grab and discard command argument separator */
void discardSeparator()
{
	getchar(); /* Possibly error if char is not a space */
}

int isOkChar(char c)
{
	return (c != EOF) && c != '\n'; /* Possibly add more restrictions with ctype.h funcs */
}

void readInt(int *i)
{
	scanf("%d", i);
}

void readString(char s[], int maxsize)
{
	int i = 0;
	char c;
	while (i < maxsize - 2 && isOkChar(c = getchar())) {
		s[i++] = c;
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