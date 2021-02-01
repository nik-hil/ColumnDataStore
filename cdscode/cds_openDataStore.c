/*
 * cds_openDataStore.c
 *
 *  Created on: 11-Oct-2010
 *      Author: nikhilesh
 */
#include "common.h"

extern struct colDataStore cdsInfo;

int cds_Init(FILE *fp, int flCount) {

	if (flCount == 0) {

		cdsInfo.freelist = (struct stack*)malloc(sizeof(struct stack));
		if (stackLoadFromFile(fp, cdsInfo.freelist) == 0);
		 else{
			free(cdsInfo.freelist);
			return 1;
		}

//		rewind (fp);
		cdsInfo.primaryNdx = bstLoadFromFile(fp);
		return 0;
//		if (cdsInfo.primaryNdx == NULL)
//			return 1;
	//	else

	} else if (flCount == 1) {
		cdsInfo.secondaryNdx=(struct hashTable*)malloc(sizeof(struct hashTable));
		hashInit(cdsInfo.secondaryNdx,MAXBUCKETS);
		if(hashLoadFromFile(fp, cdsInfo.secondaryNdx)==0) return 0;
		else {
			free(cdsInfo.secondaryNdx);
			return 1;
		}

	} else if (flCount > 2)
		return 1;
	return 0;
}

int cds_openDataStore(char *database)
{
	// Check if database is already opened, if yes return 1

	char *data=(char *)malloc(sizeof(char)*30);
	strcpy(data, database);
	strcat(data, ".sch");


	cdsInfo.database=data;


	if (cdsInfo.state == CDS_OPEN_RW) {
		return CDS_OPEN_RW;
	}


	FILE *fpSchema = fopen(data, "rb");

	if (fpSchema == NULL) {
		return 1;
	}
	char fileName[100];

	char *pch=(char*)malloc(30);

	char *field1=(char*)malloc(30);

	char *field2=(char*)malloc(30);;

	FILE *fp[2 + MAX_COL];

	int flCount = 0;

	/*write a function to check if all the file in dataschema are correct or not*/
	while (fgets(fileName, 100, fpSchema) != NULL) {
		pch = strTok(fileName, ":");


		if (flCount < 2)
		{
			sprintf(fileName, "data_%s.ndx", pch);
			fp[flCount + MAX_COL] = fopen(fileName, "rb");

			if (fp[flCount + MAX_COL] == NULL) {
				return 1;
			}
			cds_Init(fp[flCount + MAX_COL], flCount);
			fclose(fp[flCount + MAX_COL]);

		}

		char tempfilename[30];
		sprintf(tempfilename, "%s.dat", pch);
		fp[flCount] = fopen(tempfilename, "rb+");

		if (fp[flCount] == NULL) {
					return 1;
			}

			cdsInfo.fileregister[flCount].fptr = fp[flCount];

			strcpy(cdsInfo.fileregister[flCount].colname,pch);

			printf("\n%d %s",flCount,cdsInfo.fileregister[flCount].colname);

			field1 = strTok(NULL, ":");
			field2 = strTok(NULL, ":");

			if(strcmp(field2,"int\n")==0)
				cdsInfo.fileregister[flCount].type=TYPE_INT;
			else
				cdsInfo.fileregister[flCount].type=TYPE_STRING;


			cdsInfo.fileregister[flCount].length=30;//atoi(field1);

			printf("\n%d %d",cdsInfo.fileregister[flCount].type,cdsInfo.fileregister[flCount].length);

			flCount++;
		}
		cdsInfo.numCols=flCount;
		cdsInfo.state = CDS_OPEN_RW; // to denote it has been open first time
		return 0;
	}

