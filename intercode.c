#include "node.h"
#include "intercode.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
FILE* fp;
extern char* output;

int var_no;
InterCodes InterCodes_init(){
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
	intercodes_head = InterCodes_init();
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
		case LAB:
			fprintf(fp,"label%d:",p->label_no);
			break;
		case GOTO:
			fprintf(fp,"label%d",p->label_no);
		case RET:
			fprintf(fp,"%s",p->name);
	}
}
void printf_ASSIGN(InterCodes q){
	InterCode p = q->code;
	printf_Operand(p->assign.left);
	fputs(" := ",fp);
	printf_Operand(p->assign.right);
}
void printf_ADD(InterCodes q){
	InterCode p = q->code;
	printf_Operand(p->binop.result);
	fputs(" := ",fp);
	printf_Operand(p->binop.op1);
	fputs(" + ",fp);
	printf_Operand(p->binop.op2);
}
void printf_SUB(InterCodes q){
	InterCode p = q->code;
	printf_Operand(p->binop.result);
	fputs(" := ",fp);
	printf_Operand(p->binop.op1);
	fputs(" - ",fp);
	printf_Operand(p->binop.op2);
}
void printf_MUL(InterCodes q){
	InterCode p = q->code;
	printf_Operand(p->binop.result);
	fputs(" := ",fp);
	printf_Operand(p->binop.op1);
	fputs(" * ",fp);
	printf_Operand(p->binop.op2);
}
void printf_DIV(InterCodes q){
	InterCode p = q->code;
	printf_Operand(p->binop.result);
	fputs(" := ",fp);
	printf_Operand(p->binop.op1);
	fputs(" / ",fp);
	printf_Operand(p->binop.op2);
}
void printf_LABEL(InterCodes q){
	InterCode p = q->code;
	fputs("LABEL ",fp);
	printf_Operand(p->onlyop.op);
}
void printf_GOTO(InterCodes q){
	InterCode p = q->code;
	fputs("GOTO ",fp);
	printf_Operand(p->onlyop.op);
}
void printf_RETURN(InterCodes q){
	InterCode p = q->code;
	fputs("RETURN ",fp);
	printf_Operand(p->onlyop.op);
}
void show_all(char* output){
	fp = fopen(output,"w");
	if ( !fp )
	{
		perror(output);
		return ;
	}
	InterCodes p = intercodes_head;
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
			case GOTO:
				printf_GOTO(p);
				break;
			case LABEL:
				printf_LAEBL(p);
				break;
			case RETURN:
				printf_RETURN(p);
				break;
			
		}
		p=p->next;
		fputs("\n",fp);
	}
	fclose(fp);
}


InterCode new_interCode(int kind){//init a new interCode
	InterCode code = (InterCode)malloc(sizeof(InterCode_));
	code->kind = kind;
	/*if(kind == 0){//assignop
		code->assign = (assign *)malloc(sizeof(assign));
	}
	else{
		code->binop = (binop *)malloc(sizeof(binop));
	}*/
	return code;
}

Operand new_operand(int kind,int value){//init a new operand
	Operand op = (Operand)malloc(sizeof(Operand_));
	op->kind = kind;
	op->is_min = 0;
	if(kind == 1)//constant
		op->value = value;
	else
		op->var_no = var_no;
	return op;
}

Operand new_operand_name(char* name){
	Operand op = (Operand)malloc(sizeof(Operand_));
	op->kind = 0;//var
	op->is_min = 0;
	strcpy(op->name,name);
	return op;
}

Operand new_temp(){
	Operand op = (Operand)malloc(sizeof(Operand_));
	op->kind = 3;
	op->is_min = 0;
	op->var_no = var_no;
	var_no++;
	return op;
}

InterCodes translate_Exp(node* exp,Operand place){
	//-------------------------------------------------Exp ASSIGNOP Exp
	if(exp->exp_type == 7){
		Operand t = new_temp();		
		InterCodes codes1 = InterCodes_init();
		InterCodes codes2 = InterCodes_init();
		codes1 = translate_Exp(exp->child->brother->brother,t);
		codes2->code = new_interCode(0);
		codes2->code->assign.left = new_operand_name(exp->child->node_value);
		codes2->code->assign.right = t;

		InterCodes codes3 = InterCodes_init();
		codes3->code = new_interCode(0);
		codes3->code->assign.left = place;
		codes3->code->assign.right = new_operand_name(exp->child->node_value);

		InterCodes_link(codes1,codes2);
		codes2->next = codes3;
		codes3->prev = codes2;
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
		Operand t1 = new_temp();
		Operand t2 = new_temp();

		InterCodes codes1 = InterCodes_init();
		InterCodes codes2 = InterCodes_init();
		InterCodes codes3 = InterCodes_init();
		codes1 = translate_Exp(exp->child->brother->brother,t1);
		codes2 = translate_Exp(exp->child,t2);
		codes3->code = new_interCode(1);//plus
		codes3->code->binop.result = place;
		codes3->code->binop.op1 = t1;
		codes3->code->binop.op2 = t2;

		InterCodes_link(codes1,codes2);
		InterCodes_link(codes2,codes3);

		return codes1;
	}

	//-------------------------------------------------Exp MINUS Exp
	else if(exp->exp_type == 12){
		Operand t1 = new_temp();
		Operand t2 = new_temp();

		InterCodes codes1 = InterCodes_init();
		InterCodes codes2 = InterCodes_init();
		InterCodes codes3 = InterCodes_init();
		codes1 = translate_Exp(exp->child->brother->brother,t1);
		codes2 = translate_Exp(exp->child,t2);
		codes3->code = new_interCode(2);//sub
		codes3->code->binop.result = place;
		codes3->code->binop.op1 = t1;
		codes3->code->binop.op2 = t2;

		InterCodes_link(codes1,codes2);
		InterCodes_link(codes2,codes3);

		return codes1;
	}

	//--------------------------------------------------Exp STAR Exp
	else if(exp->exp_type == 13){
		Operand t1 = new_temp();
		Operand t2 = new_temp();

		InterCodes codes1 = InterCodes_init();
		InterCodes codes2 = InterCodes_init();
		InterCodes codes3 = InterCodes_init();
		codes1 = translate_Exp(exp->child->brother->brother,t1);
		codes2 = translate_Exp(exp->child,t2);
		codes3->code = new_interCode(3);//star
		codes3->code->binop.result = place;
		codes3->code->binop.op1 = t1;
		codes3->code->binop.op2 = t2;

		InterCodes_link(codes1,codes2);
		InterCodes_link(codes2,codes3);

		return codes1;
	}

	//--------------------------------------------------Exp DIV Exp
	else if(exp->exp_type == 14){	
		Operand t1 = new_temp();
		Operand t2 = new_temp();

		InterCodes codes1 = InterCodes_init();
		InterCodes codes2 = InterCodes_init();
		InterCodes codes3 = InterCodes_init();
		codes1 = translate_Exp(exp->child->brother->brother,t1);
		codes2 = translate_Exp(exp->child,t2);
		codes3->code = new_interCode(4);//div
		codes3->code->binop.result = place;
		codes3->code->binop.op1 = t1;
		codes3->code->binop.op2 = t2;

		InterCodes_link(codes1,codes2);
		InterCodes_link(codes2,codes3);

		return codes1;
	}

	//--------------------------------------------------LP Exp RP
	else if(exp->exp_type == 15){
		
	}

	//--------------------------------------------------MINUS Exp
	else if(exp->exp_type == 16){
		Operand t1 = new_temp();
		InterCodes codes1 = InterCodes_init();
		InterCodes codes2 = InterCodes_init();
		codes1 = translate_Exp(exp->child->brother,t1);
		codes2->code = new_interCode(0);
		codes2->code->assign.left = place;
		t1->is_min = 1;
		codes2->code->assign.right = t1;

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
		codes->code = new_interCode(0);
		codes->code->assign.right = new_operand(1,exp->node_int);
		codes->code->assign.left = new_operand(3,var_no-1);
		return codes;
	}

	//--------------------------------------------------FLOAT
	else if(exp->exp_type == 24){
		
	}
} 

InterCodes translate_Cond(node* exp,Operand true_place,Operand false_place){
	if(strcmp(exp->child->name,"NOT")==0){
		
	}
	else if(strcmp(exp->child->brother->name,"RELOP")==0){
		Operand t1 = new_temp();
		Operand t2 = new_temp();
		InterCodes codes1 = translate_Exp(exp->child,t1);
		InterCodes codes2 = translate_Exp(exp->child->brother->brother,t2);
		
	}
	else if(strcmp(exp->child->brother->name,"AND")==0){

	}
	else if(strcmp(exp->child->brother->name,"OR")==0){

	}
}

InterCodes translate_Dec(node* dec){
	/*
	*	Dec
	*	|	VarDec 
	*	|	VarDec ASSIGNOP Exp
	*/	

	if(dec->child->brother != NULL){
		Operand t1 = new_temp();
		InterCodes codes1 = translate_Exp(dec->child->brother->brother, t1);
		//Operand t1 = new_temp();
		//InterCodes codes1 = translate_Vardec(child, t1);
		codes3.code = new_interCode(0);
		codes3.code.left = new_operand_name(dec->child->node_value);
		codes3.code.right = t1;
		InterCodes_link(codes1,codes3);
		//InterCodes_link(codes2,codes3);
		return codes1;
	}
	return NULL;
}

InterCodes translate_Declist(node* declist){
	InterCodes codes1 = InterCodes_init();
	codes1 = translate_Dec(declist->child);
	if(declist->child->brother == NULL){
		return codes1;
	}
	else{
		InterCodes codes2 = InterCodes_init();
		codes1 = translate_Dec(declist->child);
		codes2 = translate_Declist(declist->child->brother->brother);
		InterCodes_link(codes1, codes2);
		return codes1;
	}
}

InterCodes translate_Def(node* deflist){
	if(deflist->child != NULL)
		return translate_Declist(deflist->child->brother);
	else
		return NULL;
}

InterCodes translate_Deflist(node* deflist){
	if(deflist != NULL){
		InterCodes codes1 = InterCodes_init();
		InterCodes codes2 = InterCodes_init();
		codes1 = translate_Def(deflist->child);
		codes2 = translate_Deflist(deflist->child->brother);
		InterCodes_link(codes1,codes2);
	return codes1;
	}
	else
		return NULL;
}

InterCodes translate_Compst(node* CompSt){
	InterCodes codes1 = InterCodes_init();
	InterCodes codes2 = InterCodes_init();
	codes1 = translate_Deflist(CompSt->child->brother);
	codes2 = translate_Stmtlist(CompSt->child->brother->brother);
	InterCodes_link(codes1, codes2);
	return codes1;
}

InterCodes translate_Stmt(node* Stmt){
	if(strcmp(Stmt->child->node_value,"Exp") == 0){
		return translate_Exp(Stmt->child,NULL);
	}
	else if(strcmp(Stmt->child->node_value,"CompSt") == 0){
		return translate_Compst(Stmt->child);
	}
	else if(strcmp(Stmt->child->node_value,"RETURN") == 0){

	}
	else if(strcmp(Stmt->child->node_value,"WHILE") == 0){

	}
	else if(Stmt->child->brother-)
} 

InterCodes translate_Stmtlist(node* Stmtlist){
	if(Stmtlist != NULL){
		InterCodes codes1 = InterCodes_init();
		InterCodes codes2 = InterCodes_init();
		codes1 = translate_Stmt(Stmtlist->child);
		codes2 = translate_Stmtlist(Stmtlist->child->brother);
		InterCodes_link(codes1,codes2);
		return codes1;
	}
	else
		return NULL;
}


void intercode_aly(node *p){		
	char name[20];
	strcpy(name,p->name);
	if(strcmp(name,"Def")==0){
	
	}
	else if(strcmp(name,"ExtDef")==0){

	}
	else if(strcmp(name,"Exp")==0){
		char* t1 = new_temp();
		translate_Exp(p,t1);
		if(p->brother != NULL)
			intercode_aly(p->brother);
		return;
	}
	else if(strcmp(name,"CompSt")==0){

	}
	else if(strcmp(name,"Args")==0){

	}
	else if(strcmp(name,"Stmt")==0){

	}
	if(p->child != NULL)
		intercode_aly(p->child);
	if(p->brother != NULL)
		intercode_aly(p->brother);
	return;
}
