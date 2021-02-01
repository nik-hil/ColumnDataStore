
#include "common.h"


int cds_deleteByKey(char* key)
{
	int delete_status,i=0;
	struct dataRecord *record;
	record=(struct dataRecord*)malloc(sizeof(struct dataRecord));
	record->numCols=cdsInfo.numCols;
	for(i=0;i<record->numCols;i++)
	{
		record->values[i]=(char*)malloc(30);
	}

	if(selectByKey(key,record)==1)
		return 1;

	else
	{
		struct primaryIndex *pd=(struct primaryIndex *)malloc(sizeof(struct primaryIndex));
		/*bstSearch is called to the offset value to be delete, offset is stored in getoffset
		 * which is pushed on stack
		 * */
		pd = bstSearchNode(cdsInfo.primaryNdx,record->values[0]);

		if(pd==NULL)
		{
			delete_status=DELETEBYKEY_FAILURE;
			return delete_status;
		}

		int getoffset=pd->offset;

		if(bstMarkDeleted(cdsInfo.primaryNdx,record->values[0])==1)
		{
			delete_status = DELETEBYKEY_FAILURE;
		}
		else
		{

/*
			FILE *fp=cdsInfo.fileregister[1].fptr;
			fseek(fp,sizeof(char)*30*getoffset,SEEK_SET);
			fgets(record->card_type,30,fp);

*/
//			printf("\nPrinting in deletebykey %s\n",record->card_type);

			struct secondaryIndex *sd=(struct secondaryIndex*)malloc(sizeof(struct secondaryIndex));

			sd=hashSearchUnique(cdsInfo.secondaryNdx,record->values[1],getoffset);

			if(hashMarkDeleted(cdsInfo.secondaryNdx,sd)==1)
			{
				delete_status = DELETEBYKEY_FAILURE;
			}
			else
			{
				if(stackPush(cdsInfo.freelist,getoffset)==1)
				{
					delete_status = DELETEBYKEY_FAILURE;
				}
				else
					delete_status=DELETEBYKEY_SUCCESS;
			}
		}
	}
	return delete_status;
}
