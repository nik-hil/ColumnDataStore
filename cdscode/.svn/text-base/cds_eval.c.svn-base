
#include "common.h"
#include <time.h>
FILE *logfile;

#define logarg(msg, arg) fprintf(logfile, "%s: %s %s\n", __FILE__, msg, arg); \
	fprintf(stdout, "%s: %s %s\n", __FILE__, msg, arg);

extern struct colDataStore cdsInfo;

/* Local functions */
int showmenu();
struct dataRecord* makeRecord();

int main()
{
	int choice, status,z=0;
	char dbname[30], col[30], value[30];
	struct dataRecord *record, *selrecord;
	struct LISTCOLLECTION *recordset;
	char key[30], secondarykey[30];
	int currtime = time( NULL );

	srand ( time(NULL) );

	logfile = (FILE*) fopen("cdseval.log", "a");
	if( logfile == NULL ){
		fprintf(stderr, "Unable to open cdseval.log in write mode");
		exit(1);
	}

	logarg("LOG STARTED AT ", ctime(&currtime));
	strcpy(dbname, "");
	while( 1 ){
		choice = showmenu();

		switch(choice){
			case 0: /* Close Database and exit */
				if( cdsInfo.state == CDS_CLOSED ){
					fprintf(stderr, "ERROR: Database %s is not open to Unload\n\tProgram is exiting",dbname);
					exit(1);
				}
				status = cds_unloadDataStore();
				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to unload database - ", dbname);
					exit(1);
				}
				else{
					logarg("++++++++++ SUCCESS: Database unloaded - ", dbname);
					exit(0);
				}
			break;
			case 1: /* Create Database */
				if( cdsInfo.state == CDS_OPEN_RW ){
					fprintf(stderr, "ERROR: Database %s is already open.\nBefore creating new Database unload it. \n",dbname);
					break;
				}
				printf("Enter database name: ");
				scanf("%s", dbname);
				status = cds_createDataStore( dbname );
				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to create database - ", dbname);
				}
				else{
					logarg("++++++++++ SUCCESS: Database created - ", dbname);
				}
			break;
			case 2: /* Open Database */
				printf("Enter database name: ");
				scanf("%s", dbname);
				status = cds_openDataStore( dbname );
				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to open database - ", dbname);
				}
				else{
					logarg("++++++++++ SUCCESS: Database open - ", dbname);
				}
			break;
			case 3: /* Print database */
				if( cdsInfo.state == CDS_CLOSED ){
					fprintf(stderr, "ERROR: No Database is open\n");
					break;
				}

				hashprint(cdsInfo.secondaryNdx);
///*
				status = cds_printDatabase();
				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to print database - ", dbname);
				}
				else{
					logarg("++++++++++ SUCCESS: Database printed - ", dbname);
				}
//*/
			break;
			case 4: /* Add record */
				if( cdsInfo.state == CDS_CLOSED ){
					fprintf(stderr, "ERROR: No Database is open\n");
					break;
				}
				record=makeRecord();

				strcpy(key,"inserted");
				status = cds_addUniqueRecord( record );

				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to add record with key - ", key);
				}
				else{
					logarg("++++++++++ SUCCESS: Added record with key - ", key);
				}
//				free(record);
			break;
			case 5: /* Modify record */
				if( cdsInfo.state == CDS_CLOSED ){
					fprintf(stderr, "ERROR: No Database is open\n");
					break;
				}
				printf("\nEnter the primary key to modify");
				scanf("%s",key);

				struct dataRecord *record1=(struct dataRecord*)malloc(sizeof(struct dataRecord));
				record1->numCols=cdsInfo.numCols;

				for(z=0;z<cdsInfo.numCols;z++)
				{
					record1->values[z] = (char *)malloc(sizeof(char)*30);
					printf("\nEnter %s\t",cdsInfo.fileregister[z].colname);
					scanf("%s",record1->values[z]);
				}
				//record = makeRecord();
				status = updateRecord( key, record1);
				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to modify record with key - ", key);
				}
				else{
					logarg("++++++++++ SUCCESS: Modified record with key - ", key);
				}
//				free(record1);
			break;
			case 6: /* Delete by key */
				if( cdsInfo.state == CDS_CLOSED ){
					fprintf(stderr, "ERROR: No Database is open\n");
					break;
				}
				printf("Enter key of record to be deleted: ");
				scanf("%s", key);
				status = cds_deleteByKey( key );
				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to delete record with key - ", key);
				}
				else{
					logarg("++++++++++ SUCCESS: Deleted record with key - ", key);
				}
			break;
			case 7: /* Select by key */
				if( cdsInfo.state == CDS_CLOSED ){
					fprintf(stderr, "ERROR: No Database is open\n");
					break;
				}
				printf("Enter key of record to be selected: ");
				scanf("%s", key);

				selrecord = (struct dataRecord *) malloc( sizeof(struct dataRecord) );
				selrecord->numCols=cdsInfo.numCols;

				for(z=0;z<cdsInfo.numCols;z++)
					selrecord->values[z]=(char*)malloc(30);

				status = selectByKey( key, selrecord );

				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to select record with key - ", key);
				}
				else{
					status = cds_printRecord(selrecord);
					if( status != SUCCESS ){
						logarg("---------- FAILURE: Unable to print record with key - ", key);
					}
					else{
						logarg("++++++++++ SUCCESS: Selected and printed record with key - ", key);
					}
				}
				free(selrecord);
			break;
			case 8:
				if( cdsInfo.state == CDS_CLOSED ){
					fprintf(stderr, "ERROR: No Database is open\n");
					break;
				}
				printf("Enter secondary key of records to be selected: ");
				scanf("%s", key);

				recordset = (struct LISTCOLLECTION *) malloc( sizeof(struct LISTCOLLECTION) );

				recordset->head=(struct node*)malloc(sizeof(struct node));

				status = selectBySecondaryKey( key, recordset );

				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to select record with key - ", key);
				}
				else{
					status = cds_printCollection(recordset);
					if( status != SUCCESS ){
						logarg("---------- FAILURE: Unable to print records with secondary key - ", key);
					}
					else{
						logarg("++++++++++ SUCCESS: Selected and printed records with secondary key - ", key);
					}
				}
				free(recordset);
			break;
			case 9:
				if( cdsInfo.state == CDS_CLOSED ){
					fprintf(stderr, "ERROR: No Database is open\n");
					break;
				}
				printf("Enter filter column name: ");
				scanf("%s", col);
				
				printf("Enter filter column value: ");
				scanf("%s", value);
				
				recordset = (struct LISTCOLLECTION *) malloc( sizeof(struct LISTCOLLECTION) );

				recordset->head=(struct node*)malloc(sizeof(struct node));

				status = selectByColumnName( col, value, recordset );

				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to select by column name - ", col);
				}
				else{
					status = cds_printCollection(recordset);
					if( status != SUCCESS ){
						logarg("---------- FAILURE: Unable to print records with column filter on  - ", col);
					}
					else{
						logarg("++++++++++ SUCCESS: Selected and printed records with column filter on - ", col);
					}
				}
			break;
			case 10:
				if( cdsInfo.state == CDS_CLOSED ){
					fprintf(stderr, "ERROR: No Database is open\n");
					break;
				}
				printcolnames();
			break;
			default:
				printf("Invalid input... enter value between 0-9\n"); 
			break;
		}
	}
}

struct dataRecord* makeRecord()
{
	int count;
	struct dataRecord *record1 = (struct dataRecord *) malloc( sizeof(struct dataRecord) );
	record1->numCols = cdsInfo.numCols;

	for( count = 0; count < record1->numCols; count++ )
	{
		record1->values[count] = (char *)malloc(sizeof(char)*30);
		printf("\nEnter %s",cdsInfo.fileregister[count].colname);
		scanf("%s",record1->values[count]);
	}
	return record1;
}

int showmenu()
{
	int choice = 0;

	printf("\nCDS Evaluation Program\n");
	printf("======================\n");
	
	printf("\t0) Exit\n\n");
	printf("\t1) Create Database\n\n");
	printf("\t2) Open Database\n\n");
	printf("\t3) Print Database\n\n");
	printf("\t4) Add Unique Record\n\n");
	printf("\t5) Modify Record\n\n");
	printf("\t6) Delete By Key\n\n");
	printf("\t7) Select By Key\n\n");
	printf("\t8) Select By Secondary Key\n\n");
	printf("\t9) Select By Column Name\n\n");
	printf("\t10) Print the colnames\n\n");

	printf("ENTER YOUR CHOICE (0-10): ");
	fflush(stdin);
	scanf("%d", &choice);

	return choice;
}

