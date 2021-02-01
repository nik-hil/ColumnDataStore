/*
 * cds_addUniqueRecord.c
 *
 *  Created on: 20-Oct-2010
 *      Author: nikhil
 */

#include "common.h"

extern struct colDataStore cdsInfo;

int cds_addUniqueRecord(struct dataRecord* record)
{
      FILE *fp;
      int i;
      if(cdsInfo.state == CDS_CLOSED || cdsInfo.state==CDS_OPEN_READONLY)
	      return 1;

	/* validation of the record */
      else
      {
    	  for(i=0;i<record->numCols;i++)
    	  {
    		  if(strcmp(record->values[i],"")==0)
    		  {
    			  printf("\nNull Record Found");
    			  return 1;
    		  }
    	  }

      }

 		int offset=0,final_offset=0,fromstack=0;
		if( stackPop(cdsInfo.freelist,&offset) == 1 )
		{
		  // when the freelist is empty
		  printf("\nwhen the freelist is empty:\n");
		  fp=cdsInfo.fileregister[0].fptr;
//		  rewind(fp);

		  fseek(fp,0,SEEK_END);
		  offset = (ftell(fp))/(sizeof(char)*30);
		  final_offset=offset;
		}
		else
		{
			fromstack=1;
			final_offset=offset;
			fp=cdsInfo.fileregister[0].fptr;
		}

		printf("adduniquerecord:final_offset= %d",final_offset);
		struct primaryIndex data;
		strcpy(data.key,record->values[0]);
		data.offset=final_offset;
		data.flag=0;

		if(bstInsertNode(&cdsInfo.primaryNdx,&data) == 0 )
		{
		      struct secondaryIndex detail;
		      strcpy(detail.key,record->values[1]);
		      detail.offset=final_offset;
		      detail.flag=0;
		      if(hashInsert(cdsInfo.secondaryNdx,&detail) == 0)
		      {
			      fseek(fp,sizeof(char)*30*(final_offset),SEEK_SET);
			      fwrite(record->values[0],30,1,fp);


			      for(i=1;i<record->numCols;i++)
			      {
			    	  fp=cdsInfo.fileregister[i].fptr;
			    	  fseek(fp,sizeof(char)*30*(final_offset),SEEK_SET);
			    	  fwrite(record->values[i],sizeof(char)*30,1,fp);
			      }
			      return 0;
		      }
		      else
		      {
			      //reverting the changes if hash insert fails.
			      bstMarkDeleted(&cdsInfo.primaryNdx,data.key);
		          if(fromstack==1)
				  stackPush(cdsInfo.freelist,final_offset);
		      }

		}
		else
		{
		      //reverting the changes if bst insert fails.
		    if(fromstack==1)
			stackPush(cdsInfo.freelist,final_offset);
		}
		return 1;

}

