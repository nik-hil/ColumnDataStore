
#include "common.h"

int LC_init(struct LISTCOLLECTION *lc)
{
     if(lc==NULL)
       return NULL_LIST;
     lc->count=0;
     lc->head=NULL;
     return SUCCESS;
}

int LC_insertHead(struct LISTCOLLECTION *lc,void *data)
{
    struct node *newNode;
    if(data==NULL)
       return NULL_DATA;
    if(lc==NULL)
       return NULL_LIST;
    newNode=(struct node*)malloc(sizeof(struct node));
    newNode->data=data;
    newNode->next=lc->head;
    lc->count++;
    lc->head=newNode;
    return SUCCESS;
}


/*delete functionality is not required */
