#include "common.h"

extern struct colDataStore cdsInfo;

void unloadcdsInfo()
{
	int i=0;
	cdsInfo.state=CDS_CLOSED;
	cdsInfo.database=NULL;
	cdsInfo.freelist=NULL;
	cdsInfo.primaryNdx=NULL;
	cdsInfo.secondaryNdx=NULL;
	for(i=0;i<cdsInfo.numCols;i++)
	{
		fclose(cdsInfo.fileregister[i].fptr);
		cdsInfo.fileregister[i].fptr=NULL;
	}

	return;
}

int cds_unloadDataStore()
{
	int i=0;
	if(cdsInfo.state==CDS_CLOSED)
		return 2;
	else
	{
		char colname[30];
		sprintf(colname,"data_%s.ndx",cdsInfo.fileregister[0].colname);
		FILE *fp=fopen(colname,"wb");


		if((stackPersist(fp,cdsInfo.freelist)==0) && (bstPersistNodes(cdsInfo.primaryNdx,fp)==0))
		{

			fclose(fp);
		}

		else
		{
			fclose(fp);
			unloadcdsInfo(fp);
			return 1;
		}

		sprintf(colname,"data_%s.ndx",cdsInfo.fileregister[1].colname);
		fp=fopen(colname,"wb");


		if(hashPersist(fp,cdsInfo.secondaryNdx )==0)
		{
			fclose(fp);
			unloadcdsInfo();
			return 0;
		}

		else
		{
			fclose(fp);
			unloadcdsInfo();
			return 1;
		}


	}
	
}

