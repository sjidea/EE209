//pipe.c
/*-------------------------------------------------------------------*
 *                                                                   *
 *  File Name : pipe.c                                               *
 *  Author: 박지현(20170285), 손소정(20170337)                          *
 *  Description: check if pipe exist, and do pipe process            *
 *                                                                   *
 *-------------------------------------------------------------------*/

#include "ish.h"
extern int ispipe;

/*-------------------------------------------------------------------*
   Function : int _pipe(char **argvp)                                *
   ============================================                      *
   Input    : command를 분리한 argument vector                         *
   Output   : -1(fails) or exit                                      *
   Purpose  : pipe() process                                         *
---------------------------------------------------------------------*/
int _pipe(char **argvp) {

   int n = 0, i, j;
   int fd[2];
   int status;
   char *argvp2[MAXSIZE]; 

   // '|' does not exist
   if(!ispipe){
      if(cmdproc(argvp) == 1) execvp(*argvp, argvp);
      return 0;
   }    
   // '|' exists
   else {
   // find where pipe is
      for(n=0; argvp[n] != NULL; n++)
         if(strcmp(argvp[n], "|") == 0) break;

   // "argvp | argvp2" make this form
      argvp[n] = NULL; //add NULL at the end of argvp
      for(i=n+1, j=0; argvp[i]!=NULL; i++, j++)
      {
         strcpy(argvp2[j], argvp[i]);
         argvp[i] = NULL; //remove frop argvp 
      }
      argvp2[j] = NULL; //add NULL at the end of argvp2

   // use fork() to execute
      // make pipe
      if(pipe(fd) == -1){
         fprintf(stderr, "./ish: pipe failed\n");
         return -1;
      }

      int pid;
      fflush(NULL);
      pid = fork();
      if(pid <0){
         fprintf(stderr, "./ish: Can't fork process\n");
         return -1;
      } else if(pid == 0 ) {
         dup2(fd[1], 0);
         close(fd[0]);
         close(fd[1]);
         if(cmdproc(argvp) == 1) execvp(*argvp, argvp);
         exit(0); 
      } else { 
         if((pid = waitpid(pid, &status, 0)) < 0){
          fprintf(stderr,"./ish: wait pid error\n");
          return -1;
          }
          dup2(fd[0], 1);
         close(fd[0]);
         close(fd[1]);
      }
   }
   if(cmdproc(argvp2) == 1) execvp(*argvp2, argvp2);
   return 0;
}
