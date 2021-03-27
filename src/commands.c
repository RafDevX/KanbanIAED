/*
 *	File: commands.c
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Handlers for all commands.
*/

/*** Include standard libraries ***/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*** Include project header file ***/
#include "kanban.h"

void task(State *state)
{
	printf("Task!");
}

void list(State *state)
{
	printf("List!");
}

void step(State *state)
{
	printf("Step!");
}

void user(State *state)
{
	printf("User!");
}

void move(State *state)
{
	printf("Move!");
}

void tina(State *state)
{
	printf("Tina!");
}

void actv(State *state)
{
	printf("Actv!");
}