/*
 *	File: constants.h
 *	Author: Rafael Serra e Oliveira (ist199311)
 *	Description: Constants for the whole project in the same place for easy configuration.
*/

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