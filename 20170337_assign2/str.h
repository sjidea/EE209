/*Sojung Son 20170337 assignment 2 sgrep.c*/
#ifndef _STR_H_
#define _STR_H_
#include <unistd.h> /* for typedef of size_t */

/* Part 1 */
//StrGetLength counts the length of the given string
//gets pointer variable and return an integer of type size_t
size_t StrGetLength(const char* pcSrc);

//StrCopy copies a string(source) to an address(destination)
//gets two pointer variables and returns the address
char *StrCopy(char *pcDest, const char* pcSrc);

//StrCompare compares two string
//gets two painter variables and returns an integer
int StrCompare(const char* pcS1, const char* pcS2);

//StrSearch searches a string(needle) in another string(Haystack)
//gets two pointer variables and returns the address of Needle (if found)
//if needle is not found, then return null
//needle is an empty string, return the initial address of Haystack
char *StrSearch(const char* pcHaystack, const char *pcNeedle);

//StrConcat extends the string pcSrc after pcDest
//gets two string with address and returns an address of the string
char *StrConcat(char *pcDest, const char* pcSrc);

#endif /* _STR_H_ */