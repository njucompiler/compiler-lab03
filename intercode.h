#ifndef _INTERCODE_H_
#define _INTERCODE_H_

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "node.h"

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;
typedef struct InterCodes_* InterCodes;

typedef struct Operand_ {
	enum { VARIABLE, CONSTANT, ADDRESS, TEMP,LABEL,FUNC_op,PARAM_op,ADDR_op} kind;
	int is_min;
	union {
	char name[20];
	int var_no;
	int value;
	int label_no;
	char *func;
	char *param;
	} ;
}Operand_;
typedef struct InterCode_
{
	enum { ASSIGN, ADD, SUB, MUL, DIVI, LAB, GOTO, RET, ADDR} kind;
	union {
		struct { Operand right, left; } assign;
		struct { Operand result, op1, op2; } binop;
		struct { Operand op; }onlyop;
		};
}InterCode_;

typedef struct InterCodes_
{
	InterCode code; 
	InterCodes prev, next; 
}InterCodes_;

InterCodes intercodes_head;

void var_no_init();
InterCode new_interCode(int kind);
Operand new_operand(int kind,int value);
Operand new_operand_name(char* name);
Operand new_label();
Operand new_temp();
InterCodes translate_Exp(node* exp,Operand place);
InterCodes translate_Stmtlist(node* Stmtlist);
InterCodes translate_Args(node* Args,Operand *arg,int num);
InterCodes translate_Struct(node *Exp);
InterCodes translate_Array(node *Exp);
InterCodes InterCodes_init();
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
int getSize(char* p);

#endif
