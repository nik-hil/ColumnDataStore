
#include "common.h"

//structure for stack.

//structure for stack.

//Initialize the stack.Return 0 for success and- -1 for failure.
int stackInit(struct stack *s)
{
	  s->top=-1;
	  return 0;
}


//pop the data from the stack and store its address 'data'.Return 0 for success and -1 for failure.
int stackPop(struct stack *s,int *data)
{
	if(s == NULL )return 1;
   if(s->top!=-1)
    {
       *data=s->stack[(s->top)--];
       return 0;
     }
   else 
     return 1;
}

//push the data to the stack.Return 0 for success and -1 for failure.
int stackPush(struct stack *s, int data)
{
	if(s->top==99)
	    return 1;
	  else
	  {
	    s->stack[++(s->top)]=data;
	    return 0;
  }
}

//Write the stack to the file for making it persistent.Return 0 for success and -1 for failure.
int stackPersist(FILE *fp, struct stack *s)
{

	if((fp==NULL)||(s==NULL))
	   		return 1;
	  else
	  {
   	     fwrite(s,sizeof(struct stack),1,fp);
	  }
	//fclose(fp);
   return 0;
  }



//Populate the stack from the file.Return 0 for success and -1 for failure.
int stackLoadFromFile(FILE *fp, struct stack * s)
{

   if(!fp) return 1;

   if(fread(s,sizeof(struct stack),1,fp)!=1)
	   return 1;

//	fclose(fp);
   return 0;
}


