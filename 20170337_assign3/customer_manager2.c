/* SoJung Son, Assignment3, customer_manager2.c*/
#include <assert.h>
#include <assert.h>  //
#include <stdlib.h>  //
#include <stdio.h>  //
#include <string.h>  //
#include "customer_manager.h"  //

enum { BUCKET_COUNT = 1024 };
enum { HASh_MULTIPLIER = 65599 };

#define UNIT_BUCKET_SIZE 1024

/*-------------------------------------------------------------------*/

//structure which consists information of a user
struct UserInfo{
	const char *id;             //customer id
	const char *name;           //customer name
	int purchase;               //purchase amount (>0)
	struct UserInfo *next_id;   //points the next userinfo of same hash
	struct UserInfo *next_name; //points the next userinfo of same hash
};

//structure which consists an pointer to array
//each array points UserInfo
struct Table{
	struct UserInfo *array[BUCKET_COUNT]; 
	//array which represents each hash
};

////structure to save information of users
//consists two tables
//keep track of number of Items and the size of hash
struct DB {
	struct Table *t_id;   //table of id
	struct Table *t_name; //table of name
	int iBucketCount;     //# of hash
	int numItems;         //# of Users
};

/*-------------------------------------------------------------------*/

/*return a hash code for pcKey that is between 0 and iBucketCount-1*/
static int hash_function(const char *pcKey, int iBucketCount){
	int i;
	unsigned int uiHash = 0U;
	for(i=0; pcKey[i]!='\0'; i++){
		uiHash = uiHash * (unsigned int)HASh_MULTIPLIER
						+(unsigned int)pcKey[i];
	}
	return (int)(uiHash & ((unsigned int)iBucketCount-1));
}

/*-------------------------------------------------------------------*/
//create a DB
//returns a pointer to DB
//returns NULL for any error cases
DB_T
CreateCustomerDB(void) {
	//create new DB
	DB_T d; 
	d = (DB_T) calloc(1, sizeof(struct DB)); 
  if (d == NULL) {
    fprintf(stderr, "Can't allocate a memory for DB_T\n");
    return NULL;
  }
  d->iBucketCount = UNIT_BUCKET_SIZE;

 //create a table which organize information by id
	d->t_id = (struct Table *)calloc (1, sizeof(struct Table));
	if (d->t_id == NULL) {
    fprintf(stderr, "Can't allocate a memory of size %d\n", 
    	d->iBucketCount);
    free(d);
    return NULL;
  }

  //create a table which organize information by name
	d->t_name = (struct Table *)calloc (1, sizeof(struct Table));
	if (d->t_name == NULL) {
    fprintf(stderr, "Can't allocate a memory of size %d\n", 
    	d->iBucketCount);
    free(d);
    return NULL;
  }

  return d;
}

/*-------------------------------------------------------------------*/
//destroys (deletes) DB
//returns nothing (void)
//gets pointer struct DB
void
DestroyCustomerDB(DB_T d){
	//do nothing if d does not exist
	assert(d);

	struct UserInfo *p;
	struct UserInfo *nextp;

	//delete userinfo one by one
	//free table of id (t_id)
	for(int i=0; i< d->iBucketCount ; i++){
		p= d->t_id->array[i];
		//empty d->t_id->array[i]
		for(; p!=0; p=nextp){
			free((char *)p->id);
			free((char *)p->name);
			nextp = p->next_id;
			free(p);
		}
		d->t_id->array[i] = NULL;
	}

	free(d->t_id);

	//free table of name
	for(int i=0; i<d->iBucketCount ; i++){
		d->t_name->array[i] = NULL;
	}
	free(d->t_name);

	free(d);
}


/*-------------------------------------------------------------------*/
//registers an information of an user in DB
//returns -1 for any failure, 0 for success
//gets pointer of struct DB, id(pointer), name(pointer), and purchase
int
RegisterCustomer(DB_T d, const char *id, const char *name, const int purchase){
	//error cases
	if(d==NULL||id==NULL||name==NULL) return (-1);
	if(purchase<=0) return (-1);

  //if id or name already exists
  if(GetPurchaseByID(d, id)>0) return (-1);
  if(GetPurchaseByName(d, name)>0) return (-1);

  //numItems == 0.75 * iBucketCount


  //add UserInfo in DB
  struct UserInfo *p = (struct UserInfo *)malloc(sizeof(struct UserInfo));
  if(p==NULL) {
  	fprintf(stderr, "Can't allocate a memory of size %lu\n", 
  		sizeof(struct UserInfo));
  	return (-1);
  }

  //calculate the hash of id and name
  //in order to add to two tables
	int h_id = hash_function(id, d->iBucketCount);
	int h_name = hash_function(name, d->iBucketCount);

	//copy information
	p->id = strdup(id);
	p->name = strdup(name);
	p->purchase = purchase;
 
	//add to t_id
	p->next_id = d->t_id->array[h_id];
	d->t_id->array[h_id] = p;

	//add to t_name
	p->next_name = d->t_name->array[h_name];
	d->t_name->array[h_name] = p;

  (d->numItems)++;
  return 0;
}

/*-------------------------------------------------------------------*/
//deletes an information of an user of id
//returns -1 for any failure, 0 for success
//gets pointer of sturct DB and id(pointer)
int UnregisterCustomerByID(DB_T d, const char *id) {

	struct UserInfo **prevp; //declared to remember the previous address
	struct UserInfo *p;
	char *name; //declared to remember name
	struct UserInfo **nextname; //declared to remember nextname

	//error cases	
	if(d==NULL||id==NULL) return (-1);
	//if ID does not exist
	if(GetPurchaseByID(d, id)<=0) return (-1);
	
/*----------deleting from table of id--------------------*/

	int h_id = hash_function(id, d->iBucketCount);
	//initialize two variables
	prevp = &(d->t_id->array[h_id]);
	p = d->t_id->array[h_id];

	//pass until id and p->id is identical
	while(strcmp(id, p->id)!=0){
		prevp = &p;
		p = p->next_id;
	}

	//remember name to find info in t_name
	name = strdup(p->name);	
	//remember next_name to put at previous name address
	nextname = &(p->next_name);


	//fill the previous address with the next address
	//(deleting the current address of p)
	*prevp = p->next_id;


/*----------deleting from table of name------------------*/

	int h_name = hash_function(name, d->iBucketCount);
	prevp = &(d->t_name->array[h_name]);
	p = d->t_name->array[h_name];

	while(strcmp(name, p->name)!=0){
		prevp = &p;
		p = p->next_name;
	}	//same as deleting from talbe of id until here

	free(name);
	//deleting the information of p
	p->next_id = NULL;
	p->next_name = NULL;
	free((char *)p->id);
	free((char *)p->name);	
	p->id = p->name = NULL;
	// p->purchase =0; /////////////////////////////////////////

	free(p);
	//fill the previous address with the next address
	//(deleting the current address of p)
	*prevp = *nextname; 

	p=NULL;
	(d->numItems)--;
	return 0;
 }


//deletes an information of an user of name
//returns -1 for any failure, 0 for success
//gets pointer of sturct DB and id(pointer)
int UnregisterCustomerByName(DB_T d, const char *name) {

	struct UserInfo **prevp; //declared to remember the previous address
	struct UserInfo *p; 
	char *id; //declared to remember id
	struct UserInfo **nextid; //declared to remember nextid
	
	//error cases
	if(d==NULL||name==NULL) return (-1);
	//if Name does not exist
	if(GetPurchaseByName(d, name)<=0) return (-1);

/*----------deleting from table of name------------------*/	
	int h_name = hash_function(name, d->iBucketCount);
	prevp = &(d->t_name->array[h_name]);
	p = d->t_name->array[h_name];

	while(strcmp(name, p->name)!=0){
		prevp = &p;
		p = p->next_name;
	}

	id = strdup(p->id);	
	nextid = &(p->next_id);
	*prevp = p->next_name; 

/*----------deleting from table of id--------------------*/
	int h_id = hash_function(id, d->iBucketCount);
	prevp = &(d->t_id->array[h_id]);
	p = d->t_id->array[h_id];

	while(strcmp(id, p->id)!=0){
		prevp = &p;
		p = p->next_id;
	}

	free(id);
	p->next_id = NULL;
	p->next_name = NULL;
	free((char *)p->id);
	free((char *)p->name);
	p->id = p->name = NULL;


	free(p);
	*prevp = *nextid;

	p=NULL;
	(d->numItems)--;
	return 0;
}

/*-------------------------------------------------------------------*/
//find out the purchase knowing the id of the user
//returns purchase of the user if success, and returns -1 for failure
//gets a pointer of struct DB and id(pointer)
int GetPurchaseByID(DB_T d, const char *id) {

	//error cases
	if(d==NULL||id==NULL) return (-1);

	struct UserInfo *p;
	int h = hash_function(id, d->iBucketCount);

	//find id and return the appropriate purchase
	for(p= d->t_id->array[h]; p!=NULL; p=p->next_id){
		if(strcmp(id, p->id)==0) return p->purchase;
	}
	return -1;
}

//find out the purchase knowing the name of the user
//returns purchase of the user if success, and returns -1 for failure
//gets a pointer of struct DB and name(pointer)
int GetPurchaseByName(DB_T d, const char *name) {
	//same as GerPurchaseByID
	if(d==NULL||name==NULL) return (-1);
	struct UserInfo *p;
	int h = hash_function(name, d->iBucketCount);
	for(p=d->t_name->array[h]; p!=NULL; p=p->next_name){
		if(strcmp(name, p->name)==0) return p->purchase;
	}
	return -1;
}

/*-------------------------------------------------------------------*/
//adds the sum of function fp of all users
//returns the sum
//gets pointer of DB and pointer of function
int 
GetSumCustomerPurchase(DB_T d, FUNCPTR_T fp) {

	//error cases
	if(d==NULL||fp==NULL) return (-1);

	int j=0;
	struct UserInfo *p;

  //get the sum of purchase which fulfil the function
	for(int i=0; i<d->iBucketCount; i++){
		p= d->t_id->array[i];
		for(; p!=0; p=p->next_id) {
			j += fp(d->t_id->array[i]->id, d->t_id->array[i]->name, 
				      d->t_id->array[i]->purchase);
		}
	}
	return j;
}