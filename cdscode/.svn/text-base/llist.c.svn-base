#include "common.h"


int testkey(char *key)
{
	int i;
	int len=strlen(key);
	for(i=0;i<len;i++)
	{
		if((key[i]>='a' && key[i]<='z') || (key[i]>='A' && key[i]<='Z') || (key[i]>='0' && key[i]<='9'));
		else
			return 1;
	}
	return 0;
}
			

int llInsertSortedOrder(struct llNode **head,struct secondaryIndex *data)
{
	char tstring[30];
	struct llNode *temp=*head;
	int ret=testkey(data->key);
	if(data->flag != 1)
	{
	if(ret==0)//return from testkey
	{
	if(temp==NULL)//if head is NULL(i.e.,when there is no list from that bucket
	{
		struct llNode *l=(struct llNode*)malloc(sizeof(struct llNode));
				
		l->data=(struct secondaryIndex *)malloc(sizeof(struct secondaryIndex));
		
		strcpy(l->data->key,data->key);
		printf("\n");
		l->data->offset = data->offset;

		l->data->flag = data->flag;

		l->next=NULL;

		*head=l;

		printf("\nfun=> llinsertSortedOrder=> %s %d %d inserted",data->key,data->offset,data->flag);

		return 0;
	}
	else//when head is not NULL
	{		
		struct llNode *parent;

		while(temp!=NULL && (strcmp(data->key,temp->data->key)>=0) )//checking 1.control went to leaf and 2.whether the string to insert is alphabetically prior to the current one or not
		{
			parent=temp;
			temp=temp->next;
		}

		if((strcmp(parent->data->key,data->key)==0) && (parent->data->offset == data->offset) && (parent->data->flag == 0))
		{
			printf("\nDuplicate entry in hash");
			return 1;
		}
		else if((strcmp(parent->data->key,data->key)==0) && (parent->data->offset == data->offset) && (parent->data->flag == 1))
		{
			parent->data->flag=0;
			return 0;
		}
		else
		{
		struct llNode *l=(struct llNode*)malloc(sizeof(struct llNode));
		
		l->data=(struct secondaryIndex *)malloc(sizeof(struct secondaryIndex));
		
		strcpy(l->data->key,data->key);

		l->data->offset = data->offset;

		l->data->flag = data->flag;

		l->next=NULL;
		
		parent->next=l;
		l->next=temp;
		
		printf("\nfun=> llinsertSortedOrder=> %s %d %d inserted",data->key,data->offset,data->flag);
		return 0;
		}
	}	
	return 1;
	}
	else
	{
		printf("\n Invalid Key");return 1;
	}
	}
}

struct llNode* llGetNode(struct llNode *head, char *key)
{
	struct llNode *temp=head;
	while(temp!=NULL)
	{
		if(strcmp(temp->data->key,key)==0)
		{
			printf("\n%s getting",key);
			return temp;
		}			
		temp=temp->next;
	}
	return NULL;
}

int llMarkDeleted(struct llNode *head,struct secondaryIndex * detail)
{
	struct llNode *temp=head;
	while(temp!=NULL)
	{
		if(strcmp(temp->data->key,detail->key)==0)
		{
			if(temp->data->offset==detail->offset)
				{
					temp->data->flag=1;
					printf("\n%s %d %d MarkDeleted ",detail->key,detail->offset,detail->flag);
					return 0;
				}
		}
		temp=temp->next;
	}
	return 1;
}

int llDeleteNode(struct llNode **head,struct secondaryIndex *detail)
{
	struct llNode *temp=*head;
	if(temp==NULL)
		return 1;
	
	struct llNode *parent=temp;
	while(temp!=NULL)
	{
		
		if((strcmp(temp->data->key,detail->key)==0) && (temp->data->offset==detail->offset) && (temp->data->flag==1))
		{
				if(temp==*head)
				{
					*head=temp->next;
					free(temp);
					return 0;
				}				
				if(parent->next==NULL)
				{
					*head=NULL;
					return 0;
				}
				else
				{	
					parent->next=temp->next;
					free(temp);
					printf("\n%s %d %d Deleted",detail->key,detail->offset,detail->flag);
					return 0;
				}			
				struct secondaryIndex *data;
				struct llNode *next;

		}

		parent=temp;		
		temp=temp->next;
	}
	return 0;
}

int llPersist(struct llNode *head,FILE *fp)
{
	struct llNode *temp=head;
	if(temp!=NULL)
	{
		while(temp!=NULL)
		{
			fwrite(temp->data,sizeof(struct secondaryIndex),1,fp);
			temp=temp->next;
		}
	}
	return 0;
}

void print(struct llNode *head)
{
	struct llNode *temp=head;
	while(temp!=NULL)
	{	
		printf("%s %d %d\n",temp->data->key,temp->data->offset,temp->data->flag);
		temp=temp->next;
	}
}


