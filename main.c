#include <stdlib.h>
#include <stdio.h>
extern FILE* yyin;

int main(int argc, char** argv)
{
	if ( argc <= 1 ) return 1;
	printf("%s %s\n",argv[2],argv[3] );
	FILE* fr = fopen(argv[2], "r");
	if ( !fr )
	{
		perror(argv[2]);
		return 1;
	}
	yyrestart(fr);
	yyparse();
	show_all(argv[3]);
	return 0;
}
