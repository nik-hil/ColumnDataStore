#include "common.h"


char *strTok(char *string, char *delimiter)
{
	static char str[50];
	char* output=(char*)malloc(sizeof(char)*10);
	char* temp=(char*)malloc(sizeof(char)*50);
	int i=0,j,k,p,q,tokenlength=0;
	if(string!=NULL)
		strcpy(str,string);	

	if(strcmp(str,"")==0)
		return NULL;
	
	strcpy(temp,"");
	for(i=0;i<strlen(str);i++)
	{	
		if(str[i]==delimiter[0])
		{
			int count=1;
			for(p=i+1,q=1;q<strlen(delimiter);p++,q++)
				if(str[p]==delimiter[q])
					count++;
			if(count==strlen(delimiter))	
			{
				output[tokenlength++]='\0';
				for(j=i+strlen(delimiter),k=0;j<strlen(str);j++,k++)
					temp[k]=str[j];
			
				strcpy(str,"");
				strcpy(str,temp);

				return output;
			}
		}
		else
			output[tokenlength++]=str[i];
	}
	
	strcpy(str,"");
	return output;

}

