
#include "common.h"



/* Internal function */


int cds_printRecord( struct dataRecord* record )
{
	int count;

	if( record == NULL ){
		fprintf(stderr, "ERROR: NULL record given for print\n");
		return PRINT_ERROR;
	}

	for ( count=0; count < cdsInfo.numCols; count++ ){
		printf("\n%s: ", cdsInfo.fileregister[count].colname);
		printf("%s\n", record->values[ count ]);
	}
	return 0;
}

int cds_printCollection(struct LISTCOLLECTION *recordset )
{
	struct node *curr;
	struct dataRecord* record;

	if( recordset == NULL ){
		fprintf(stderr, "ERROR: NULL recordset given for print\n");
		return PRINT_ERROR;
	}

	printf("Recordset contains %d records\n", recordset->count);
	curr = recordset->head;
	while( curr != NULL ){
		record = (struct dataRecord*) curr->data;
		cds_printRecord(record);
		curr = curr->next;
	}	
	return 0;
}

int cds_printDatabase()
{
	struct bstNode *root = cdsInfo.primaryNdx;

	if( cdsInfo.state == CDS_CLOSED ){
		fprintf(stderr, "ERROR: Closed database given for print\n");
		return PRINT_ERROR;
	}
	else if( root == NULL ){
		fprintf(stderr, "ERROR: NULL BST root given for print\n");
		return PRINT_ERROR;
	}

	printf("----------------BEGIN PRINTING %s-------------------------\n", cdsInfo.database);
	printAllRecords( root ); 
	printf("----------------END PRINTING %s-------------------------\n", cdsInfo.database);
	return 0;
}

/* Internal function */
void printAllRecords( struct bstNode *node )
{
	int status,i=0;
	struct dataRecord *record;

	if ( node == NULL )
		return;

	record = (struct dataRecord *) malloc( sizeof(struct dataRecord) );
	record->numCols=cdsInfo.numCols;

	for(i=0;i<record->numCols;i++)
		record->values[i]=(char*)malloc(30);

	status = selectByKey( node->data->key, record );

	if( status != 0 )
	{
		fprintf(stderr, "ERROR: Unable to get record for key = %s\n", node->data->key);
	}
	else
	{
		cds_printRecord( record );
		free( record );
	}

	printAllRecords( node->leftChild );
	printAllRecords( node->rightChild );
}

int writeString( FILE *fp, int position, char *str, int maxsize )
{
	char *wstr;

	wstr = (char *) malloc(sizeof(char)*maxsize + 1);
	memset(wstr, '\0', maxsize+1);

	if( fp == NULL || position < 0 || str == NULL || maxsize < 0 ){
		fprintf(stderr, "ERROR: Invalid arguments given for writeString\n");
		return STRING_WRITE_ERROR;
	}

	if( strlen(str) > maxsize ){
		/* Truncate string */
		fprintf(stderr, "Warning: Input string is going to be truncated\n");
	}

	strncpy(wstr, str, maxsize);

	fseek(fp, position, SEEK_SET);

	/* Do not forget to write the string with '\0'. */
	fwrite(wstr, sizeof(char), maxsize+1, fp);
	return SUCCESS;
}

/*
When reading, read the actual string length first and then read only that many bytes. 
Do not forget to read the string with '\0'.
*/

char *readString( FILE *fp, int position, int maxsize )
{
	char *str;

	if( fp == NULL || position < 0  || maxsize < 0 ){
		fprintf(stderr, "ERROR: Invalid arguments given for readString\n");
		return NULL;
	}
	fseek(fp, position, SEEK_SET);
	str = (char *) malloc(sizeof(char)*maxsize + 1);

	/* Do not forget to read the string with '\0'. */
	fread( str, sizeof(char), maxsize+1, fp );
	return str;
}
