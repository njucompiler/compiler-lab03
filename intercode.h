
#define MAX_LINE 1000

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;
struct Operand_ {
	enum { VARIABLE, CONSTANT, ADDRESS, TEMP} kind;
	union {
	char name[20];
	int var_no;
	int value;
	} u;
};
struct InterCode_
{
	enum { ASSIGN, ADD, SUB, MUL} kind;
	union {
		struct { Operand right, left; } assign;
		struct { Operand result, op1, op2; } binop;
		} u;
	InterCode next;
};

void var_no_init();
InterCode new_interCode(int kind);
Operand new_operand(int kind,int value);
Operand new_operand_name(char* name);
Operand translate_Exp(node* exp,char* place);