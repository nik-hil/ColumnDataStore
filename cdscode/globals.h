/*
 * globals.h
 *
 *  Created on: 15-Nov-2010
 *      Author: ram
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

struct colDataStore cdsInfo;

int cds_printRecord( struct dataRecord* record );
int cds_printCollection(struct LISTCOLLECTION *recordset );
int cds_printDatabase();
static void printAllRecords( struct bstNode *node );
int writeString( FILE *fp, int position, char *str, int maxsize );
char *readString( FILE *fp, int position, int maxsize );

#endif /* GLOBALS_H_ */
