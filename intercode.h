

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;
typedef struct InterCodes_* InterCodes;

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
	enum { ASSIGN, ADD, SUB, MUL, DIVI} kind;
	union {
		struct { Operand right, left; } assign;
		struct { Operand result, op1, op2; } binop;
		} u;
};

struct InterCodes_
{
	InterCode code; 
	InterCodes prev, next; 
};
void var_no_init();
InterCode new_interCode(int kind);
Operand new_operand(int kind,int value);
Operand new_operand_name(char* name);
Operand translate_Exp(node* exp,char* place);
