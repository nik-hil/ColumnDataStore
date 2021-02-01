#include "stdio.h"
#include "hashTable.c"
#include "string.h"
#include "malloc.h"

void main()
{
	struct hashTable hash;

	hashInit(&hash,100);

	struct secondaryIndex data1,data2,data3,data4;
 
	FILE *fp;
 
	strcpy(data1.key,"ravi");
	data1.offset=1;
        data1.flag=0;
 
	strcpy(data2.key,"ravi");
        data2.offset=2;
        data2.flag=0;
     
 	strcpy(data3.key,"ravi");
        data3.offset=3;
        data3.flag=0;

	strcpy(data4.key,"ravi");
        data4.offset=4;
        data4.flag=0;

	printf("\n\n");

	fp=fopen("xyz","w");
	fwrite(&data1,sizeof(struct secondaryIndex),1,fp);
	fwrite(&data2,sizeof(struct secondaryIndex),1,fp);
	fwrite(&data3,sizeof(struct secondaryIndex),1,fp);
	fwrite(&data4,sizeof(struct secondaryIndex),1,fp);	
	fclose(fp);

	fp=fopen("xyz","rb");
	int ret=hashLoadFromFile(fp,&hash );
	printf("\n%d File Loaded",ret);
	fclose(fp);
	

	
	hashMarkDeleted(&hash,&data3);
	printf("\n");
 
	
        printf("\nprinting the data in hash\n");
	hashprint(&hash);
	printf("\n\n");

 	

	struct llNode *data;
	data=hashSearchCollection(&hash,"ravi");
	struct llNode *temp;
	temp=data;
	printf("\nprinting the search collection\n");
	while(temp!=NULL)
	{	
		
		printf("\n%s%d%d\n",temp->data->key,temp->data->offset,temp->data->flag);
		temp=temp->next;
	}



	
	ret=hashDeleteNode(&hash,&data3);
	printf("\n%d\n",ret);

	

	printf("\nprinting the data in hash\n");
	hashprint(&hash);
	printf("\n\n");



	struct secondaryIndex *dat;
	char *key="ravi";
	dat=hashSearchUnique(&hash,key,2);
	if(dat==NULL)
		printf("data not found");
	else
	printf("\n%s%d%d Search Unique\n ",dat->key,dat->offset,dat->flag);	


	fp=fopen("xyz1","wb");
	ret=hashPersist(fp,&hash );
	printf("\n%d Persisted",ret);
	fclose(fp);
	
	

	struct secondaryIndex detail;
	fp=fopen("xyz1","rb");
	while(fread(&detail,sizeof(struct secondaryIndex),1,fp))
	
	{
		printf("\n\n%s %d %d",detail.key,detail.offset,detail.flag);
	}
		
	fclose(fp);
	
}

