// validity_test.c
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  File Name : validity_test.c                                      */
/*  Author: 박지현(20170285), 손소정(20170337)                          */
/*  Description: parsing command line                                */
/*                                                                   */
/*-------------------------------------------------------------------*/

#include "ish.h"

// enum TokenType {TOKEN, PIPELINE}; // 0 and 1 set! 
// enum {FALSE, TRUE};
// struct Token
// {
//    enum TokenType eType;  //The type of the token. 
//    char *pcValue; /* The string which is the token's value. */
// };

/*-------------------------------------------------------------------*
   Function : freeToken                                              *
   ============================================                      *
   Input    : Token                                                  *
   Output   : (no output)                                            *
   Purpose  : delete(free) token                                     *
---------------------------------------------------------------------*/
void freeToken(void *pvItem, void *pvExtra)
{
   struct Token *psToken = (struct Token*)pvItem;
   free(psToken->pcValue);
   free(psToken);
}

/*-------------------------------------------------------------------*
   Function : printToken                                             *
   ============================================                      *
   Input    : Token                                                  *
   Output   : (no output)                                            *
   Purpose  : Print token pvItem to stdout. pvExtra is unused.       *
---------------------------------------------------------------------*/
// static void printToken(void *pvItem, void *pvExtra)
// {
//    struct Token *psToken = (struct Token*)pvItem;
//    printf("%s ", psToken->pcValue);
// }

/*-------------------------------------------------------------------*
   Function : makeToken                                              *
   ============================================                      *
   Input    : TokenType, pcValue                                     *
   Output   : Token* (Token pointer)                                 *
   Purpose  : Create and return a Token whose type is eTokenType and *
              whose value is pcValue. Return NULL if insufficient    *
              memory is available. The caller owns the Token.        *
---------------------------------------------------------------------*/
static struct Token *makeToken(enum TokenType eTokenType,
   char *pcValue)
{
   struct Token *psToken;

   psToken = (struct Token*)malloc(sizeof(struct Token));
   if (psToken == NULL)
      return NULL;

   psToken->eType = eTokenType;

   psToken->pcValue = (char*)malloc(strlen(pcValue) + 1);
   if (psToken->pcValue == NULL)
   {
      free(psToken);
      return NULL;
   }

   strcpy(psToken->pcValue, pcValue);

   return psToken;
}

/*-------------------------------------------------------------------*
   Function : lexLine                                                *
   ============================================                      *
   Input    : pcLine, oTokens(dynamic array)                         *
   Output   : static int : 1(True) or 0(False)                       *
   Purpose  : Lexically analyze string pcLine. Populate oTokens with *
              the tokens that pcLine contains. Return 1(TRUE) if     *
              successful, or 0(FALSE) otherwise.                     *
              The caller owns the tokens placed in oTokens.          *
---------------------------------------------------------------------*/
int lexLine(const char *pcLine, DynArray_T oTokens)
{
   enum LexState{START,IN_TOKEN,IS_PIPELINE,QUOTE,QUOTE_PAIR};
   enum LexState eState = START;  // Initial state is START.

   int iLineIndex = 0;
   int iValueIndex = 0;
   char c;
   char acValue[MAXSIZE];
   struct Token *psToken;

   assert(pcLine != NULL);
   assert(oTokens != NULL);

   for (;;)
   {
      /* "Read" the next character from pcLine. */
      c = pcLine[iLineIndex++];

      switch (eState)
      {
         case START:
            if ((c == '\n') || (c == '\0'))
               return TRUE;
            else if (isspace(c))
               eState = START;
            else if (c== '"')
               eState = QUOTE;
            else if (c=='|')
            {
               // make token "|"
               acValue[0] = '|';
               acValue[1] = '\0';
               psToken = makeToken(PIPELINE, acValue);
               if (psToken == NULL)
               {
                     fprintf(stderr, "./ish: Cannot allocate memory\n");
                  return FALSE;
               }
               if (!DynArray_add(oTokens, psToken))
               {
                     fprintf(stderr, "./ish: Cannot allocate memory\n");
                  return FALSE;
               }
               iValueIndex=0;
            }
            else // case of c is one of another characters
            {
               acValue[iValueIndex++] = c;
               eState = IN_TOKEN;
            }
            break;

         case IN_TOKEN:
            if ((c == '\n') || (c == '\0'))
            {
               /* Create a token. */
               acValue[iValueIndex] = '\0';
               psToken = makeToken(TOKEN, acValue);
               if (psToken == NULL)
               {
                  fprintf(stderr, "./ish: Cannot allocate memory\n");
                  return FALSE;
               }
               if (!DynArray_add(oTokens, psToken))
               {
                  fprintf(stderr, "./ish: Cannot allocate memory\n");
                  return FALSE;
               }
               iValueIndex = 0;
               strcpy(acValue,"");
               eState = START;
               return TRUE;
            }
            else if (isspace(c))
            {
               /* Create a token. */
               acValue[iValueIndex] = '\0';
               psToken = makeToken(TOKEN, acValue);
               if (psToken == NULL)
               {
                  fprintf(stderr, "./ish: Cannot allocate memory\n");
                  return FALSE;
               }
               if (! DynArray_add(oTokens, psToken))
               {
                  fprintf(stderr, "./ish: Cannot allocate memory\n");
                  return FALSE;
               }
               iValueIndex = 0;
               strcpy(acValue,"");
               eState = START;
            }
            else if (c=='"')
               eState = QUOTE;
            else if (c=='|')
            {
               // make tokens with the word stored
               acValue[iValueIndex]='\0';
               psToken = makeToken(TOKEN, acValue);
               if (psToken == NULL)
               {
                  fprintf(stderr, "./ish: Cannot allocate memory\n");
                  return FALSE;
               }
               if (! DynArray_add(oTokens, psToken))
               {
                  fprintf(stderr, "./ish: Cannot allocate memory\n");
                  return FALSE;
               }
               // make token "|"
               acValue[0] = '|';
               acValue[1] = '\0';
               psToken = makeToken(PIPELINE, acValue);
               if (psToken == NULL)
               {
                     fprintf(stderr, "./ish: Cannot allocate memory\n");
                  return FALSE;
               }
               if (!DynArray_add(oTokens, psToken))
               {
                     fprintf(stderr, "./ish: Cannot allocate memory\n");
                  return FALSE;
               }

               iValueIndex = 0;
               strcpy(acValue,"");
               eState = START;
            }
            else // case of c is one of anothere characters
               acValue[iValueIndex++] = c;
            break;

         case QUOTE:
            if ((c == '\n') || (c == '\0'))
            {
               /* There is no quote pair. Print error message. */
               fprintf(stderr, "./ish: Could not find quote pair\n");
               return FALSE;
            }
            else if (c == '"')
               eState = IN_TOKEN;
            else
               acValue[iValueIndex++] = c;
            break;

         default:
            assert(FALSE);
      }
   }
}

/*-------------------------------------------------------------------*
   Function : synLine                                                *
   ============================================                      *
   Input    : oTokens(dynamic array)                                 *
   Output   : static int : 1(True) or 0(False)                       *
   Purpose  : Syntactically analyze string pcLine. Return 1(TRUE) if *
              successful, or 0(FALSE) otherwise. The caller owns the *
              tokens placed in oTokens.                              *
---------------------------------------------------------------------*/
int synLine(DynArray_T oTokens)
{
   struct Token s[MAXSIZE];
   void **TokenList= (void*)&s;
   // initializing TokenList.

   DynArray_toArray(oTokens, TokenList);
   struct Token** tokens = (struct Token **) TokenList;
   // Purpose of upper process is to access oTokens. 
   
   struct Token *token;
   int length = DynArray_getLength(oTokens);
   
   ///////////////////////////////////////////////////////////////////
   //
   // [ handling pipe lines ]
   //
   // if first command is |, print error message
   if (tokens[0]->eType == PIPELINE){
      fprintf(stderr, "./ish: Missing Command name \n");
      return FALSE;  }
   // If first command is not '|', and the only token -> return True.
   if (length==1) return TRUE;
   
   // if last command is |, print error message
   if (tokens[length-1]->eType == PIPELINE){
      fprintf(stderr,
            "./ish: Pipe or redirection destination not specified\n");
      return FALSE;  }

   // if '|', both previous and next token type should be TOKEN
   int index=1;
   while( index < length-1 ){
      token = tokens[index];
      if(token->eType == PIPELINE){
         if(tokens[index-1]->eType == TOKEN && 
                               tokens[index+1]->eType == TOKEN);
         else {
            fprintf(stderr,
             "./ish: Pipe or redirection destination not specified\n");
            return FALSE;  
         }
      }
      index++;
   }
   return TRUE;
}
