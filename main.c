#include <stdlib.h>
#include <stdio.h>
extern FILE* yyin;
char output[20];

int main(int argc, char** argv)
{
	if ( argc <= 1 ) return 1;
	FILE* fr = fopen(argv[1], "r");
	strcpy(output,argv[2]);
	if ( !fr )
	{
		perror(argv[1]);
		return 1;
	}
	yyrestart(fr);
	yyparse();
	return 0;
}
