#define _CRT_SECURE_NO_WARNINGS
#include"execute.h"
int main()
{
	FILE *ilf, *m, *metadata, *cfile, *stf;
	ilf = fopen("intermediatelang.txt", "r");
	m = fopen("memory.txt", "r");
	stf = fopen("symboltable.txt", "r");
	metadata = fopen("metadata.txt", "r");
	cfile = fopen("clang.txt", "w");
	fputs("#include<stdio.h>\n", cfile);
	fputs("int main()\n{\n", cfile);
	fputs("int AX,BX,CX,DX,EX,FX,GX,HX;\n", cfile);
	load_memory(m);
	load_intermediatelang(ilf, metadata);
	read_symbol_table(stf, metadata, cfile);
	read_lbls(metadata);
	display(il);
	execute(il, cfile);
	convert_to_c(il, cfile);
	int end;
	scanf("%d", &end);
	return 0;
}