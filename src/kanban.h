/*
 *	File: kanban.h
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Header file for the whole project in the same place for easy configuration.
*/

/*** Include standard libraries ***/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**********************************
 ***** Project-Wide Constants *****
 **********************************/

/*** Type-related constants ***/

#define MAX_ACTIVITY_SIZE 20
#define MAX_USER_SIZE 20
#define MAX_TASK_DESC_SIZE 50

#define MAX_TASKS 10000
#define MAX_USERS 50
#define MAX_ACTIVITIES 10

/*** Available commands ***/

/* Exit the program */
#define QUIT_CMD 'q'
/* Add a new task */
#define TASK_CMD 't'
/* List tasks */
#define LIST_CMD 'l'
/* Step into next time instant */
#define STEP_CMD 'n'
/* Add or list users */
#define USER_CMD 'u'
/* Move tasks to another activity */
#define MOVE_CMD 'm'
/* List [T]asks [in] [a]ctivity */
#define TINA_CMD 'd'
/* Add or list activities */
#define ACTV_CMD 'a'

/*** User-Oriented Messages ***/

#define ERR_INVALID_DURATION "invalid duration"
#define ERR_TOO_MANY_TASKS "too many tasks"
#define ERR_DUPLICATE_DESC "duplicate description"

/************************
 ***** Custom Types *****
 ************************/

typedef struct {
	char desc[MAX_ACTIVITY_SIZE];
} Activity;

typedef struct {
	char desc[MAX_USER_SIZE];
} User;

typedef struct {
	unsigned int id;
	char desc[MAX_TASK_DESC_SIZE];
	User user;
	Activity activity;
	unsigned int estDuration;
	unsigned int startTime;
} Task;

typedef struct {
	Task tasks[MAX_TASKS];
	unsigned int tasksSize;
	User users[MAX_USERS];
	unsigned int usersSize;
	Activity activities[MAX_ACTIVITIES];
	unsigned int activitiesSize;
	unsigned int time;
} State;

/*********************
 ***** Functions *****
 *********************/

/* Auxiliary */

void discardSeparator(); /* FIXME: multiple (or 0 for invalid cmd) spaces are allowed as separators!!! */
int isOkChar(char c);
void readInt(int *i);
void readString(char s[], int maxsize);
void getActivity(Activity *actv, Activity list[], int listSize, char desc[]);
int compareStringToActivity(const void *s, const void *a);

/* Note: Cannot have a readUnsignedInt as there will be tests like duration = -10 */

/* Commands */

void task(State *state);
void list(State *state);
void step(State *state);
void user(State *state);
void move(State *state);
void tina(State *state); /* Tasks IN Activity */
void actv(State *state); /* Activities */