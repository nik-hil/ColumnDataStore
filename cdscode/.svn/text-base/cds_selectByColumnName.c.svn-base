
#include "common.h"


extern struct colDataStore cdsInfo;

int selectByColumnName(char *colname,char *value,struct LISTCOLLECTION *resultset)
{
	if(cdsInfo.state==CDS_CLOSED)
		return 1;

	int i=0,z=0;
	int flag=0;
	char key[30];

	//Looping through to find out whether or not such a column is present
	for(i=0;i<cdsInfo.numCols;i++)
	{
//		printf("\n%s %s",cdsInfo.fileregister[i].colname,colname);
		if(strcmp(cdsInfo.fileregister[i].colname,colname)==0)
		{
//			printf("\nInside selectByColoumn\n");
			flag=1;
			break;
		}
	}


	if(flag==0) return 1; //There is no such colname

//	printf("\nInside selectByColoumn\n");

	fseek( cdsInfo.fileregister[i].fptr,0,SEEK_SET );
	
//	int IntValue;
//	if(cdsInfo.fileregister[i].type==TYPE_INT)
//	{
//		IntValue=atoi(value);
//		flag=0;
//	}
//	else flag=1;

	int offset=0;

	if(LC_init(resultset)!=0)
		return 1;

	char *fileValue=(char *)malloc(sizeof(char)*30);
	while(fread( fileValue, sizeof(char)*30,1,cdsInfo.fileregister[i].fptr ))
	{
			if(strcmp(fileValue,value)==0)
			{
				fseek( cdsInfo.fileregister[0].fptr ,cdsInfo.fileregister[0].length*offset , SEEK_SET );
				fread( &key ,cdsInfo.fileregister[0].length,1, cdsInfo.fileregister[0].fptr );

				struct dataRecord *record=(struct dataRecord*)malloc(sizeof(struct dataRecord));
				record->numCols=cdsInfo.numCols;

				for(z=0;z<record->numCols;z++)
					record->values[z]=(char*)malloc(30);

				if(selectByKey(key,record)==0)
 					LC_insertHead(resultset,record);
			}
			offset++;
	}

	return 0;
}
