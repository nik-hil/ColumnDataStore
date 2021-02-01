#include "stdio.h"

#include "malloc.h"

#include "stdlib.h"

#define MAXBUCKETS 100


#include "cds.h"


#include "llist.c"

#include "string.h"

struct hashTable
{
int numBuckets;
struct llNode *buckets[MAXBUCKETS] ;
};


void hashInit(struct hashTable *hash,int numBuckets)
{
	hash->numBuckets=numBuckets;
	int i=0;
	for(i=0;i<MAXBUCKETS;i++)
		hash->buckets[i]=NULL;	
}

int calcHash( char *key)
{
	int hx,i,index,size;
	size=strlen(key);
	for (hx =i = 0; i < size; ++i) 
	  hx = ((hx<<1) + key[i]);
        index=hx%100;
	return index;
}

int hashInsert(struct hashTable *hash, struct secondaryIndex*  data)
{
	int index;
	index=calcHash(data->key);
	int ret=llInsertSortedOrder(&hash->buckets[index],data);
	if(ret==0)
		return 0;
	else 
		return 1;

}

int hashMarkDeleted(struct hashTable *hash, struct secondaryIndex*  detail)
{
	int index=calcHash(detail->key);
	int ret=llMarkDeleted(hash->buckets[index],detail);
	if(ret==0)
		return 0;
	else
		return 1;
}

int hashDeleteNode(struct hashTable *hash, struct secondaryIndex *detail)
{
	int index=calcHash(detail->key);
	
	int ret=llDeleteNode(&hash->buckets[index],detail);
	if(ret==0)
		return 0;
	else
		return 1;

}

struct llNode*  hashSearchCollection(struct hashTable *hash,char *key)
{
	int index=calcHash(key);
	struct llNode *original=NULL;
	struct llNode *temp=hash->buckets[index];
	while(temp!=NULL)
	{
		if((strcmp(temp->data->key,key)==0) && temp->data->flag!=1)
		{
			struct llNode *l=(struct llNode*)malloc(sizeof(struct llNode));
			l->data=temp->data;
			l->next=NULL;
			if(original==NULL)
				original=l;
						
			else
			{
				struct llNode *tempo=original;
				while(tempo->next!=NULL)
					tempo=tempo->next;
				tempo->next=l;
			}
		}
		temp=temp->next;
	}
	return original;
	
}

struct secondaryIndex* hashSearchUnique(struct hashTable *hash,char *key,int offset)
{
	int index=calcHash(key);
	struct llNode *temp=hash->buckets[index];
	while(temp!=NULL)
	{
		if(strcmp(temp->data->key,key)==0)
		{
			if(temp->data->offset==offset)
				return temp->data;
		}
		temp=temp->next;
	}
	return NULL;
}

int hashLoadFromFile(FILE *fp, struct hashTable *hash )
{
	if(fp==NULL)
		return 1;
	else
	{	
		struct secondaryIndex *data=(struct secondaryIndex*)malloc(sizeof(struct secondaryIndex));
		while(fread(data,sizeof(struct secondaryIndex),1,fp))
		{	
			//printf("%p",data);
			int index=calcHash(data->key);
			llInsertSortedOrder(&hash->buckets[index],data);
			//struct secondaryIndex *data=(struct secondaryIndex*)malloc(sizeof(struct secondaryIndex));	
		}
		return 0;
	}
}

int hashPersist(FILE *fp,struct hashTable *hash )
{
	int j=0;	
	for(j=0;j<100;j++)
		llPersist(hash->buckets[j],fp);	
	
	return 0;
}

void hashprint(struct hashTable *h)
{
	int i;
	for(i=0;i<100;i++)
		print(h->buckets[i]);
}






