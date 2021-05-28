//cmdproc.c
/*-------------------------------------------------------------------*
 *                                                                   *
 *  File Name : cmdproc.c                                            *
 *  Author: 박지현(20170285), 손소정(20170337)                          *
 *  Description: Check if built-in commands exists and implement     *
 *                                                                   *
 *-------------------------------------------------------------------*/

#include "ish.h"
extern int ispipe;
/*-------------------------------------------------------------------*
   Function : cmdproc(char **argvp)                                  *
   ============================================                      *
   Input    : command를 분리한 argument vector                         *
   Output   : 1(no blt-in cmds), 0(process success),                 * 
            -1(process fail), 2(blt-in cmd is exit                   *
   Purpose  : Find blt-in cmds                                       *
---------------------------------------------------------------------*/
int cmdproc(char **argvp){
   char *elem1=argvp[0]; //oh my god
   if(strcmp(elem1, "setenv") == 0) return _setenv(argvp);
   else if(strcmp(elem1, "unsetenv") == 0) return _unsetenv(argvp);
   else if(strcmp(elem1, "cd") == 0) return _cd(argvp);
   else if(strcmp(elem1, "exit") == 0) {
      if(ispipe)
      fprintf(stderr, "./ish: built-in commands do not contain pipes\n");
      return 2;
   }
   else return 1;
}

/*-------------------------------------------------------------------*
   Function : int _setenv(char **argvp)                              *
   ============================================                      *
   Input    : command를 분리한 argument vector                         *
   Output   : -1(process fail), 0(process success)                   * 
   Purpose  : set environment by setenv()                            *
---------------------------------------------------------------------*/
int _setenv(char **argvp){ //hmm, void could be better,, istn't it???

   if(ispipe){
      fprintf(stderr, "./ish: built-in commands do not contain pipes\n");
      return -1;
   }
   
   char *name, *value;
   int   length=0;
   for(;argvp[length]!=NULL; length++);

   if((length == 1) || (length > 3)){
      fprintf(stderr, "./ish: setenv takes one or two parameters\n");
      return -1; 
   } else if(length==2){

      name = argvp[1];
      if(setenv(name, "", 1) == -1){
         fprintf(stderr, "./ish: setenv failed\n");//any other opinion about this error message?
         return -1; //what whould i return??
      }
   } else{ 
      name = argvp[1];
      value = argvp[2];
      if(setenv(name, value, 1) == -1){ //setenv failed
         fprintf(stderr, "./ish: setenv failed\n");//any other opinion about this error message?
         return -1; //what should i return ????
      }
   }

   return 0; //what should i return ????
}

/*-------------------------------------------------------------------*
   Function : int _unsetenv(char **argvp)                            *
   ============================================                      *
   Input    : command를 분리한 argument vector                         *
   Output   : -1(process fail), 0(process success)                   * 
   Purpose  : unset environment by unsetenv()                        *
---------------------------------------------------------------------*/
int _unsetenv(char **argvp){

   if(ispipe){
      fprintf(stderr, "./ish: built-in commands do not contain pipes\n");
      return -1;
   }

   int length=0;
   for(;argvp[length]!=NULL; length++);

   if(length != 2) {
      fprintf(stderr, "./ish: unsetenv takes one parameter\n");
      return -1;
   }

   char *name = argvp[1];
   if(unsetenv(name) == -1){
      fprintf(stderr, "./ish: unsetenv failed\n");
   }
   return 0;//what should i return ??/?
}

/*-------------------------------------------------------------------*
   Function : int _cd(char **argvp)                                  *
   ============================================                      *
   Input    : command를 분리한 argument vector                         *
   Output   : -1(process fail), 0(process success)                   * 
   Purpose  : change directory to directory named argvp              *
---------------------------------------------------------------------*/
int _cd(char **argvp){

   if(ispipe){
      fprintf(stderr, "./ish: built-in commands do not contain pipes\n");
      return -1;
   }

   int length=0;
   for(;argvp[length]!=NULL; length++);

   if(length > 2) 
   {
      fprintf(stderr, "./ish: cd takes one parameter\n");
      return -1;
   } else if(length == 2) {
     int suc = chdir(argvp[1]);
      if(suc == -1){
         fprintf(stderr, "./ish: No such file or directory\n");
         return -1;
      }
   } else {
      char *HOMEE = getenv("HOME");
      if(chdir(HOMEE) == -1){
         fprintf(stderr, "./ish: cd failed\n");
         return -1;
      }
   }
   return 0;
}
