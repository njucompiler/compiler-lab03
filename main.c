#include <stdlib.h>
#include <stdio.h>
extern FILE* yyin;

int main(int argc, char** argv)
{
	if ( argc <= 1 ) return 1;
	printf("%s %s\n",argv[1],argv[2] );
	FILE* fr = fopen(argv[1], "r");
	if ( !fr )
	{
		perror(argv[1]);
		return 1;
	}
	yyrestart(fr);
	yyparse();
	show_all(argv[2]);
	return 0;
}
