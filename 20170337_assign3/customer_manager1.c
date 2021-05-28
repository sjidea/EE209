/* SoJung Son, Assignment3, customer_manager1.c*/
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "customer_manager.h"

#define UNIT_ARRAY_SIZE 1024

//structure which consists information of a user
struct UserInfo {
  char *name;                // customer name
  char *id;                  // customer id
  int purchase;              // purchase amount (> 0)
};

//structure to save information of users
//keep track of number of userinfo
struct DB {        
  struct UserInfo *pArray;   // pointer to the array
  int curArrSize;            // current array size (max # of elements)
  int numItems;              // # of stored items, needed to determine
			     // # whether the array should be expanded
			     // # or not
};

/*--------------------------------------------------------------------*/
//create a DB
//returns a pointer to DB
//returns NULL for any error cases
DB_T
CreateCustomerDB(void) 
{
  // create new DB
  DB_T d;
  d = (DB_T) calloc(1, sizeof(struct DB)); 
  if (d == NULL) {
    fprintf(stderr, "Can't allocate a memory for DB_T\n");
    return NULL;
  }
  d->curArrSize = UNIT_ARRAY_SIZE; // start with 1024 elements
  d->pArray = (struct UserInfo *)calloc(d->curArrSize,
               sizeof(struct UserInfo));
  if (d->pArray == NULL) {
    fprintf(stderr, "Can't allocate a memory for array of size %d\n",
	    d->curArrSize);   
    free(d);
    return NULL;
  }
  return d;
}

/*--------------------------------------------------------------------*/
//destroys (deletes) DB
//returns nothing (void)
//gets pointer struct DB
void
DestroyCustomerDB(DB_T d)
{
  //do nothing if d does not exist
  assert(d);

  //remember the initial point of d->pArray
  struct UserInfo *ipArray = d->pArray;

  //free pointer of name and id
  //malloc at RegisterCustomer>strdup
  while(d->pArray->purchase>0){
    // d->pArray->name = d->pArray->id = NULL; /////////////////////
    free(d->pArray->name);
    free(d->pArray->id);
    // d->pArray->purchase = 0; ////////////////////////////////////
    (d->pArray)++;
  }

  //free d->pArray
  //calloc at CreateCustomerDB
  d->pArray = ipArray;
  free(d->pArray);
  // d->pArray = NULL; ///////////////////////////////////////////////

  //free d
  //calloc at CreateCustomerDB
  free(d);
  // d=NULL; /////////////////////////////////////////////////////////
}

/*--------------------------------------------------------------------*/
//registers an information of an user in DB
//returns -1 for any failure, 0 for success
//gets pointer of struct DB, id(pointer), name(pointer), and purchase
int
RegisterCustomer(DB_T d, const char *id,
		 const char *name, const int purchase)
{
  //error cases
  if(d==NULL||id==NULL||name==NULL) return (-1);
  if(purchase<=0) return (-1);

  //remember the initial point of d->pArray
  struct UserInfo *ipArray = d->pArray;

  //if id or name already exists
  if(GetPurchaseByID(d, id)>0) return (-1);
  if(GetPurchaseByName(d, name)>0) return (-1);

  //expand d->pArray when allocated memory is not enough
  if(d->numItems==d->curArrSize){
    //initialize new variables
  	struct UserInfo *newArray = d->pArray;
  	int newArrSize=d->curArrSize;
    d->pArray = (struct UserInfo *)realloc(d->pArray, 
      sizeof(struct UserInfo)*(newArrSize+UNIT_ARRAY_SIZE));
    //if realloc failed
	  if (d->pArray == NULL) {
  	  fprintf(stderr, "Can't allocate a memory for array of size %d\n",
	  	  (newArrSize+UNIT_ARRAY_SIZE)); 
	  	d->pArray = newArray;
  	  return (-1);
  	}

    //initialize the newly allocated memory
  	int i;
  	ipArray = d->pArray;
    //pass the previous memory saved
  	for(i=1; i<newArrSize; i++) (d->pArray)++;
  	for(i=0; i<UNIT_ARRAY_SIZE; i++){
  		(d->pArray)++;
  		d->pArray->name = d->pArray->id = NULL;
  		d->pArray->purchase = 0;
  	}
  	d->curArrSize = newArrSize + UNIT_ARRAY_SIZE;
  	d->pArray = ipArray;
  }

  //find an empty space, store new data
  while (d->pArray->purchase>0) (d->pArray)++;

  //copy string into d
  free(d->pArray->name);
  free(d->pArray->id);
  d->pArray->name= strdup(name);
  d->pArray->id=strdup(id);
  d->pArray->purchase = purchase;

  (d->numItems)++;
  d->pArray = ipArray;
  return 0;
}

/*--------------------------------------------------------------------*/
//deletes an information of an user of id
//returns -1 for any failure, 0 for success
//gets pointer of sturct DB and id(pointer)
int
UnregisterCustomerByID(DB_T d, const char *id)
{
  //error cases
  if(d==NULL||id==NULL) return (-1);

  int i=1;

  //remember the initial point of d->pArray
  struct UserInfo *ipArray = d->pArray;
  struct UserInfo *cpArray;

  //if ID does not exist
  if(GetPurchaseByID(d, id)<=0) return (-1);


  //pass until finding userinfo of same id
  while(d->pArray->purchase>0){
   	if(strcmp(d->pArray->id, id)) {
   		i++;
   		(d->pArray)++;    		
   	}
   	else break;
   }
  //pull one userinfo one by one
  //unregister by replacing with the following userinfo
   if(i<d->numItems){
 		cpArray = d->pArray;
   	while(i++<d->numItems){
   		cpArray++;
      free(d->pArray->name);
      free(d->pArray->id);
   		d->pArray->name = strdup(cpArray->name);
      // free(cpArray->name);
   		d->pArray->id = strdup(cpArray->id);
      // free(cpArray->id);
   		d->pArray->purchase = cpArray->purchase;
   		d->pArray++;
   	}
   }
  //delete the last element

  free(d->pArray->name);
  free(d->pArray->id);
  d->pArray->name = d->pArray->id = NULL;
 	d->pArray->purchase=0;

 	d->pArray = ipArray;    
 

  d->numItems--;
  return (0);
}

/*--------------------------------------------------------------------*/
//deletes an information of an user of name
//returns -1 for any failure, 0 for success
//gets pointer of sturct DB and name(pointer)
int
UnregisterCustomerByName(DB_T d, const char *name)
{
  /* fill out this function */
  if(d==NULL||name==NULL) return (-1);

  //if Name does not exist
  if(GetPurchaseByName(d, name)<=0) return (-1);

	int i=1;

  //remember the initial point of d->pArray
	struct UserInfo *ipArray = d->pArray;
  struct UserInfo *cpArray;

  //pass until finding userinfo of same name
  while(d->pArray->purchase>0){
   	if(strcmp(d->pArray->name, name)) {
   		i++;
   		(d->pArray)++;    		
   	}
   	else break;
  }

  //pull one userinfo one by one
  //unregister by replacing with the following userinfo
  if(i<d->numItems){
   	cpArray = d->pArray;
   	while(i++<d->numItems){
   		cpArray++;
      free(d->pArray->name);
      free(d->pArray->id);
   		d->pArray->name = strdup(cpArray->name);
      // free(cpArray->name);
  		d->pArray->id = strdup(cpArray->id);
      // free(cpArray->id);
 		d->pArray->purchase = cpArray->purchase;
		d->pArray++;
  	}
  }
    //delete the last element

  free(d->pArray->name);
  free(d->pArray->id);
  d->pArray->name = d->pArray->id = NULL;
 	d->pArray->purchase=0;

 	d->pArray = ipArray;

  d->numItems--;
  return (0);
}

/*--------------------------------------------------------------------*/
//find out the purchase knowing the id of the user
//returns purchase of the user if success, and returns -1 for failure
//gets a pointer of struct DB and id(pointer)
int
GetPurchaseByID(DB_T d, const char* id)
{
  //error cases
  if(d==NULL||id==NULL) return (-1);

  //remember the initial point of d->pArray
  struct UserInfo *ipArray = d->pArray;

  int i;
  int a=0;

  //look for id
  while(a++<d->numItems){
  	if(strcmp(d->pArray->id, id)==0){ 
  		i=d->pArray->purchase;
  		d->pArray = ipArray;
  		return i;
  	}
  	else (d->pArray)++;
  }

  d->pArray = ipArray;
  return (-1);
}

/*--------------------------------------------------------------------*/
//find out the purchase knowing the name of the user
//returns purchase of the user if success, and returns -1 for failure
//gets a pointer of struct DB and name(pointer)
int
GetPurchaseByName(DB_T d, const char* name)
{
  /* fill out this function */
  if(d==NULL||name==NULL) return (-1);
  //remember the initial point of d->pArray
  struct UserInfo *ipArray = d->pArray;

  int i;
  int a =0;

  //look for name
  while(a++<d->numItems){
  	if(strcmp(d->pArray->name, name)==0){
  			i= d->pArray->purchase;
  			d->pArray = ipArray;
  			return i;
  		}
  	else (d->pArray)++;
  }

  d->pArray = ipArray;
  return (-1);
}
/*--------------------------------------------------------------------*/
//adds the sum of function fp of all users
//returns the sum
//gets pointer of DB and pointer of function
int
GetSumCustomerPurchase(DB_T d, FUNCPTR_T fp)
{
  /* fill out this function */
  if(d==NULL||fp==NULL) return (-1);

  int i=0;

  //remember the initial point of d->pArray
  struct UserInfo *ipArray = d->pArray;

  //get the sum of purchase which fulfil the function
  int j=1;
  do{
    i += fp(d->pArray->id, d->pArray->name, d->pArray->purchase);
    (d->pArray)++;
  } while (j++<d->numItems);

  d->pArray = ipArray;
  return i;
}