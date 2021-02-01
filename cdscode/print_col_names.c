/*
 * print_col_names.c
 *
 *  Created on: 15-Nov-2010
 *      Author: ram
 */

#include "common.h"

void printcolnames()
{
	int i=0;
	for(i=0;i<cdsInfo.numCols;i++)
	{
		printf("\n%s",cdsInfo.fileregister[i].colname);
	}
}
