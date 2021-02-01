/*
 * BSTTest.c
 *
 *  Created on: 21-Sep-2010
 *      Author: nikhil
 */

#include <stdio.h>
#include <malloc.h>
#include "BST.h"

void printbst(struct bstNode *rootNode) {
	struct bstNode *temp = rootNode;
	if (temp == NULL) {
		return;
	}
	if (temp->leftChild == NULL && temp->rightChild == NULL) {
		printf("\nKey : %d\nOffset : %d\nFlag : %c\n",temp->data->key,temp->data->offset,temp->data->flag);
	}
	else {
		printf("\nKey : %d\nOffset : %d\nFlag : %c\n",temp->data->key,temp->data->offset,temp->data->flag);
		printbst(temp->leftChild);
		printbst(temp->rightChild);
	}
	return;
}
#define FAILURE 1

int main(int argc, char **argv) {
	FILE *fp = NULL;
	int arr[10] = { 12,4,16,2,6,14,18 };
	int i = 0;
	printf("Testing BST-001\n");
	struct bstNode **rootNode = (struct bstNode**) malloc(sizeof(struct bstNode*));
	while(i<7) {
		struct primaryIndex *pi = (struct primaryIndex*) malloc(sizeof(struct primaryIndex));
		pi->key = arr[i];
		pi->offset = i;
		pi->flag = 0;
		if ( bstInsertNode(rootNode,pi) == FAILURE) {
			printf("ERROR!\n\n");
		}
		i++;
	}
	printf("BST-001 Successful!\n\n");
	//----------------------------------------------------------------------------------------------------------
	printf("Testing BST-003!\n");
	struct primaryIndex pi;
	pi.key = 2;
	pi.flag = 0;
	pi.offset = 11;

	if ( bstInsertNode(rootNode,&pi) == FAILURE) {
		printf("BST-003 Successful!\n\n");
	}
	else {
		printf("ERROR!\n\n");
	}
	//----------------------------------------------------------------------------------------------------------
	printf("Testing BST-004!\n");
	if ( bstMarkDeleted(*rootNode,2) == FAILURE ) {
		printf("ERROR!!\n");
	}

	if ( bstInsertNode(rootNode,&pi) == FAILURE) {
		printf("ERROR!!\n\n");
	}
	else {
		printf("BST-004 Successful!\n\n");
	}
	//----------------------------------------------------------------------------------------------------------
	printf("Testing BST-005!\n");
	if ( bstMarkDeleted(*rootNode,18) == FAILURE ) {
		printf("ERROR!!\n");
	}
	else {
		printf("BST-004 Successful!\n\n");
	}
	//----------------------------------------------------------------------------------------------------------
	printf("Testing BST-008!\n");
	struct primaryIndex *pi1;
	if ( (pi1 = bstSearchNode(*rootNode,6)) == NULL) {
		printf("ERROR!\n");
	}
	else {
		printf("\nKey : %d\nOffset : %d\nFlag : %c\n",pi1->key,pi1->offset,pi1->flag);
		printf("BST-008 Successful!\n\n");
	}
	//----------------------------------------------------------------------------------------------------------
	printf("Testing BST-009!\n");
	if ( (pi1 = bstSearchNode(*rootNode,11)) != NULL) {
		printf("ERROR!\n");
	}
	else {
		printf("BST-009 Successful!\n\n");
	}
	//----------------------------------------------------------------------------------------------------------
	printf("Testing BST-010!\n");
	if ( bstMarkDeleted(*rootNode,14) == FAILURE ) {
		printf("ERROR!\n");
	}
	if ( (pi1 = bstSearchNode(*rootNode,14)) != NULL) {
		printf("ERROR!\n");
	}
	else {
		printf("BST-010 Successful!\n\n");
	}
	//----------------------------------------------------------------------------------------------------------
	printf("Testing BST-016\n");
	if ( bstDeleteNode(rootNode,2) == FAILURE )
		printf("ERROR!\n");
	else {
		printbst(*rootNode);
		printf("BST-016 Successful!\n\n");
	}
	//----------------------------------------------------------------------------------------------------------
	printf("Testing BST-017\n");
	if ( bstDeleteNode(rootNode,43) != FAILURE )
		printf("ERROR!\n");
	else {
		printf("BST-017 Successful!\n\n");
	}
	//----------------------------------------------------------------------------------------------------------
	printf("Testing BST-018\n");
	if ( bstDeleteNode(rootNode,12) == FAILURE )
		printf("ERROR!\n");
	else {
		printbst(*rootNode);
		printf("BST-018 Successful!\n\n");
	}
	//----------------------------------------------------------------------------------------------------------
	printf("Testing BST-011\n");
	fp = fopen("bst.txt","wb");
	if ( bstPersistNodes(*rootNode,fp) == FAILURE ) {
		printf("ERROR WRITING BST INTO FILE!\n");
	}
	else {
		printf("BST-011 Successful!\n\n");
	}
	fclose(fp);

	//----------------------------------------------------------------------------------------------------------
	printf("Testing BST-012\n");
	fp = fopen("empty_bst.txt","wb");
	*rootNode = NULL;
	if ( bstPersistNodes(*rootNode,fp) == FAILURE ) {
		printf("ERROR WRITING EMPTY BST INTO FILE!\n");
	}
	else {
		printf("BST-012 Successful!\n\n");
	}
	fclose(fp);
	//----------------------------------------------------------------------------------------------------------
	printf("Testing BST-013\n");
	fp = fopen("bst.txt","rb");
	if ((*rootNode = bstLoadFromFile(fp)) == NULL) {
		printf("ERROR!\n");
	}
	else {
		printbst(*rootNode);
		printf("BST-013 Successful!\n\n");
	}
	fclose(fp);
	//----------------------------------------------------------------------------------------------------------
	printf("Testing BST-014\n");
	fp = fopen("no_bst.txt","rb");

	if ((*rootNode = bstLoadFromFile(fp)) != NULL) {
		printf("ERROR!\n");
	}
	else {
		printf("BST-014 Successful!\n\n");
	}
	//----------------------------------------------------------------------------------------------------------
	return 0;
}
