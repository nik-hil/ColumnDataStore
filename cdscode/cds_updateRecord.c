/*
 * update_record.c
 *
 *  Created on: 22-Oct-2010
 *      Author: ram
 */
#include "common.h"

extern struct colDataStore cdsInfo;

int updateRecord(char *key,struct dataRecord *newrecord)
{
	int i;
	if(strlen(key) == 0)
		return 1;

/*
	struct dataRecord *record=(struct dataRecord*)malloc(sizeof(struct dataRecord));

	record->numCols=newrecord->numCols;

	for(i =0; i< cdsInfo.numCols; i++)
	{
		record->values[i]=(char*)malloc(30);
		strcpy(record->values[i] ,newrecord->values[i]);
	}
*/

	struct dataRecord *dRecord=(struct dataRecord *)malloc(sizeof(struct dataRecord));
	dRecord->numCols=cdsInfo.numCols;
	int x=0;
	for(x=0;x<dRecord->numCols;x++)
	{
		dRecord->values[x]=(char*)malloc(30);
	}

	if(selectByKey(key,dRecord)==1)
		return 1;

	if(cds_deleteByKey(key)==1)
		return 1;

	if(cds_addUniqueRecord(newrecord)==1)
	{
		for(i =0; i< cdsInfo.numCols; i++)
		{
			strcpy(newrecord->values[i],dRecord->values[i]);
		}
		cds_addUniqueRecord(newrecord);
		return 1;
	}

	else
		return 0;

}
