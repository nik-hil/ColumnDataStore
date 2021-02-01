/*
 * cds_createdatastore.c
 *
 *  Created on: 10-Oct-2010
 *      Author: nikhil
 */

#include "common.h"


extern struct colDataStore cdsInfo;
/*
 * return 1, if string is of length 0,
 * return 2, if schema file doesn't exist
 * return 0, on success
 * */

int checkSchemaFile(FILE *fpTemp){
	char nFileName[100], *pch;
	int iCount =0;
		while(fgets(nFileName,100,fpTemp)!= NULL){
		pch = strTok(nFileName,":");
		while(pch != NULL){
			iCount++;
			pch = strTok(NULL,":");
		}
	if(iCount%3 != 0) {
			printf("\nAn error occured in Schema File");
			return 1;
		}
	}
	rewind(fpTemp);
	return 0;
}


int cds_createDataStore(char *database)
{
	char data[30], delFileName[2 + MAX_COL][100];
	int iCount = 0;
	if(strlen(database)==0)
		return 1;
	strcpy(data,database);

	strcat(data,".sch");


	FILE *fpSchema = fopen (data,"r");
	if(fpSchema==NULL)
		return 1;


	if(checkSchemaFile(fpSchema) == 1)
	{
		fclose(fpSchema);
		free(cdsInfo.freelist);
		return 1;
		return 1;
	}


	FILE *fp;
	char *pch, fileName[100],nfileName[100];
	int fCount =0;

	while(fgets(fileName,100,fpSchema ) != NULL )
	{
		pch = strTok(fileName,":");
		if(fCount < 2)
		{
			sprintf(nfileName,"data_%s.ndx",pch);
			strcpy(delFileName[iCount++], nfileName);

			//check if we are reopening the datastore
			fp = fopen(nfileName,"rb");
			if(fp != NULL)
			{
				printf("\nAn error occurred. Database is already opened");
				fclose(fp);
				return 1;
			}

			fp = fopen(nfileName,"wb");
			if(fp == NULL)
			{
				printf("\nError in creation of data store.\n Deleting files...");

				while(iCount != -1)
				{
					if(remove(delFileName[--iCount]) == -1)
						printf("\nError in deleting the file %s", delFileName[iCount]);
				}
				return 1;
			}

			if(fCount == 0)
			{
				struct stack s;
				if(1==stackInit(&s))	return 1;
				else if (stackPersist(fp, &s) == 1)
					return 1;
			}

			fclose(fp);
		}

		sprintf(nfileName,"%s.dat",pch);
		//check if we are reopening the datastore
		fp = fopen(nfileName,"rb");
		if(fp != NULL)
		{
			printf("\nAn error occurred. Database is already opened");
			fclose(fp);
			return 1;
		}

		fp = fopen(nfileName,"wb");
		if(fp == NULL)
		{
			printf("\nError in creation of data store.\n Deleting files...");

			while(iCount != -1)
			{
				if(remove(delFileName[--iCount]) == -1)
					printf("\nError in deleting the file %s", delFileName[iCount]);
			}
			return 1;
		}

		fclose(fp);
		fCount++;

	}
	cdsInfo.numCols=fCount;
	if(iCount == 0)	return 1;
	return 0;
}

 
