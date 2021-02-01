
int main(int argc,char *args[])
{
	struct stack s;

	FILE *fp;

	stackInit(&s);
	int i,x,data;
	printf("persist %d\n",stackPersist(fp,&s));	
	stackPop(&s,&data);
	printf("%d\n",data);

	for(x=0;x<100;x++)
	{
		stackPush(&s,x);
	}
	printf("push %d\n",stackPush(&s,x));
	
	stackPop(&s,&data);
	printf("%d\n",data);
	stackPop(&s,&data);
	printf("%d\n",data);	
	fp=fopen("out.txt","wb");
	printf("persist %d\n",stackPersist(fp,&s));
	fp=fopen("out.txt","rb");
	printf("load %d\n",stackLoadFromFile(fp,&s));
	stackPop(&s,&data);

	printf("%d\n",data);
	
	
	for(x=0;x<99;x++)
	{
		;
		printf("%d\n",stackPop(&s,&data));
	}


}

