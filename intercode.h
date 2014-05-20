#ifdef _INTERCODE_
#define _INTERCODE_

#include "node.h"
#include "string.h"
#include "stdio.h"
typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;
typedef struct InterCodes_* InterCodes;

struct Operand_ {
	enum { VARIABLE, CONSTANT, ADDRESS, TEMP,LABEL} kind;
	int is_min;
	union {
	char name[20];
	int var_no;
	int value;
	int label_no;
	} u;
};
struct InterCode_
{
	enum { ASSIGN, ADD, SUB, MUL, DIVI, LAB, GOTO, RET} kind;
	union {
		struct { Operand right, left; } assign;
		struct { Operand result, op1, op2; } binop;
		struct { Operand op; }onlyop;
		} u;
};

struct InterCodes_
{
	InterCode code; 
	InterCodes prev, next; 
};

InterCodes intercodes_head;

void var_no_init();
InterCode new_interCode(int kind);
Operand new_operand(int kind,int value);
Operand new_operand_name(char* name);
Operand translate_Exp(node* exp,char* place);
void InterCodes_init();
void InterCodes_link(InterCodes prev,InterCodes next);
void head_init();
void intercode_aly(node* p);
void printf_Operand(Operand p);
void printf_ASSIGN(InterCodes p);
void printf_ADD(InterCodes p);
void printf_SUB(InterCodes p);
void printf_MUL(InterCodes p);
void printf_DIV(InterCodes p);
void printf_LABEL(InterCodes p);
void printf_GOTO(InterCodes p);
void printf_RETURN(InterCodes p);
void show_all(char* output);

#endif