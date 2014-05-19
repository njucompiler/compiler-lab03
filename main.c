#include <stdlib.h>
#include <stdio.h>
#include <intercode.h>
extern FILE* yyin;
extern FILE* fp;

int main(int argc, char** argv)
{
	if ( argc <= 1 ) return 1;
	FILE* fp = fopen(argv[1], "r");
	if ( !f )
	{
		perror(argv[1]);
		return 1;
	}
	FILE* fp = fopen(argv[2],"w");
	yyrestart(f);
	yyparse();
	show_all(InterCodes);
	fclose(fp);
	return 0;
}
