//ish.c
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  File Name : ish.c                                                */
/*  Author: 박지현(20170285), 손소정(20170337)                          */
/*  Description: Make a simple shell process to handle commands      */
/*                                                                   */
/*-------------------------------------------------------------------*/

#include "ish.h"
/*-------------------------------------------------------------------*/
/* A DynArray consists of an array, along with its logical and
   physical lengths. */
struct DynArray
{
   /* The number of elements in the DynArray from the client's
      point of view. */
   int iLength;
   
   /* The number of elements in the array that underlies the
      DynArray. */
   int iPhysLength;
   
   /* The array that underlies the DynArray. */
   const void **ppvArray;
};
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*
   Function : SIGQUIT_handler                                        *
   ============================================                      *
   Input    : signal number                                          *
   Output   : void                                                   *
   Purpose  : making a handler to handle SIGQUIT(ctrl+/) signal      *
---------------------------------------------------------------------*/
int squit = 0;
time_t secondSig = 0;
void sigquit_handler(int signum)
{
    if(squit == 0){
      printf("\nType Ctrl-\\ again within 5 seconds to exit.\n");
      printf("%% ");
      fflush(stdout);
      squit = 1;
      alarm(5);
    }
    else exit(0);
}
void salarm(int time)
{
  squit = 0;
}

int ispipe = 0;

/*-------------------------------------------------------------------*
   Function : main                                                   *
   ============================================                      *
   Input    : argc, argv, envp                                       *
   Output   : 1 or 0.                                                *
   Purpose  : receive and execute command from .ishrc and stdin      *
---------------------------------------------------------------------*/
int main(int argc, char  *argv[], char **envp)
{
  /*-----------------------------------------------------------------*
     Make SIGINT, SIGQUIT, SIGALARM signals unblocked
  -------------------------------------------------------------------*/
  sigset_t sSigSet;
  int iRet;
  sigemptyset(&sSigSet);
  sigaddset(&sSigSet, SIGALRM);
  sigaddset(&sSigSet, SIGINT);
  sigaddset(&sSigSet, SIGQUIT);
  iRet = sigprocmask(SIG_UNBLOCK, &sSigSet, NULL);
  assert(iRet == 0);
  
  char  command[MAXSIZE] = {0};
  DynArray_T oTokens;
  int   iSuccessful;   // result of validity test(lexLine,synLine)
  int   i=0;  // temporary variable
  int   a=0;

  /*-----------------------------------------------------------------*
     Signal Handler part
  -------------------------------------------------------------------*/
  signal(SIGINT, SIG_IGN);
  void (*sig_handler1)(int);
  sig_handler1 = signal(SIGALRM, salarm);
  assert(sig_handler1!=SIG_ERR);
  void (*sig_handler2)(int);
  sig_handler2 = signal(SIGQUIT, sigquit_handler);
  assert(sig_handler2!=SIG_ERR);

  /*-----------------------------------------------------------------*
     get input from file ".ishrc"
  -------------------------------------------------------------------*/
  FILE *f = fopen(".ishrc", "r");
  while (fgets(command, MAXSIZE, f)) {
    if(!f) {
      break;
    }
    // print prompt
    printf("%% %s", command);
    fflush(stdout);

    /*---------------------------------------------------------------*
      Check the length of command line.
    -----------------------------------------------------------------*/
    if (strcmp(command, "\n")==0) continue;
    if (strlen(command) > MAXSIZE-1)
      fprintf(stderr, "%s: Input line is too long\n",argv[0]);
    else { // if command is not too long,
      oTokens = DynArray_new(0);
      if (oTokens == NULL) {
        fprintf(stderr, "%s: Cannot allocate memory\n",argv[0]);
        exit(EXIT_FAILURE);
      }
      
      /*-------------------------------------------------------------*
        Check if command is valid.
      ---------------------------------------------------------------*/
      iSuccessful = lexLine(command, oTokens) && synLine(oTokens);
      int length = DynArray_getLength(oTokens);
      char *argvp[MAXSIZE];
      if (iSuccessful) {  
        /* making array of Token->pcValue 's. */
        
        // initializing TokenList.
        struct Token s[MAXSIZE];
        void **TokenList= (void*)&s;

        // Access oTokens. 
        DynArray_toArray(oTokens, TokenList);
        struct Token** tokens = (struct Token **) TokenList;

        // Check if pipeline is in argvp.
        for (i=0; i< length ; i++)
          if (tokens[i]->eType == PIPELINE) ispipe=1;
        
        for (i=0; i< length ; i++)
          *(argvp+i)= tokens[i]->pcValue;

        /*-----------------------------------------------------------*
          handling all commands
        -------------------------------------------------------------*/
        // printf("%d\n", length );
        // int done = 0;


        /*---------------------------------------------------------*
          built-in commands
        -----------------------------------------------------------*/
        a = cmdproc(argvp);
        if(a == 0) { // built-in command
          for(i=0; i<length; i++) argvp[i]=NULL;
          continue;
        } 
        else if(a == 2){ //// if exit, ret=2
          fclose(f);
          for(i=0; i<length; i++) argvp[i]=NULL;
          DynArray_map(oTokens, freeToken, NULL);
          DynArray_free(oTokens);
          exit(0);
        } 
        else if(a == -1){
          for(i=0; i<length; i++) argvp[i]=NULL;
          continue;
        }
        /*---------------------------------------------------------*
          non built-in commands -> make child process
        -----------------------------------------------------------*/
        if (_fork(argvp)==-1){
          for(i=0; i<length; i++) argvp[i]=NULL;
            continue;
        }
      }

      /*-------------------------------------------------------------*
        Preparing next command line. (free all variables)
      ---------------------------------------------------------------*/
      ispipe=0;
      for(i=0; i<length; i++) argvp[i]=NULL;
      DynArray_map(oTokens, freeToken, NULL);
      DynArray_free(oTokens);
    }
  }
  if(f!=NULL) fclose(f);
  fflush(NULL);

  /*-----------------------------------------------------------------*
     get input from stdin.
  -------------------------------------------------------------------*/
  for(printf("%% "); fgets(command,MAXSIZE,stdin);printf("%% ")){
    fflush(stdout);
    /*---------------------------------------------------------------*
      Check the length of command line.
    -----------------------------------------------------------------*/
    if (strcmp(command, "\n")==0) continue;
    if (strlen(command) > MAXSIZE-1)
      fprintf(stderr, "%s: Input line is too long\n",argv[0]);
    else { // if command is not too long,
      oTokens = DynArray_new(0);
      if (oTokens == NULL) {
        fprintf(stderr, "%s: Cannot allocate memory\n",argv[0]);
        exit(EXIT_FAILURE);
      }
      
      /*-------------------------------------------------------------*
        Check if command is valid.
      ---------------------------------------------------------------*/
      iSuccessful = lexLine(command, oTokens) && synLine(oTokens);
      int length = DynArray_getLength(oTokens);
      char *argvp[MAXSIZE];
      if (iSuccessful) {  
        /* making array of Token->pcValue 's. */
        
        // initializing TokenList.
        struct Token s[MAXSIZE];
        void **TokenList= (void*)&s;

        // Access oTokens. 
        DynArray_toArray(oTokens, TokenList);
        struct Token** tokens = (struct Token **) TokenList;
        
        // Make char** type variable, argvp. 
        for (i=0; i< length ; i++)
          *(argvp+i)= tokens[i]->pcValue;
        
        /*-----------------------------------------------------------*
          handling all commands
        -------------------------------------------------------------*/
        fflush(stdout);

        /*---------------------------------------------------------*
          built-in commands
        -----------------------------------------------------------*/
        a= cmdproc(argvp);
        if(a == 1) { // not built-in command
          // for(i=0; i<length; i++) argvp[i]=NULL;
          // continue;
        } 
        else if(a == 2){
          DynArray_map(oTokens, freeToken, NULL);
          DynArray_free(oTokens);
          for(i=0; i<length; i++) argvp[i]=NULL;
          exit(0);
        }
        else if(a == -1){
          for(i=0; i<length; i++) argvp[i]=NULL;
          continue;
        }        
        /*---------------------------------------------------------*
          non built-in commands -> make child process
        -----------------------------------------------------------*/
        if (_fork(argvp)==-1){
          for(i=0; i<length; i++) argvp[i]=NULL;
            continue;
        }
      }
      /*-------------------------------------------------------------*
        Preparing next command line. (free all variables)
      ---------------------------------------------------------------*/
      ispipe=0;
      for(i=0; i<length; i++) argvp[i]=NULL;
      DynArray_map(oTokens, freeToken, NULL);
      DynArray_free(oTokens);
    }
  }
//fflush(NULL); //do we need this
}
