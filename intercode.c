
#include "intercode.h"
#include "node.h"
#include "string.h"
#include "stdio.h"


int var_no;
InterCodes head;
void InterCodes_init(){
	InterCodes temp = (InterCodes)malloc(sizeof(InterCodes_));
	temp->prev = NULL;
	temp->next = NULL;
	return temp;
}

void InterCodes_link(InterCodes prev,InterCodes next){
	InterCodes temp = prev;
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = next;
	next->prev = prev;
}

void head_init(){
	head = InterCodes_init();
}
void var_no_init(){
	var_no = 1;
}
void printf_Operand(Operand p){
	switch(p->kind){
		case VARIABLE:
			fprintf(fp,"%s",p->name);
			break;
		case CONSTANT:
			fprintf(fp,"#%d",p->value);
			break;
		case ADDRESS:
			fprintf(fp,"#%d",p->value);
			break;
		case TEMP:
			fprintf(fp,"%s",p->name);
			break;
	}
}
void printf_ASSIGN(InterCodes *p){
	printf_Operand(p->left);
	fputs(" := ");
	printf_Operand(p->right);
}
void printf_ADD(InterCodes *p){
	printf_Operand(p->result);
	fputs(" := ");
	printf_Operand(p->op1);
	fputs(" + ");
	printf_Operand(p->op2);
}
void printf_SUB(InterCodes *p){
	printf_Operand(p->result);
	fputs(" := ");
	printf_Operand(p->op1);
	printf(" - ");
	printf_Operand(p->op2);
}
void printf_MUL(InterCodes *p){
	printf_Operand(p->result);
	fputs(" := ");
	printf_Operand(p->op1);
	fputs(" * ");
	printf_Operand(p->op2);
}
void printf_DIV(InterCodes *p){
	printf_Operand(p->result);
	fputs(" := ");
	printf_Operand(p->op1);
	fputs(" / ");
	printf_Operand(p->op2);
}
void show_all(InterCodes *p){
	while(p!=NULL){
		switch(p->code->kind){
			case ASSIGN:
				printf_ASSIGN(p);
				break;
			case ADD:
				printf_ADD(p);
				break;
			case SUB:
				printf_SUB(p);
				break;
			case MUL:
				printf_MUL(p);
				break;
			case DIV:
				printf_DIV(p);
				break;
		}
		p=p->next;
		printf("\n");
	}
}


InterCode* new_interCode(int kind){//init a new interCode
	InterCode code = (InterCode)malloc(sizeof(InterCode_));
	code.kind = kind;
	if(kind == 0){//assignop
		code.assign = (assign *)malloc(sizeof(assign));
	}
	else{
		code.binop = (binop *)malloc(sizeof(binop));
	}
	return code;
}

Operand new_operand(int kind,int value){//init a new operand
	Operand op = (Operand)malloc(sizeof(Operand_));
	op.kind = kind;
	if(kind == 1)//constant
		op.value = value;
	else
		op.var_no = var_no;
	return op;
}

Operand new_operand_name(char* name){
	Operand op = (Operand)malloc(sizeof(Operand_));
	op.kind = 0;//var
	strcpy(op.name,name);
	return op;
}

char* new_temp(){
	char temp[8] = "t";
	char num[4];
	sprintf(str,"%d",var_no);
	strcat(temp,num);
	var_no++;
	return temp;
}

Operand translate_Exp(node* exp,char* place){
	//-------------------------------------------------Exp ASSIGNOP Exp
	if(exp->exp_type == 7){
		t_no = var_no;
		char t = new_temp();		
		InterCodes codes1 = InterCodes_init();
		InterCodes codes2 = InterCodes_init();
		codes1 = translate_Exp(exp->child->brother->brother,t);
		codes2.code = new_interCode(0);
		codes2.code.assign.left = new_operand_name(exp->child->node_value);
		codes2.code.assign.right = new_operand(0,t_no);

		InterCodes codes3 = InterCodes_init();
		codes3.code = new_interCode(0);
		codes3.code.assign.left = new_operand(3,t_no);
		codes3.code.assign.right = new_operand_name(exp->child->node_value);

		InterCodes_link(codes1,codes2);
		codes2.next = codes3;
		codes3.prev = codes2;
		return codes1;
	}
	//-------------------------------------------------Exp AND Exp
	else if(exp->exp_type == 8){

	}

	//-------------------------------------------------Exp OR Exp
	else if(exp->exp_type == 9){

	}

	//-------------------------------------------------Exp RELOP Exp
	else if(exp->exp_type == 10){
		
	}

	//-------------------------------------------------Exp PLUS Exp
	else if(exp->exp_type == 11){
		int t1_no = var_no;
		int t2_no = t1_no+1;
		char* t1 = new_temp();
		char* t2 = new_temp();

		InterCodes codes1 = InterCodes_init();
		InterCodes codes2 = InterCodes_init();
		InterCodes codes3 = InterCodes_init();
		codes1 = translate_Exp(exp->child->brother->brother,t1);
		codes2 = translate_Exp(exp->child,t2);
		codes3.code = new_interCode(1);//plus
		if(place[0] == 't');
			codes3.code.binop.result = new_operand(3,t1_no-1);
		else
			codes3.code.binop.result = new_operand_name(place);
		codes3.code.binop.op1 = new_operand(3,t1_no);
		codes3.code.binop.op2 = new_operand(3,t2_no);

		InterCodes_link(codes1,codes2);
		InterCodes_link(codes2,codes3);

		return codes1;
	}

	//-------------------------------------------------Exp MINUS Exp
	else if(exp->exp_type == 12){
		int t1_no = var_no;
		int t2_no = t1_no+1;
		char* t1 = new_temp();
		char* t2 = new_temp();

		InterCodes codes1 = InterCodes_init();
		InterCodes codes2 = InterCodes_init();
		InterCodes codes3 = InterCodes_init();
		codes1 = translate_Exp(exp->child->brother->brother,t1);
		codes2 = translate_Exp(exp->child,t2);
		codes3.code = new_interCode(2);//sub
		if(place[0] == 't');
			codes3.code.binop.result = new_operand(3,t1_no-1);
		else
			codes3.code.binop.result = new_operand_name(place);
		codes3.code.binop.op1 = new_operand(3,t1_no);
		codes3.code.binop.op2 = new_operand(3,t2_no);

		InterCodes_link(codes1,codes2);
		InterCodes_link(codes2,codes3);

		return codes1;
	}

	//--------------------------------------------------Exp STAR Exp
	else if(exp->exp_type == 13){
		int t1_no = var_no;
		int t2_no = t1_no+1;
		char* t1 = new_temp();
		char* t2 = new_temp();

		InterCodes codes1 = InterCodes_init();
		InterCodes codes2 = InterCodes_init();
		InterCodes codes3 = InterCodes_init();
		codes1 = translate_Exp(exp->child->brother->brother,t1);
		codes2 = translate_Exp(exp->child,t2);
		codes3.code = new_interCode(3);//plus
		if(place[0] == 't');
			codes3.code.binop.result = new_operand(3,t1_no-1);
		else
			codes3.code.binop.result = new_operand_name(place);
		codes3.code.binop.op1 = new_operand(3,t1_no);
		codes3.code.binop.op2 = new_operand(3,t2_no);

		InterCodes_link(codes1,codes2);
		InterCodes_link(codes2,codes3);

		return codes1;
	}

	//--------------------------------------------------Exp DIV Exp
	else if(exp->exp_type == 14){	
		int t1_no = var_no;
		int t2_no = t1_no+1;
		char* t1 = new_temp();
		char* t2 = new_temp();

		InterCodes codes1 = InterCodes_init();
		InterCodes codes2 = InterCodes_init();
		InterCodes codes3 = InterCodes_init();
		codes1 = translate_Exp(exp->child->brother->brother,t1);
		codes2 = translate_Exp(exp->child,t2);
		codes3.code = new_interCode(4);//div
		if(place[0] == 't');
			codes3.code.binop.result = new_operand(3,t1_no-1);
		else
			codes3.code.binop.result = new_operand_name(place);
		codes3.code.binop.op1 = new_operand(3,t1_no);
		codes3.code.binop.op2 = new_operand(3,t2_no);

		InterCodes_link(codes1,codes2);
		InterCodes_link(codes2,codes3);

		return codes1;
	}

	//--------------------------------------------------LP Exp RP
	else if(exp->exp_type == 15){
		
	}

	//--------------------------------------------------MINUS Exp
	else if(exp->exp_type == 16){
		int t1_no = var_no;
		char* t1 = new_temp();
		InterCodes codes1 = InterCodes_init();
		InterCodes codes2 = InterCodes_init();
		codes1 = translate_Exp(exp->child->brother,t1);
		codes2.code = new_interCode(0);
		if(place[0] == 't')
			codes2.code.assign.left = new_operand(3,t1_no-1);
		else
			codes2.code.assign.left = new_operand_name(place);
		codes2.code.assign.right = new_operand(3,-t1_no);

		InterCodes_link(codes1,codes2);
		return codes1;
	}

	//---------------------------------------------------NOT Exp
	else if(exp->exp_type == 17){
		
	}

	//---------------------------------------------------ID LP Args RP
	else if(exp->exp_type == 18){
		
	}

	//---------------------------------------------------ID LP RP
	else if(exp->exp_type == 19){
		
	}

	//--------------------------------------------------Exp LB Exp RB
	else if(exp->exp_type == 20){
		
	}

	//--------------------------------------------------Exp DOT ID
	else if(exp->exp_type == 21){	
		
	}

	//---------------------------------------------------ID
	else if(exp->exp_type == 22){
		/*????
		InterCode code = new_interCode(0);
		code.assign.left = new_operand(0,var_no);
		code.assign.right = new_operand_name(exp->node_value);
		return code;*/
	}

	//--------------------------------------------------INT
	else if(exp->exp_type == 23){
		InterCodes codes = InterCodes_init();
		codes.code = new_interCode(0);
		codes.code.assign.right = new_operand(1,exp->node_int);
		codes.code.assign.left = new_operand(3,var_no);
		var_no++;
		return codes;
	}

	//--------------------------------------------------FLOAT
	else if(exp->exp_type == 24){
		
	}
} 

Operand translate_Stmt(node* Stmt){
	if(strcmp(Stmt->child->node_value,"Exp") == 0){

	}
	else if(strcmp(Stmt->child->node_value,"CompSt") == 0){

	}
	else if(strcmp(Stmt->child->node_value,"RETURN") == 0){

	}
	else if(strcmp(Stmt->child->node_value,"WHILE") == 0){

	}
	else if(Stmt->child->brother-)
} 
