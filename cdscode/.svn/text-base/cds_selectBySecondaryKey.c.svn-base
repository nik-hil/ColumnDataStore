
//This is the global variable defined in globals.c and to be
//used by various files.
#include "common.h"

extern struct colDataStore cdsInfo;

extern struct colDataStore cdsInfo;
//return any error code , 0 on success
//LISTCOLLECTION is a LIST which can can take generic type.
//Implemented LISTCOLLECTION will be added shortly

int selectBySecondaryKey(char *key,struct LISTCOLLECTION *resultset)
{
	int i=0;
	FILE *fp;
	struct llNode *list=NULL;
	list=hashSearchCollection(cdsInfo.secondaryNdx,key);
	if(list==NULL)
		return 1;
	char *bstkey=(char*)malloc(30);
	if(LC_init(resultset)!=SUCCESS)
		return SELECT_SECONDARY_KEY_FAIL;
	while(list!=NULL)
	{
		int offset=list->data->offset;
		fp=cdsInfo.fileregister[0].fptr;
		fseek(fp ,cdsInfo.fileregister[0].length*offset,SEEK_SET );
		fread( bstkey ,cdsInfo.fileregister[0].length,1, fp);

		struct dataRecord *record=(struct dataRecord *)malloc(sizeof(struct dataRecord));

		record->numCols=cdsInfo.numCols;

		for(i=0;i<record->numCols;i++)
			record->values[i]=(char*)malloc(30);
		printf("\nbst key is %s",bstkey);

		if(selectByKey(bstkey,record)==0)
 			LC_insertHead(resultset,record);

		list=list->next;
	}
	return SELECT_SECONDARY_KEY_SUCCESS;
}
	

