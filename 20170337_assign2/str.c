/*Sojung Son 20170337 assignment 2 sgrep.c*/
#include <assert.h> /* to use assert() */
#include <stdio.h>
#include "str.h"

/* Your task is: 
   1. Rewrite the body of "Part 1" functions - remove the current
      body that simply calls the corresponding C standard library
      function.
   2. Write appropriate comment per each function
*/

/* Part 1 */
/*------------------------------------------------------------------------*/
//StrGetLength counts the length of the given string
//gets pointer variable and return an integer of type size_t
size_t StrGetLength(const char* pcSrc)
{
  const char *pcEnd;
  assert(pcSrc); /* NULL address, 0, and FALSE are identical. */
  pcEnd = pcSrc;
	
  while (*pcEnd) /* null character and FALSE are identical. */
    pcEnd++;

  return (size_t)(pcEnd - pcSrc);
}

/*------------------------------------------------------------------------*/
//StrCopy copies a string(source) to an address(destination)
//gets two pointer variables and returns the address
char *StrCopy(char *pcDest, const char* pcSrc)
{
  /* TODO: fill this function */
  char *pcDest1; //initial value of pcDest
  assert(pcSrc);
  assert(pcDest);
  pcDest1 = pcDest;

/*if there is nothing to copy, just return pcDest*/
  if(!(*pcSrc)){ 
    *pcDest1=*pcSrc;
  }

  while(*pcSrc) {  /*copy the value in Source to Destination*/
    *pcDest = *pcSrc;
    pcDest++;
    pcSrc++;
  }
  *pcDest = *pcSrc;/*copy NULL at the end of pcDest*/

  return pcDest1;
}

/*------------------------------------------------------------------------*/
//StrCompare compares two string
//gets two painter variables and returns an integer
int StrCompare(const char* pcS1, const char* pcS2)
{
  /* TODO: fill this function */

  assert(pcS1);
  assert(pcS2);


  while(*pcS1==*pcS2){
    if (*pcS1==0) return 0; //two string is the same
    pcS1++;
    pcS2++;
  }

  return(*pcS1-*pcS2);
}

/*------------------------------------------------------------------------*/
//StrSearch searches a string(needle) in another string(Haystack)
//gets two pointer variables and returns the address of Needle (if found)
//if needle is not found, then return null
//needle is an empty string, return the initial address of Haystack
char *StrSearch(const char* pcHaystack, const char *pcNeedle){
  /* TODO: fill this function */
  //  if(pcNeedle=null) what should i do?

   const char *pcHaystack1;
   const char *pcNeedle1; 
  assert(pcHaystack);
  assert(pcNeedle); 

  if(*pcNeedle==0) return (char *)pcHaystack;
 
 /*check the string for every single character in Haystack*/
  for( ; *pcHaystack!=0; pcHaystack++){ 
    pcNeedle1 = pcNeedle; /*this is to remember the string in Needle*/
    if (*pcHaystack != *pcNeedle1) continue;
/*if first char of string matches, remember the address*/
    pcHaystack1 = pcHaystack;
    while(1) {
      if(*pcNeedle1 ==0) return (char *)pcHaystack;
      if(*pcHaystack1++!=*pcNeedle1++) break;
    }
  }

  return 0;
}


/*------------------------------------------------------------------------*/
//StrConcat extends the string pcSrc after pcDest
//gets two string with address and returns an address of the string
char *StrConcat(char *pcDest, const char* pcSrc){
  /* TODO: fill this function */

  char *pcDest1;
  assert(pcDest);
  assert(pcSrc);
  pcDest1 = pcDest;

  while(*pcDest) { //get to the end of the string pcDest
    pcDest++;
  } 

  while(*pcSrc){ //copies one character by one character
    *pcDest = *pcSrc;
    pcDest++;
    pcSrc++;  
  } 

  *pcDest = *pcSrc; //adds a null character at the end of the string
  
  return pcDest1;
}

