/*-------------------------------------------------------------------*/
/*                                                                   */
/*  File Name : ish.h                                                */
/*  Author: 박지현(20170285), 손소정(20170337)                          */
/*  Description: Declare functions used in the entire process        */
/*                                                                   */
/*-------------------------------------------------------------------*/


#ifndef __ISH_H__
#define __ISH_H__

/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pwd.h>
#include <signal.h>
#include <fcntl.h>
#include "dynarray.h"

/*--------------------------------------------------------------------*/

#define MAXSIZE 1024
enum {FALSE, TRUE};


void SIGQUIT_handler(int signo);
void salarm(int time);
/*--------------------------------------------------------------------*/
/* Dynarray.h                                                         */
// included by [ #include "dynarray.h" ]

/*--------------------------------------------------------------------*/
/* Validity_test.c                                                    */
enum TokenType {TOKEN, PIPELINE}; // 0 and 1 set! 
struct Token
{
   enum TokenType eType; /* The type of the token. */
   char *pcValue; /* The string which is the token's value. */
};
void freeToken(void *pvItem, void *pvExtra);
// static void printToken(void *pvItem, void *pvExtra);
// static struct Token *makeToken(enum TokenType eTokenType, char *pcValue);
int lexLine(const char *pcLine, DynArray_T oTokens);
int synLine(DynArray_T oTokens);

/*--------------------------------------------------------------------*/
/* cmdproc.c                                                          */
int cmdproc(char **argvp);
int _setenv(char **argvp);
int _unsetenv(char **argvp);
int _cd(char **argvp);

/*--------------------------------------------------------------------*/
/* pipe.c                                                             */
int _pipe(char **argvp);

/*--------------------------------------------------------------------*/
/* fork.c                                                             */
int _fork(char **argvp);

/*--------------------------------------------------------------------*/

#endif
