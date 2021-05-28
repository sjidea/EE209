//fork.c
/*-------------------------------------------------------------------*
 *                                                                   *
 *  File Name : fork.c                                               *
 *  Author: 박지현(20170285), 손소정(20170337)                          *
 *  Function : int _fork(char **argvp)                            *
 * ================================================================  *
 *  Input    : command를 분리한 argument vector                        *
 *  Output   : If error occurs -1. Otherwise 0                       *
 *  Purpose  : fork() to make child process and execute command      *
 *                                                                   *
 *-------------------------------------------------------------------*/

#include "ish.h"
extern int ispipe;

int _fork(char **argvp)
{
   int      pid;
   int      status;   

   fflush(NULL);
   if((pid = fork()) < 0)
   {
      fprintf(stderr,"./ish: Can't fork process");
      return -1;
   }

   else if(pid == 0)
   {
      signal(SIGINT, SIG_DFL);

      if(ispipe){
          if(_pipe(argvp)==-1) return -1;
      }
      execvp(*argvp, argvp);

      exit(0);
   }

   else
   {

      if((pid = waitpid(pid, &status, 0)) < 0)
      {
         fprintf(stderr,"./ish: wait pid error\n");
         return -1;
      }
      return 0;
   }
}
