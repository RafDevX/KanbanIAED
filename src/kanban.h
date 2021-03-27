/*
 *	File: kanban.h
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Header file for the whole project in the same place for easy configuration.
*/

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

/************************
 ***** Custom Types *****
 ************************/

typedef struct {
	char description[MAX_ACTIVITY_SIZE];
} Activity;

typedef struct {
	char description[MAX_USER_SIZE];
} User;

typedef struct {
	unsigned int id;
	char description[MAX_TASK_DESC_SIZE];
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

/* Commands */
void task(State *state);
void list(State *state);
void step(State *state);
void user(State *state);
void move(State *state);
void tina(State *state);
void actv(State *state);