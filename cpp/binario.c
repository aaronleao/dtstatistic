#include<stdio.h>

/* Our structure */
struct rec
{
	int x,y,z;
};
int main()
{
	int counter;
	FILE *ptr_myfile;
	FILE *ptr_myfile1;
	struct rec my_record;

	ptr_myfile=fopen("test.bin","wb");
	ptr_myfile1=fopen("test.txt","w");
	if (!ptr_myfile)
	{
		printf("Unable to open file!");
		return 1;
	}
	if (!ptr_myfile1)
	{
		printf("Unable to open file!");
		return 1;
	}
	for ( counter=1; counter <= 10; counter++)
	{
		my_record.x= counter;
		fwrite(&my_record, sizeof(struct rec), 1, ptr_myfile);
		fprintf (ptr_myfile1, "%d",my_record.x);
	}
	fclose(ptr_myfile);
	fclose(ptr_myfile1);
	return 0;
}