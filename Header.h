#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct intermediatelang
{
	int inno;
	int opcode;
	int parameters[6];
	int len;
};
struct symboltable
{
	char sym;
	int add;
	int size;
};
struct label
{
	char *name;
	int add;
};
struct label lbl[10];
int lblind = 0;
struct symboltable st[10];
void *memory = malloc(1000);
struct intermediatelang il[50];
int inno, nsym;
char get_mem_variable(int index)
{
	for (int i = 0; i < nsym; i++)
	{
		if (i == index)
			return st[i].sym;
	}
	return '\0';
}
void load_memory(FILE *m)
{
	int y;
	for (int i = 0; i < 400; i++)
	{
		fscanf(m, "%d", &y);
		memcpy(&memory + i, &y, sizeof(int));
	}
}
void load_intermediatelang(FILE *ilf, FILE *metadata)
{
	char *s = (char *)malloc(sizeof(char) * 20);

	fscanf(metadata, "%d", &inno);
	int i = 0;
	while (i<inno)
	{
		fscanf(ilf, "%d", &il[i].inno);
		fscanf(ilf, "%d", &il[i].opcode);
		int len = 0;
		fscanf(metadata, "%d", &len);
		il[i].len = len;
		int j = 0;
		while (j<len)
		{
			fscanf(ilf, "%d", &il[i].parameters[j]);
			j++;
		}
		i++;
	}

}
void display(intermediatelang il[])
{

	for (int i = 0; i < inno; i++)
	{
		printf("%d    %d    ", il[i].inno, il[i].opcode);
		for (int j = 0; j < il[i].len; j++)
		{
			printf("%d ", il[i].parameters[j]);

		}


		printf("\n");

	}

}
void read_symbol_table(FILE *stf, FILE *metadata, FILE *cfile)
{
	char sym;
	int add, size, i = 0;
	fscanf(metadata, "%d", &nsym);
	while (i<nsym)
	{
		fscanf(stf, "%c", &sym);
		fscanf(stf, "%d", &add);
		fscanf(stf, "%d", &size);
		st[i].sym = sym;
		st[i].add = add;
		st[i].size = size;
		fscanf(stf, "%c", &sym);
		if (size != 0)
			fprintf(cfile, "int %c;\n", st[i].sym);
		else
			fprintf(cfile, "const int %c;\n", st[i].sym);
		i++;
	}
}
void read_lbls(FILE *metadata)
{
	fscanf(metadata, "%d", &lblind);
	for (int i = 0; i < lblind; i++)
	{
		fscanf(metadata, "%d", &lbl[i].add);
		//fgetc(metadata);
		lbl[i].name = (char *)malloc(sizeof(char) * 10);
		fscanf(metadata, "%s", lbl[i].name);
	}
}
char * get_label(int add)
{
	for (int i = 0; i < lblind; i++)
	{
		if (lbl[i].add == add)
			return lbl[i].name;
	}
	return "A";
}