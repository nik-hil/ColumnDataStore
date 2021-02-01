/*
 * cds_selectByKey.c
 *
 *  Created on: 19-Oct-2010
 *      Author: nikhil
 */

#include "common.h"
#include <stdio.h>

extern struct colDataStore cdsInfo;
/*
int selectByKey(char* key,struct dataRecord *record){
	if(cdsInfo.state == CDS_CLOSED)
	{
		return 1;
	}

	//return null if key <0
	if(key < 0){
		return 1;
	}

	struct primaryIndex *bstTemp=(struct primaryIndex *)malloc(sizeof(struct primaryIndex));
	int offSet;

	//return if key not present
	bstTemp= bstSearchNode(cdsInfo.primaryNdx,key);
	if(bstTemp == NULL){
		return 1;
	}else{

		//loop is here to point the file pointer at appropriate location in .dat files.
		//then read through fread and put it in debit_card
		strcpy(record->values[0],bstTemp->key);
		char s[30];
		offSet = bstTemp->offset;

		printf("\n\nObtained offset after bstSearchNode is %d\n",offSet);

		FILE *fp=cdsInfo.fileregister[1].fptr;
		fseek(fp,30*offSet,SEEK_SET);
		fread(&record->values[1],30,1,fp);


		fp=cdsInfo.fileregister[2].fptr;
		fseek(fp,30*offSet,SEEK_SET);
		fread(&record->holder_name,30,1,fp);

	}
	return 0;
}
*/

/*
 * cds_selectByKey.c
 *
 *  Created on: 19-Oct-2010
 *      Author: nikhil
 */



int selectByKey(char* key,struct dataRecord *record)
{
	FILE *fp;
	if(cdsInfo.state == CDS_CLOSED)
	{
		return 1;
	}

	//return null if key =0
	if(strlen(key) == 0){
		return 1;
	}

	struct primaryIndex *bstTemp=(struct primaryIndex *)malloc(sizeof(struct primaryIndex));
	int offSet;

	//return if key not present
	bstTemp= bstSearchNode(cdsInfo.primaryNdx,key);
	if(bstTemp == NULL){
		return 1;
	}else{

		//loop is here to point the file pointer at appropriate location in .dat files.
		//then read through fread and put it in debit_card
		strcpy(record->values[0],bstTemp->key);
		char s[30];
		offSet = bstTemp->offset;

		printf("\n\nObtained offset after bstSearchNode is %d\n",offSet);

		int i;
		for (i=1; i < record->numCols ;i++)
		{
			int size=30;
			//int size= cdsInfo.fileregister[i].length;
			fp=cdsInfo.fileregister[i].fptr;
			rewind(fp);


			fseek(fp,size*offSet,SEEK_SET);
			fread(record->values[i],size,1,fp);
		}
/*
		fp=cdsInfo.fileregister[2].fptr;
		fseek(fp,30*offSet,SEEK_SET);
		fread(&record->holder_name,30,1,fp);
*/
	}
	return 0;
}
