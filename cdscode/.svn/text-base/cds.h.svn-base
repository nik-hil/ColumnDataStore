/*
 * cds.h
 *
 *  Created on: 14-Nov-2010
 *      Author: ram
 */

#ifndef CDS_H_
#define CDS_H_

/*Structures to be used in CDS*/
/*
In any function if the return type is int and
it is expected to return the status then,
on success return 0
on failure return 1

*/




struct node
{
   void *data;
   struct node *next;
};

struct LISTCOLLECTION
{
    int count;
    struct node *head;
};

struct primaryIndex
{
	char key[30]; // forms the unique key of your schema
	int offset; //offset of your unique key
	int flag; //set to 1, if deleted
};

struct secondaryIndex
{
	char key[30] ; // or int key;  //depeneds on the type of your secondary index
	int offset;
	int flag;
};



struct colDataStore
{
	int state;				//Stores the state of the datastore (CDS_CLOSED etc.)
	char *database;
	struct bstNode *primaryNdx;		//Stores the bst root node
	struct hashTable *secondaryNdx;		//Stores the hashtable for secondary indeing
	struct stack *freelist;			//Stores the stack for freelist
	int numCols;				//Number of columns in the datastore
	struct{
		FILE *fptr;			//file pointer to the corresponing column dat file
		int type;                       //Type of the field TYPE_INT or TYPE_STRING
		int length;                     //Length of the field. 4 in case of int or n depends on the record definition
		char colname[MAX_COL_NAME]; 	//Name of the column
	} fileregister[MAX_COL];		//Array of the column structure storing the name and file pointer
};

/* Added by RC */

//extern struct colDataStore cdsInfo;

struct dataRecord
{
	int numCols;
	char *values[MAX_COL];
};

/* The implementation for the following function is present in globals.c */


//int printRecord( struct dataRecord* record );
//int printCollection(struct LISTCOLLECTION* recordset );
//int printDatabase();
//int writeString( FILE *fp, int position, char *str, int maxsize );
//char *readString( FILE *fp, int position, int maxsize );


#endif /* CDS_H_ */
