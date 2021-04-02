/*
 *	File: kanban.h
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Header file for the whole project, in the same place
 *		for easy configuration. Includes constants and prototypes.
*/

/*** Include standard libraries ***/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**********************************
 ***** Project-Wide Constants *****
 **********************************/

/*** General ConfigurationConstants ***/

#define INITIAL_TIME 0

/*** Type-Related Constants ***/

#define MAX_ACTIVITY_SIZE 21
#define MAX_USER_SIZE 21
#define MAX_TASK_DESC_SIZE 51

#define MAX_TASKS 10000
#define MAX_USERS 50
#define MAX_ACTIVITIES 10

/*** Keys for Available Commands ***/

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

#define ERR_INVALID_DURATION "invalid duration\n"
#define ERR_TOO_MANY_TASKS "too many tasks\n"
#define ERR_DUPLICATE_DESC "duplicate description\n"
#define ERR_ID_NO_SUCH_TASK "%d: no such task\n"
#define ERR_INVALID_TIME "invalid time\n"
#define ERR_USER_ALREADY_EXISTS "user already exists\n"
#define ERR_TOO_MANY_USERS "too many users\n"
#define ERR_NO_SUCH_TASK "no such task\n"
#define ERR_TASK_ALREADY_STARTED "task already started\n"
#define ERR_NO_SUCH_USER "no such user\n"
#define ERR_NO_SUCH_ACTIVITY "no such activity\n"
#define ERR_DUPLICATE_ACTIVITY "duplicate activity\n"
#define ERR_INVALID_DESCRIPTION "invalid description\n"
#define ERR_TOO_MANY_ACTIVITIES "too many activities\n"

#define OUT_ADD_TASK "task %d\n"
#define OUT_LIST_TASK "%u %s #%u %s\n"
#define OUT_STEP "%u\n"
#define OUT_LIST_USER "%s\n"
#define OUT_MOVE_TASK_TO_DONE "duration=%d slack=%d\n"
#define OUT_LIST_TINA "%u %u %s\n"
#define OUT_LIST_ACTIVITY "%s\n"

/*** Default Activities ***/

#define DEFAULT_ACTV_TODO "TO DO"
#define DEFAULT_ACTV_IPRG "IN PROGRESS"
#define DEFAULT_ACTV_DONE "DONE"

/*** Return Codes ***/

#define RETCODE_OK 0
#define RETCODE_UNKNOWN_CMD -1

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
	unsigned int duration;
	unsigned int start;
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

void quickSortTasks(Task arr[], int lo, int hi, int (*compf)(Task, Task));
Task chooseAndPlacePivot(Task arr[], int lo, int hi, int (*compf)(Task, Task));
int partialSort(Task arr[], int lo, int hi, Task pivot, int (*compf)(Task, Task));
int compareTasksByDesc(Task a, Task b);
int compareTasksByStartThenDesc(Task a, Task b);
int isOkChar(char c);
void discardRemaining(void);
void readInt(int *i);
void readWord(char w[], int maxsize);
void readPhrase(char s[], int maxsize);
Activity *getActivity(Activity list[], int listSize, char *desc);
Task *getTaskById(Task list[], int listSize, unsigned int id);
Task *getTaskByDesc(Task list[], int listSize, char desc[]);
User *getUser(User list[], int listSize, char desc[]);
void printTask(Task task);
void swapTasks(Task arr[], int i, int j);
void initTask(Task *task, unsigned int id, char desc[], Activity *startActv, unsigned int duration);
int hasLowercaseLetters(char s[]);
int readAndSanitizeMoveArguments(State *state, Task **task, User **user, Activity **activity);

/* Commands */

void cmdTask(State *state);
void cmdList(State *state);
void cmdStep(State *state);
void cmdUser(State *state);
void cmdMove(State *state);
void cmdTina(State *state); /* Tasks IN Activity */
void cmdActv(State *state); /* Activities */

/* General */

int triage(State *state, char cmd);