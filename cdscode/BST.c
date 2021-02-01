/*
 * BST.c
 *
 *  Created on: 20-Sep-2010
 *      Author: nikhil
 */
#include "cds.h"
#include  <stdio.h>
#include <stdlib.h>

struct bstNode
{
struct primaryIndex *data; //This would hold the "unique" key to be indexed
struct bstNode *rightChild;
struct bstNode *leftChild;
};


int bstInsertNode(struct bstNode **rootNode, struct primaryIndex *data){

	if(data->key < 0) {
		printf("Key value is -ve\n");
		return 1;
	}
	if (*rootNode == NULL){
		struct bstNode *temp = (struct bstNode *)malloc (sizeof(struct bstNode));
		temp->data=data;
		temp->leftChild=NULL;
		temp->rightChild=NULL;

		(*rootNode) = temp;
		return 0;
	}
	else if(data->key < (*rootNode)->data->key){
		return bstInsertNode(&((*rootNode)->leftChild) , data) ;
	}
	else if(data->key > (*rootNode)->data->key){
		return bstInsertNode(&((*rootNode)->rightChild) , data) ;
	}
	else if(data->key == (*rootNode)->data->key){
		printf("Duplicate key found\n");
			return 0;
	}
	return 0;
}

struct bstNode *bstLoadFromFile(FILE *fp){

	/*FILE *fp = fopen(fileName,"rb");
	*/
	 if(fp==NULL) {
		printf("Error in opening the file\n");
		return NULL;
	}

	fseek(fp,400,SEEK_SET);

	struct bstNode *rootNode = NULL;
	int iCount ;


	while (!feof(fp)){
		struct primaryIndex *tempData = (struct primaryIndex *)malloc (sizeof(struct primaryIndex));
		iCount=fread (tempData,sizeof(struct primaryIndex),1,fp);

		if(iCount==0) {
		//	fclose(fp);
			return rootNode;
		}else{

			bstInsertNode(&rootNode, tempData);

		}
	}

	return rootNode;

}




int bstMarkDeleted(struct bstNode *rootNode,int key){
	if ((rootNode) == NULL)	{
		printf("Root Node is NULL \n");
		return 1;
	}
	else if(key == rootNode->data->key){
		rootNode->data->flag = 1;
		return 0;
	}
	else if(key < rootNode->data->key){
		if(rootNode->leftChild == NULL)		printf("Key Not Found\n");
		return bstMarkDeleted(rootNode->leftChild , key) ;
	}
	else if (key > rootNode->data->key){
		if(rootNode->rightChild == NULL)		printf("Key Not Found\n");
		return bstMarkDeleted(rootNode->rightChild , key) ;
	}

	return 1;
}

struct primaryIndex *bstSearchNode(struct bstNode *rootNode,int key){
	if (rootNode == NULL)	{
		printf("Root Node is NULL\n");
		return NULL;
	}
	else if(key == rootNode->data->key){
		if(rootNode->data->flag != 1)
			return (rootNode->data);
		else{
			return NULL;
		}
	}
	else if(key < rootNode->data->key){
		if((rootNode)->leftChild == NULL)		printf("Key Not Found\n");
		return bstSearchNode(rootNode->leftChild , key) ;
	}
	else if (key > rootNode->data->key){
		if((rootNode)->rightChild == NULL)		printf("Key Not Found\n");
		return bstSearchNode(rootNode->rightChild , key) ;
	}

	return NULL;
}

struct bstNode *findMin(struct bstNode *rootNode){
	if(rootNode == NULL) return NULL;
	if(rootNode ->leftChild == NULL) return rootNode;
	return findMin (rootNode ->leftChild);
}

struct bstNode *bstDeleteAndAdjustNode(struct bstNode **rootNode,int key)
{
	struct bstNode *tmp,*child;
	if (*rootNode == NULL) return NULL;
	if(key > (*rootNode)->data->key)
	(*rootNode)->rightChild = bstDeleteAndAdjustNode(&((*rootNode)->rightChild),key);
	else if(key < (*rootNode)->data->key)
	(*rootNode)->leftChild = bstDeleteAndAdjustNode(&((*rootNode)->leftChild),key);
	else
	{
		if(((*rootNode)->leftChild) && ((*rootNode)->rightChild))
		{
			tmp = findMin(((*rootNode)->rightChild));
			(*rootNode)->data = tmp->data;
			(*rootNode)->rightChild = bstDeleteAndAdjustNode(&((*rootNode)->rightChild),tmp->data->key);
		}
		else
		{
			tmp = (*rootNode);
			if(((*rootNode)->leftChild)==NULL)
				child = ((*rootNode)->rightChild);
			if(((*rootNode)->rightChild)==NULL)
				child = ((*rootNode)->leftChild);

			free(tmp);
			return child;
		}
	}
	return *rootNode;

}

int bstDeleteNode(struct bstNode **rootNode,int key)
{
		if(bstDeleteAndAdjustNode(rootNode,key)==NULL)
			return 1;
		else
			return 0;
}

void postOrderWrite(struct bstNode *root, FILE *fp){
	if(root == NULL) return;

	if(root->leftChild != NULL) postOrderWrite(root->leftChild,fp);
	if(root->rightChild != NULL) postOrderWrite(root->rightChild,fp);
	fwrite(root->data,sizeof(struct primaryIndex),1,fp);
	return;
}

/*we are writing data in post order through a fun postOrderWrite
 * */
//int bstPersistNodes(struct bstNode *root,FILE *fp){
int bstPersistNodes(struct bstNode *rootNode,FILE *fp)
{
	/*FILE *fp = fopen (fileName,"wb");
	*/
	if (fp==NULL) {
		printf("Error in File opening\n");
		return 1;
	}
	fseek(fp,400,SEEK_SET);

	postOrderWrite(rootNode,fp);
	//fclose(fp);
	return 0;
}

