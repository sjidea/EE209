/*Sojung Son 20170337 assignment 2 sgrep.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* for skeleton code */
#include <unistd.h> /* for getopt */
#include "str.h"

#define FIND_STR        "-f"
#define REPLACE_STR     "-r"
#define DIFF_STR        "-d"

#define MAX_STR_LEN 1023

#define FALSE 0
#define TRUE  1

typedef enum {
  INVALID,
  FIND,
  REPLACE,
  DIFF
} CommandType;

/*
 * Fill out your functions here (If you need) 
 */

/*--------------------------------------------------------------------*/
/* PrintUsage()
   print out the usage of the Simple Grep Program                     */
/*--------------------------------------------------------------------*/
void 
PrintUsage(const char* argv0) 
{
  const static char *fmt = 
	"Simple Grep (sgrep) Usage:\n"
	"%s [COMMAND] [OPTIONS]...\n"
	"\nCOMMNAD\n"
	"\tFind: -f [search-string]\n"
	"\tReplace: -r [string1] [string2]\n"
	"\tDiff: -d [file1] [file2]\n";

  printf(fmt, argv0);
}
/*-------------------------------------------------------------------*/
/* DoFind()
   Your task:
   1. Do argument validation 
   - String or file argument length is no more than 1023
   - If you encounter a command-line argument that's too long, 
   print out "Error: argument is too long"
   
   2. Read the each line from standard input (stdin)
   - If you encounter a line larger than 1023 bytes, 
   print out "Error: input line is too long" 
   - Error message should be printed out to standard error (stderr)
   
   3. Check & print out the line contains a given string (search-string)
	  
   Tips:
   - fgets() is an useful function to read characters from file. Note 
   that the fget() reads until newline or the end-of-file is reached. 
   - fprintf(sderr, ...) should be useful for printing out error
   message to standard error

   NOTE: If there is any problem, return FALSE; if not, return TRUE  */
/*-------------------------------------------------------------------*/
int
DoFind(const char *pcSearch)
{
  char buf[MAX_STR_LEN + 2]; 
  int len;
  /* 
   *  Fill out your variables here 
   */   
  /* Read the line by line from stdin, Note that this is an example */
//print error messages for error cases and return False
if ((len = StrGetLength(pcSearch)) > MAX_STR_LEN) {
  fprintf(stderr, "Error: argument is too long\n");
  return FALSE;
}
  while (fgets(buf, sizeof(buf), stdin)) {
	/* check input line length */
	if ((len = StrGetLength(buf)) > MAX_STR_LEN) {
	  fprintf(stderr, "Error: input line is too long\n");
	  return FALSE;
	}

	/* TODO: fill out this function */

	while (*buf) { //Search string pcSearch in the given file
		if(StrSearch(buf, pcSearch)){
			printf("%s", buf);
			break;
		}
		else break;
	}
  }   
  return TRUE;
}
/*-------------------------------------------------------------------*/
/* DoReplace()
   Your task:
   1. Do argument validation 
	  - String length is no more than 1023
	  - If you encounter a command-line argument that's too long, 
		print out "Error: argument is too long"
	  - If word1 is an empty string,
		print out "Error: Can't replace an empty substring"
	  
   2. Read the each line from standard input (stdin)
	  - If you encounter a line larger than 1023 bytes, 
		print out "Error: input line is too long" 
	  - Error message should be printed out to standard error (stderr)

   3. Replace the string and print out the replaced string

   NOTE: If there is any problem, return FALSE; if not, return TRUE  */
/*-------------------------------------------------------------------*/
int 
DoReplace(const char *pcString1, const char *pcString2)
{
  /* TODO: fill out this function */  
  char buf[MAX_STR_LEN + 2]; 
  int len;
  int len1 = (int)StrGetLength(pcString1);
  int i;
  char *bufff;
  char *rbufff;

//print error messages for error cases and return False
	if ((len=StrGetLength(pcString1)) > MAX_STR_LEN) {
		fprintf(stderr, "Error: argument is too long\n");
		return FALSE;
  }
	if ((len=StrGetLength(pcString2)) > MAX_STR_LEN) {
		fprintf(stderr, "Error: argument is too long\n");
		return FALSE;
  }

  while (fgets(buf, sizeof(buf), stdin)) {
	if ((len = StrGetLength(buf)) > MAX_STR_LEN) {
		fprintf(stderr, "Error: input line is too long\n");
		return FALSE;
	}

	if(*pcString1==0){
		fprintf(stderr, "Error: Can't replace an empty string\n");
                return FALSE;
	}


	bufff = buf; //initialize bufff for every line 

	while(1) {
		if (StrSearch(bufff, pcString1)) { //if pcString1 exists in bufff
			rbufff = bufff; //initialize rbufff 
			for(i=0;i<(StrSearch(bufff,pcString1))-bufff;i++){
				printf("%c", *rbufff++);
			} //copy characters just before pcString1
			bufff = rbufff;
			printf("%s", pcString2); //copy pcString2
			//make bufff point the address after pcString1
			rbufff = bufff + len1; 
			bufff = rbufff;
		}
		else break;
	}

	printf("%s", bufff);

  } 
  return TRUE;
}
/*-------------------------------------------------------------------*/
/* DoDiff()
   Your task:
   1. Do argument validation 
	 - file name length is no more than 1023
	 - If a command-line argument is too long, 
	   print out "Error: arugment is too long" to stderr

   2. Open the two files
	  - The name of files are given by two parameters
	  - If you fail to open either file, print out error messsage
	  - Error message: "Error: failed to open file [filename]\n"
	  - Error message should be printed out to stderr

   3. Read the each line from each file
	  - If you encounter a line larger than 1023 bytes, 
		print out "Error: input line [filename] is too long" 
	  - Error message should be printed out to stderr

   4. Compare the two files (file1, file2) line by line 

   5. Print out any different line with the following format
	  file1@linenumber:file1's line
	  file2@linenumber:file2's line

   6. If one of the files ends earlier than the other, print out an
	  error message "Error: [filename] ends early at line XX", where
	  XX is the final line number of [filename].

   NOTE: If there is any problem, return FALSE; if not, return TRUE  */
/*-------------------------------------------------------------------*/
int
DoDiff(const char *file1, const char *file2)
{
  /* TODO: fill out this function */

	FILE *psFile1;
	FILE *psFile2; //declare pointer variables 
	int len;

//print error messages for error cases and return False
	if ((len=StrGetLength(file1)) > MAX_STR_LEN||(len=StrGetLength(file2)) > MAX_STR_LEN) {
		fprintf(stderr, "Error: argument is too long\n");
		return FALSE;
  }

	psFile1 = fopen(file1, "r");
	psFile2 = fopen(file2, "r");
	if (!psFile1){
		fprintf(stderr, "Error : failed to open file [%s]\n", file1);
		return FALSE;
	}
	if (!psFile2) {
		fprintf(stderr, "Error : failed to open file [%s]\n", file2);
		return FALSE;
	}

	char buf1[MAX_STR_LEN+2];
	char buf2[MAX_STR_LEN+2];
	char *line1;
	char *line2;
	int line_num=0;
	char *A, *B;

	while(1){
		line_num++; //count the line of the file
		A=fgets(buf1, sizeof(buf1), psFile1);
		line1 = buf1;
		if (StrGetLength(line1) > MAX_STR_LEN) {
			fprintf(stderr, "Error: input line [%s] is too long\n", file1);
			return FALSE;
		}
		B=fgets(buf2, sizeof(buf2), psFile2);
		line2 = buf2;
		if (StrGetLength(line2) > MAX_STR_LEN) {
			fprintf(stderr, "Error: input line [%s] is too long\n", file2);
			return FALSE;
		}

		if ((A!=NULL)&&(B!=NULL)){ //if two files did not end
			if(StrCompare(line1, line2)){
				printf("%s@%d:%s", file1, line_num, line1);
				printf("%s@%d:%s", file2, line_num, line2);
			}
		}
//either of the file ended
//i did not index in else if function because they are too long
		else if ((A==NULL)&&(B!=NULL)){ 
		fprintf(stderr,"Error : [%s] ends early at line %d\n",file1,line_num-1);
			return FALSE;
		} 
		else if ((B==NULL)&&(A!=NULL)) {
		fprintf(stderr,"Error : [%s] ends early at line %d\n",file2,line_num-1);
			return FALSE;
		}
		else break; //two files ended at the same time
	}

	return TRUE;
}
/*-------------------------------------------------------------------*/
/* CommandCheck() 
   - Parse the command and check number of argument. 
   - It returns the command type number
   - This function only checks number of argument. 
   - If the unknown function is given or the number of argument is 
   different from required number, this function returns FALSE.
   
   Note: You SHOULD check the argument rule later                    */
/*-------------------------------------------------------------------*/ 
int
CommandCheck(const int argc, const char *argv1)
{
  int cmdtype = INVALID;
   
  /* check minimum number of argument */
  if (argc < 3)
	return cmdtype;
   
  /* check command type */ 
  if (strcmp(argv1, FIND_STR) == 0) {
	if (argc != 3)
	  return FALSE;    
	cmdtype = FIND;       
  }
  else if (strcmp(argv1, REPLACE_STR) == 0) {
	if (argc != 4)
	  return FALSE;
	cmdtype = REPLACE;
  }
  else if (strcmp(argv1, DIFF_STR) == 0) {
	if (argc != 4)
	  return FALSE;
	cmdtype = DIFF;
  }
   
  return cmdtype;
}
/*-------------------------------------------------------------------*/
int 
main(const int argc, const char *argv[]) 
{
  int type, ret;
   
  /* Do argument check and parsing */
  if (!(type = CommandCheck(argc, argv[1]))) {
	fprintf(stderr, "Error: argument parsing error\n");
	PrintUsage(argv[0]);
	return (EXIT_FAILURE);
  }
   
  /* Do appropriate job */
  switch (type) {
  case FIND:
	ret = DoFind(argv[2]);
	break;
  case REPLACE:
	ret = DoReplace(argv[2], argv[3]);
	break;
  case DIFF:
	ret = DoDiff(argv[2], argv[3]);
	break;
  } 

  return (ret)? EXIT_SUCCESS : EXIT_FAILURE;
}
