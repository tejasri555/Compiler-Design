#include"Header.h"
int registers[8];
char * get_reg_variable(int index)
{
	if (index == 0)
		return "AX";
	if (index == 1)
		return "BX";
	if (index == 2)
		return "CX";
	if (index == 3)
		return "DX";
	if (index == 4)
		return "EX";
	if (index == 5)
		return "FX";
	if (index == 6)
		return "GX";
	if (index == 7)
		return "HX";
}
void execute(struct intermediatelang interlang[], FILE *cfile)
{
	int i = 0, ifflag = 0;
	while (i<inno)
	{
		switch (interlang[i].opcode)
		{
		case 1:
			memcpy(&memory + interlang[i].parameters[0], &registers[interlang[i].parameters[1]], sizeof(int));
			i++;
			break;
		case 2:
			memcpy(&memory + interlang[i].parameters[1], &registers[interlang[i].parameters[0]], sizeof(int));
			i++;
			break;
		case 3:
			registers[interlang[i].parameters[0]] = registers[interlang[i].parameters[1]] + registers[interlang[i].parameters[2]];
			i++;
			break;
		case 4:
			registers[interlang[i].parameters[0]] = registers[interlang[i].parameters[1]] - registers[interlang[i].parameters[2]];
			i++;
			break;
		case 5:
			registers[interlang[i].parameters[0]] = registers[interlang[i].parameters[1]] * registers[interlang[i].parameters[2]];
			i++;
			break;
		case 6:
			i = interlang[i].parameters[0] - 1;
			break;
		case 7:
			if (interlang[i].parameters[2] == 8)
			{
				if (registers[interlang[i].parameters[0]] == registers[interlang[i].parameters[1]])
				{
					ifflag = 1;
					i++;
				}
				else
					i = interlang[i].parameters[3] - 1;
			}
			else if (interlang[i].parameters[2] == 9)
			{
				if (registers[interlang[i].parameters[0]] < registers[interlang[i].parameters[1]])
				{
					ifflag = 1;
					i++;
				}
				else
					i = interlang[i].parameters[3] - 1;
			}
			else if (interlang[i].parameters[2] == 10)
			{
				if (registers[interlang[i].parameters[0]] > registers[interlang[i].parameters[1]])
				{
					ifflag = 1;
					i++;
				}
				else
					i = interlang[i].parameters[3] - 1;
			}
			else if (interlang[i].parameters[2] == 11)
			{
				if (registers[interlang[i].parameters[0]] <= registers[interlang[i].parameters[1]])
				{
					ifflag = 1;
					i++;
				}
				else
					i = interlang[i].parameters[3] - 1;
			}
			else if (interlang[i].parameters[2] == 12)
			{
				if (registers[interlang[i].parameters[0]] >= registers[interlang[i].parameters[1]])
				{
					ifflag = 1;
					i++;
				}
				else
					i = interlang[i].parameters[3] - 1;
			}
			break;
		case 13:
			printf("%d ", registers[interlang[i].parameters[0]]);
			i++;
			break;
		case 14:scanf("%d", &registers[interlang[i].parameters[0]]);
			i++;
			break;
		case 16:

			if (ifflag == 1)
			{
				i = interlang[i].parameters[0] - 1;
			}
			else
			{
				ifflag = 0;
				i++;
			}
			break;
		default:i++;
		}
	}
}
void convert_to_c(struct intermediatelang interlang[], FILE *cfile)
{
	int i = 0, ifflag = 0;
	char *s, *label = (char *)malloc(sizeof(char) * 10);
	while (i<inno)
	{
		switch (interlang[i].opcode)
		{
		case 1:
			fprintf(cfile, "%c=%s;\n", get_mem_variable(interlang[i].parameters[0]), get_reg_variable(interlang[i].parameters[1]));
			i++;
			break;
		case 2:
			fprintf(cfile, "%s=%c;\n", get_reg_variable(interlang[i].parameters[0]), get_mem_variable(interlang[i].parameters[1]));
			i++;
			break;
		case 3:
			fprintf(cfile, "%s=%s+%s;\n", get_reg_variable(interlang[i].parameters[0]), get_reg_variable(interlang[i].parameters[1]), get_reg_variable(interlang[i].parameters[2]));
			i++;
			break;
		case 4:
			fprintf(cfile, "%s=%s-%s;\n", get_reg_variable(interlang[i].parameters[0]), get_reg_variable(interlang[i].parameters[1]), get_reg_variable(interlang[i].parameters[2]));
			i++;
			break;
		case 5:
			fprintf(cfile, "%s=%s*%s;\n", get_reg_variable(interlang[i].parameters[0]), get_reg_variable(interlang[i].parameters[1]), get_reg_variable(interlang[i].parameters[2]));
			i++;
			break;
		case 6:
			s = (char *)malloc(sizeof(char) * 10);
			s = get_label(interlang[i].parameters[0] - 1);
			fprintf(cfile, "goto %s;\n", s);
			i++;
			break;
		case 7:
			if (interlang[i].parameters[2] == 8)
			{
				fprintf(cfile, "if(%s == %s){\n", get_reg_variable(interlang[i].parameters[0]), get_reg_variable(interlang[i].parameters[1]));
			}
			else if (interlang[i].parameters[2] == 9)
			{
				fprintf(cfile, "if(%s < %s){\n", get_reg_variable(interlang[i].parameters[0]), get_reg_variable(interlang[i].parameters[1]));

			}
			else if (interlang[i].parameters[2] == 10)
			{
				fprintf(cfile, "if(%s > %s){\n", get_reg_variable(interlang[i].parameters[0]), get_reg_variable(interlang[i].parameters[1]));
			}
			else if (interlang[i].parameters[2] == 11)
			{
				fprintf(cfile, "if(%s <= %s){\n", get_reg_variable(interlang[i].parameters[0]), get_reg_variable(interlang[i].parameters[1]));

			}
			else if (interlang[i].parameters[2] == 12)
			{
				fprintf(cfile, "if(%s >= %s){\n", get_reg_variable(interlang[i].parameters[0]), get_reg_variable(interlang[i].parameters[1]));
			}
			i++;
			break;
		case 13:
			fprintf(cfile, "printf(\"%%d \",%s);\n", get_reg_variable(interlang[i].parameters[0]));
			i++;
			break;
		case 14:
			fprintf(cfile, "scanf(\"%%d\",&%s);\n", get_reg_variable(interlang[i].parameters[0]));
			i++;
			break;
		case 15:
			fprintf(cfile, "\n}\n");
			i++;
			break;
		case 16:
			fprintf(cfile, "}\n");
			fprintf(cfile, "else\n");
			fprintf(cfile, "{\n");
			i++;
			break;
		case 17:
			fprintf(cfile, "%s:\n", get_label(interlang[i].parameters[0] - 1));
			i++;
		}
	}
	fputs("return 0;\n}\n", cfile);
	fclose(cfile);
}