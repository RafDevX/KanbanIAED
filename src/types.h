/*
 *	File: types.h
 *	Author: Rafael Serra e Oliveira (99311)
 *	Description: Header file for relevant type definition
*/

#define MAX_ACTIVITY_SIZE 20
#define MAX_USER_SIZE 20
#define MAX_TASK_DESC_SIZE 50

#define MAX_TASKS 10000
#define MAX_USERS 50
#define MAX_ACTIVITIES 10

/*	"typedef char TypeName[Size]" is bad practice so a one-field struct is used
 *	See https://stackoverflow.com/a/4523537/11156826
*/

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
	User users[MAX_USERS];
	Activity activities[MAX_ACTIVITIES];
	unsigned int time;
} State;