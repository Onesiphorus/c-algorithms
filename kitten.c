//Paul Bagley
//CSCI 4230
//Assignment 2

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE * pFile;
	int c;

	if(argc != 2)
	{
		printf("usage: kitten <filename>\n");
	}
	else
	{
		pFile = fopen (argv[1], "r");
		if (pFile == NULL) perror ("Error opening file");
		else 
		{
			while(( c = fgetc(pFile)) != EOF)
			{
				printf("%c",c);
			}
			fclose (pFile);
		}
	}
	return 0;
}
