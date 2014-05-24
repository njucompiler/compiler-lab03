
#include "node.h"
#include <assert.h>
#include "intercode.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "type.h"

FILE* fp;

int var_no;
int label_num = 0;
InterCodes InterCodes_init(){
	InterCodes temp = (InterCodes)malloc(sizeof(InterCodes_));
	temp->prev = NULL;
	temp->next = NULL;
	return temp;
}

void InterCodes_link(InterCodes prev,InterCodes next){
	InterCodes temp = prev;
	if(temp == NULL){
		printf("InterCodes_link error prev is NULL\n");
		return;
	}
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = next;
	next->prev = prev;
}

void add_to_head(InterCodes codes){
	InterCodes temp = intercodes_head;
	if(temp == NULL){
		printf("InterCodes_link error prev is NULL\n");
		return;
	}
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = codes;
	codes->prev = temp;
}

void head_init(){
	intercodes_head = InterCodes_init();
	var_no = 1;
}

void printf_Operand(Operand p){
	assert(p != NULL);
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
			fprintf(fp,"t%d",p->var_no);
			break;
		case LABEL:
			fprintf(fp,"label%d",p->label_no);
			break;
		case FUNC_op:
			fprintf(fp,"%s",p->func);
			break;
		case PARAM_op:
			fprintf(fp,"%s",p->param);
			break;
		case ADDR_op:
			fprintf(fp,"*%s",p->name);
			break;
		case op:
			fprintf(fp,"%s",p->op);
			break;
		default:
			break;
	}
}
void printf_ASSIGN(InterCodes q){
	InterCode p = q->code;printf("%d\n",p->kind);printf("kkkkk\n");
	printf_Operand(p->assign.left);
	fputs(" := ",fp);printf("dddddd\n");
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
	fputs(":",fp);
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
void printf_CALL(InterCodes q){
	InterCode p = q->code;
	printf_Operand(p->assign.left);
	fputs(" :=CALL ",fp);
	printf_Operand(p->assign.right);
}
void printf_DEC(InterCodes q){
	InterCode p = q->code;
	fputs("DEC ",fp);
	printf_Operand(p->assign.left);
	fputs(" ",fp);
	printf_Operand(p->assign.right);
}
void printf_ARG(InterCodes q){
	InterCode p = q->code;
	fputs("ARG ",fp);
	printf_Operand(p->onlyop.op);
}
void printf_COND(InterCodes q){
	InterCode p = q->code;
	fputs("IF ",fp);
	printf_Operand(p->cond.op1);
	fprintf(fp," %s ",p->cond.op->op );
	printf_Operand(p->cond.op2);
	fputs(" ",fp);
}
void printf_READ(InterCodes q){
	InterCode p = q->code;
	fputs("READ ",fp);
	printf_Operand(p->onlyop.op);
}
void printf_WRITE(InterCodes q){
	InterCode p = q->code;
	fputs("WRITE ",fp);
	printf_Operand(p->onlyop.op);
}
void show_all(char* output){
	fp = fopen(output,"w");
	if ( !fp )
	{
		perror(output);
		return ;
	}
	InterCodes p = intercodes_head->next;int i = 0;
	while(p!=NULL){i++;
		switch(p->code->kind){
			case ASSIGN:printf("11111\n");
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
			case DIVI:
				printf_DIV(p);
				break;
			case GOTO:
				printf_GOTO(p);
				break;
			case LAB:
				printf_LABEL(p);
				break;
			case RET:
				printf_RETURN(p);
				break;
			case COND:
				printf_COND(p);
				break;
			case DEC:
				printf_DEC(p);
				break;
			case FUNC_I:
				printf_Operand(p->code->onlyop.op);
			case DEC:
				printf_READ(p);
				break;
			case DEC:
				printf_WRITE(p);
				break;
			default:
				break;

		}
		if(p->code->kind!=COND)
			fputs("\n",fp);
		p=p->next;
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
	else if(kind == 8)
		;
	else 
		op->label_no = value;
	return op;
}

Operand new_operand_name(char* name){
	Operand op = (Operand)malloc(sizeof(Operand_));
	op->kind = 0;//var
	op->is_min = 0;
	strcpy(op->name,name);
	return op;
}
Operand new_label(){
	Operand op = new_operand(4,label_num);
	label_num++;
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
		InterCodes codes1 ;
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
		Operand	label1 = new_label();
		Operand label2 = new_label();
		InterCodes codes1 = InterCodes_init();
		codes1->code = new_interCode(0);
		codes1->code->assign.left = place;
		codes1->code->assign.right = new_operand(1,0);

		InterCodes codes2 = translate_Cond(exp, label1, label2);
		
		InterCodes codes3 = InterCodes_init();
		codes3->code = new_interCode(5);
		codes3->code->onlyop.op = label1;

		InterCodes codes4 = InterCodes_init();
		codes4->code = new_interCode(0);
		codes4->code->assign.left = place;
		codes4->code->assign.right = new_operand(1,1);

		InterCodes codes5 = InterCodes_init();
		codes5->code = new_interCode(LAB);
		codes5->code->onlyop.op = label2; 

		InterCodes_link(codes1,codes2);
		InterCodes_link(codes1,codes3);
		InterCodes_link(codes1,codes4);
		InterCodes_link(codes1,codes5);
		
		return codes1;
	}

	//-------------------------------------------------Exp OR Exp
	else if(exp->exp_type == 9){
		Operand	label1 = new_label();
		Operand label2 = new_label();
		InterCodes codes1 = InterCodes_init();
		codes1->code = new_interCode(0);
		codes1->code->assign.left = place;
		codes1->code->assign.right = new_operand(1,0);

		InterCodes codes2 = translate_Cond(exp, label1, label2);
		
		InterCodes codes3 = InterCodes_init();
		codes3->code = new_interCode(5);
		codes3->code->onlyop.op = label1;

		InterCodes codes4 = InterCodes_init();
		codes4->code = new_interCode(0);
		codes4->code->assign.left = place;
		codes4->code->assign.right = new_operand(1,1);

		InterCodes codes5 = InterCodes_init();
		codes5->code = new_interCode(LAB);
		codes5->code->onlyop.op = label2; 

		InterCodes_link(codes1,codes2);
		InterCodes_link(codes1,codes3);
		InterCodes_link(codes1,codes4);
		InterCodes_link(codes1,codes5);
		
		return codes1;
	}

	//-------------------------------------------------Exp RELOP Exp
	else if(exp->exp_type == 10){
		Operand	label1 = new_label();
		Operand label2 = new_label();
		InterCodes codes1 = InterCodes_init();
		codes1->code = new_interCode(0);
		codes1->code->assign.left = place;
		codes1->code->assign.right = new_operand(1,0);

		InterCodes codes2 = translate_Cond(exp, label1, label2);
		
		InterCodes codes3 = InterCodes_init();
		codes3->code = new_interCode(5);
		codes3->code->onlyop.op = label1;

		InterCodes codes4 = InterCodes_init();
		codes4->code = new_interCode(0);
		codes4->code->assign.left = place;
		codes4->code->assign.right = new_operand(1,1);

		InterCodes codes5 = InterCodes_init();
		codes5->code = new_interCode(LAB);
		codes5->code->onlyop.op = label2; 

		InterCodes_link(codes1,codes2);
		InterCodes_link(codes1,codes3);
		InterCodes_link(codes1,codes4);
		InterCodes_link(codes1,codes5);
		
		return codes1;
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
		Operand	label1 = new_label();
		Operand label2 = new_label();
		InterCodes codes1 = InterCodes_init();
		codes1->code = new_interCode(0);
		codes1->code->assign.left = place;
		codes1->code->assign.right = new_operand(1,0);

		InterCodes codes2 = translate_Cond(exp, label1, label2);
		
		InterCodes codes3 = InterCodes_init();
		codes3->code = new_interCode(5);
		codes3->code->onlyop.op = label1;

		InterCodes codes4 = InterCodes_init();
		codes4->code = new_interCode(0);
		codes4->code->assign.left = place;
		codes4->code->assign.right = new_operand(1,1);

		InterCodes codes5 = InterCodes_init();
		codes5->code = new_interCode(LAB);
		codes5->code->onlyop.op = label2; 

		InterCodes_link(codes1,codes2);
		InterCodes_link(codes1,codes3);
		InterCodes_link(codes1,codes4);
		InterCodes_link(codes1,codes5);
		
		return codes1;
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
		InterCodes codes = InterCodes_init();
		codes->code = new_interCode(0);
		codes->code->assign.right = new_operand_name(exp->node_value);
		codes->code->assign.left = place;
		return codes;
	}

	//--------------------------------------------------INT
	else if(exp->exp_type == 23){
		InterCodes codes = InterCodes_init();
		codes->code = new_interCode(0);
		codes->code->assign.right = new_operand(1,exp->node_int);printf("doubi\n");printf("%d\n",place->kind);printf("%d\n",var_no);
		codes->code->assign.left = place;
		return codes;
	}

	//--------------------------------------------------FLOAT
	else if(exp->exp_type == 24){
		
	}

} 

InterCodes translate_Cond(node* exp,Operand true_place,Operand false_place){
	if(strcmp(exp->child->name,"NOT")==0){
		return translate_Cond(exp->child->brother,true_place,false_place);
	}
	else if(strcmp(exp->child->brother->name,"RELOP")==0){
		Operand t1 = new_temp();
		Operand t2 = new_temp();
		InterCodes codes1 = translate_Exp(exp->child,t1);
		InterCodes codes2 = translate_Exp(exp->child->brother->brother,t2);
		InterCodes codes3 = InterCodes_init();
		codes3->code = new_interCode(COND);
		codes3->code->cond.op1 = t1;
		codes3->code->cond.op2 = t2;
		codes3->code->cond.op = new_operand(op,0);
		strcpy(codes3->code->cond.op->op,exp->child->brother->node_value);
		printf("op:%s\n", codes3->code->cond.op->op);
		InterCodes codes4 = InterCodes_init();
		codes4->code = new_interCode(GOTO);
		codes4->code->onlyop.op = true_place;

		InterCodes codes5 = InterCodes_init();
		codes5->code = new_interCode(GOTO);
		codes5->code->onlyop.op = false_place;

		InterCodes_link(codes1,codes2);
		InterCodes_link(codes1,codes3);
		InterCodes_link(codes1,codes4);
		InterCodes_link(codes1,codes5);

		return codes1;
	}
	else if(strcmp(exp->child->brother->name,"AND")==0){
		Operand label1 = new_label();
		InterCodes codes1 = translate_Cond(exp->child, label1, false_place);
		InterCodes codes2 = translate_Cond(exp->child->brother->brother, true_place, false_place);
		InterCodes codes3 = InterCodes_init();
		codes3->code = new_interCode(LAB);
		codes3->code->onlyop.op = label1;
		
		InterCodes_link(codes1,codes3);
		InterCodes_link(codes1,codes2);
		return codes1;
	}
	else if(strcmp(exp->child->brother->name,"OR")==0){
		Operand label1 = new_label();
		InterCodes codes1 = translate_Cond(exp->child, true_place, label1);
		InterCodes codes2 = translate_Cond(exp->child->brother->brother, true_place, false_place);
		InterCodes codes3 = InterCodes_init();
		codes3->code = new_interCode(LAB);
		codes3->code->onlyop.op = label1;
		
		InterCodes_link(codes1,codes3);
		InterCodes_link(codes1,codes2);
		return codes1;
	}
	else{
		/*Operand t1 = new_temp()
		InterCodes codes1 = translate_Exp(Exp, sym_table, t1)
		code2 = [IF t1 != #0 GOTO label_true]
		return code1 + code2 + [GOTO label_false]
		*/
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
		InterCodes codes3 = InterCodes_init();
		codes3->code = new_interCode(0);
		codes3->code->assign.left = new_operand_name(dec->child->node_value);
		codes3->code->assign.right = t1;
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
	if(strcmp(Stmt->child->name,"Exp") == 0){
		return translate_Exp(Stmt->child,NULL);
	}
	else if(strcmp(Stmt->child->name,"CompSt") == 0){
		return translate_Compst(Stmt->child);
	}
	else if(strcmp(Stmt->child->name,"RETURN") == 0){
		Operand t1 = new_temp();
		InterCodes codes1 =  translate_Exp(Stmt->child->brother,t1);
		
		InterCodes codes2 = InterCodes_init();
		codes2->code = new_interCode(RET);
		codes2->code->onlyop.op = t1;
		
		InterCodes_link(codes1,codes2);
		return codes1;
	}
	else if(strcmp(Stmt->child->name,"WHILE") == 0){
		Operand label1 = new_label();
		Operand label2 = new_label();
		Operand label3 = new_label();

		InterCodes codes1 = InterCodes_init();
		codes1->code = new_interCode(LAB);
		codes1->code->onlyop.op = label1;

		InterCodes codes2 = translate_Cond(Stmt->child->brother->brother, label2, label3);
		
		InterCodes codes3 = InterCodes_init();
		codes3->code = new_interCode(LAB);
		codes3->code->onlyop.op = label2;

		InterCodes codes4 = translate_Stmt(Stmt->child->brother->brother->brother->brother);

		InterCodes codes5 = InterCodes_init();
		codes5->code = new_interCode(GOTO);
		codes5->code->onlyop.op = label1;

		InterCodes codes6 = InterCodes_init();
		codes6->code = new_interCode(LAB);
		codes6->code->onlyop.op = label3;

		InterCodes_link(codes1,codes2);
		InterCodes_link(codes1,codes3);
		InterCodes_link(codes1,codes4);
		InterCodes_link(codes1,codes5);
		InterCodes_link(codes1,codes6);

		return codes1;

	}
	//IF LP Exp RP Stmt1 
	else if(Stmt->child->brother->brother->brother->brother->brother == NULL){
		Operand label1 = new_label();
		Operand label2 = new_label();
		
		InterCodes codes1 = translate_Cond(Stmt->child->brother->brother, label1, label2);
		
		InterCodes codes2 = InterCodes_init();
		codes2->code = new_interCode(LAB);
		codes2->code->onlyop.op = label1;

		InterCodes codes3 = translate_Stmt(Stmt->child->brother->brother->brother->brother);

		InterCodes codes4 = InterCodes_init();
		codes4->code = new_interCode(LAB);
		codes4->code->onlyop.op = label2;

		InterCodes_link(codes1,codes2);
		InterCodes_link(codes1,codes3);
		InterCodes_link(codes1,codes4);

		return codes1;
	}
	//IF LP Exp RP Stmt1 ELSE Stmt2 
	else{
		Operand	label1 = new_label();
	 	Operand	label2 = new_label();
		Operand label3 = new_label();

		InterCodes codes1 = translate_Cond(Stmt->child->brother->brother, label1, label2);

		InterCodes codes2 = InterCodes_init();
		codes2->code = new_interCode(LAB);
		codes2->code->onlyop.op = label1;

		InterCodes codes3 = translate_Stmt(Stmt->child->brother->brother->brother->brother);

		InterCodes codes4 = InterCodes_init();
		codes4->code = new_interCode(GOTO);
		codes4->code->onlyop.op = label3;

		InterCodes codes5 = InterCodes_init();
		codes5->code = new_interCode(LAB);
		codes5->code->onlyop.op = label2;

		InterCodes codes6 = translate_Stmt(Stmt->child->brother->brother->brother->brother->brother->brother);

		InterCodes codes7 = InterCodes_init();
		codes7->code = new_interCode(LAB);
		codes7->code->onlyop.op = label3;

		InterCodes_link(codes1,codes2);
		InterCodes_link(codes1,codes3);
		InterCodes_link(codes1,codes4);
		InterCodes_link(codes1,codes5);
		InterCodes_link(codes1,codes6);
		InterCodes_link(codes1,codes7);

		return codes1;
	}
	//else if(Stmt->child->brother-)
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
InterCodes translate_VarDec(node* VarDec){
	InterCodes code1 = InterCodes_init();
	if(strcmp(VarDec->child->name, "ID") == 0){			//ID
		FieldList p = Findname(VarDec->child->node_value);
		if(p->type->kind == Int || p->type->kind == Float){
			return NULL;
		}
		else if(p->type->kind == ARRAY || p->type->kind == STRUCTURE){
			int size = getSize(p->type);
			code1->code->assign.left->kind = VARIABLE;
			strcpy(code1->code->assign.left->name,VarDec->child->node_value);
			Operand temp = new_operand(1,size);
			code1->code->assign.right = temp;
			code1->code->kind = DEC;
		}
		return code1;
	}
	else								//ID LB INT RB
		translate_VarDec(VarDec->child);
}
InterCodes translate_Fundec(node* Fundec){
	node* ID = Fundec->child;
	InterCodes code1 = InterCodes_init();
	code1->code->kind = FUNC_I;
	code1->code->onlyop.op->kind = FUNC_op;
	strcpy(code1->code->onlyop.op->func,ID->node_value);
	if(strcmp(ID->brother->brother->name,"VarList") == 0){			//ID LP VarList RP
		FieldList p = Findname(ID->node_value);	
		FuncVar *q = p->type->func.brother;
		while(q != NULL){
			InterCodes code2 = InterCodes_init();
			code2->code->onlyop.op->kind = PARAM_op;
			strcpy(code1->code->onlyop.op->func,q->name);	
			InterCodes_link(code1, code2);
			q = q->next;
		}
		return code1;
	}
	else 			//ID LP RP
		return code1;
}
InterCodes translate_Args(node* Args,Operand *arg,int num){
	if(Args->child->brother == NULL){
		InterCodes code1;
		Operand op = new_temp();
		code1 = translate_Exp(Args->child, op);
		arg[num++] = op;
		return code1;
	}
	else{
		InterCodes code1;
		Operand op = new_temp();
		code1 = translate_Exp(Args->child, op);
		arg[num++] = op;
		InterCodes code2 = translate_Args(Args,arg,num);
		InterCodes_link(code1,code2);
		return code1;
	}
}
InterCodes translate_Struct(node *Exp,Operand place){
	InterCodes code1 = InterCodes_init();
	int size = 0;
	if(strcmp(Exp->child->child->name,"ID") == 0){		//ID1.ID2
		node *ID2 = Exp->child->brother->brother;
		node *ID1 = Exp->child;
		char typename[20];
		strcpy(typename,FindStruct(ID1->node_value,ID2->node_value));
		FieldList p = Findname(ID1->child->node_value);	
		p = p->brother;
		while(p!=NULL){
			if(strcmp(p->name,Exp->child->brother->brother->child->node_value) == 0)
				break;
			size = size + getSize(p->type);
			p = p->brother;
		}	
		Operand op1 = new_operand_name(ID1->child->node_value);
		Operand op2 = new_operand(1,size);
		code1->code->kind = ADDR;
		code1->code->binop.result = place;
		code1->code->binop.op1 = op1;
		code1->code->binop.op2 = op2;
		place->kind = ADDR_op;
		return code1;
	}
	else if(strcpy(Exp->child->child->name,"Exp") == 0){
		InterCodes code2 = InterCodes_init();
		node *ID1 = Exp->child;
		Operand t1 = new_temp();
		code1 = translate_Struct(Exp->child, t1);
		FieldList p = Findname(ID1->child->node_value);	
		p = p->brother;
		while(p!=NULL){
			if(strcmp(p->name,Exp->child->brother->brother->child->node_value) == 0)
				break;
			size = size + getSize(p->type);
			p = p->brother;
		}
		Operand op1 = new_operand_name(ID1->child->node_value);
		Operand op2 = new_operand(1,size);
		code2->code->kind = ADDR;
		code2->code->binop.result = place;
		code2->code->binop.op1 = op1;
		code2->code->binop.op2 = op2;
		InterCodes_link(code1,code2);
		place->kind = ADDR_op;
		return code1;
	}
}
InterCodes translate_Array(node *Exp,Operand place){
	InterCodes code1 = InterCodes_init();			
	FieldList p = Findname(Exp->child->child->node_value);
	int size =0;
	//Operand t ;
	if(strcpy(Exp->child->child->name,"ID") == 0){	//Exp[Exp]
		if(p->type->array.elem->kind == STRUCTURE)
			size = getSize(p->type->array.elem);
		else size = 4;
		Operand op1 = new_operand_name(Exp->child->child->node_value);
		InterCodes code2,code3,code4;
		Operand t1 = new_temp();
		code2 = translate_Exp(Exp->child->brother->brother,t1);			//翻译[]中的exp
		Operand t2 = new_temp();
		Operand c1 = new_operand(1,size);
		code3->code->kind = MUL;
		code3->code->binop.result = t2;
		code3->code->binop.op1 = t1;
		code3->code->binop.op2 = c1;
		code4->code->kind = ADDR;
		code4->code->binop.result = place;
		code4->code->binop.op1 = op1;
		code4->code->binop.op2 = t2;
		InterCodes_link(code1,code2);
		InterCodes_link(code1,code3);
		InterCodes_link(code1,code4);
		place->kind = ADDR_op;
		return code1;
	}
	else if(strcpy(Exp->child->child->name,"Exp") == 0)			//Exp[Exp][Exp]
	{
		if(p->type->array.elem->kind == STRUCTURE)
			size = getSize(p->type->array.elem);
		else size = 4;
		InterCodes code = InterCodes_init();
		Operand temp = new_temp();
		code = translate_Array(Exp->child,temp);
		Operand op1 = new_operand_name(Exp->child->child->node_value);
		InterCodes code2,code3,code4;
		Operand t1 = new_temp();
		code2 = translate_Exp(Exp->child->brother->brother,t1);			//翻译[]中的exp
		Operand t2 = new_temp();
		Operand c1 = new_operand(1,size);
		code3->code->kind = MUL;
		code3->code->binop.result = t2;
		code3->code->binop.op1 = t1;
		code3->code->binop.op2 = c1;
		code4->code->kind = ADDR;
		code4->code->binop.result = place;
		code4->code->binop.op1 = op1;
		code4->code->binop.op2 = t2;
		InterCodes_link(code1,code2);
		InterCodes_link(code1,code3);
		InterCodes_link(code1,code4);
		InterCodes_link(code1,code);
		place->kind = ADDR_op;
		return code1;
	}

}
void intercode_aly(node *p){		
	char name[20];
	strcpy(name,p->name);
	if(strcmp(name,"Def")==0){
	
	}
	else if(strcmp(name,"ExtDef")==0){

	}
	else if(strcmp(name,"Exp")==0){
		Operand t1 = new_temp();
		InterCodes expe = translate_Exp(p,t1);
		add_to_head(expe);
		if(p->brother != NULL)
			intercode_aly(p->brother);
		return;
	}
	else if(strcmp(name,"CompSt")==0){

	}
	else if(strcmp(name,"Args")==0){

	}
	else if(strcmp(name,"Stmt")==0){
		InterCodes codes = translate_Stmt(p);
		add_to_head(codes);
		if(p->brother != NULL)
			intercode_aly(p->brother);
		return;
	}

	if(p->child != NULL)
		intercode_aly(p->child);
	if(p->brother != NULL)
		intercode_aly(p->brother);
	return;
}

/*int op_assign(Operand op1,Operand op2){
	if(op1->kind != op2->kind)

}*/

Operand get_left(InterCodes codes){
	if(codes->code->kind == 0)
		return codes->code->assign.left;
	else
		return codes->code->binop.result;
}

void optimize(){
	InterCodes temp = intercodes_head->next;
	if(temp == NULL){
		printf("error at optimize\n");
		return;
	}
	while(temp->next != NULL){
		if((temp->code->kind == 0 || temp->code->kind == 1 || temp->code->kind == 2 || temp->code->kind == 3 || temp->code->kind == 4)&& (temp->next->code->kind == 0)){
			Operand left = get_left(temp);
			if(left == temp->next->code->assign.right){
				if(temp->code->kind == 0)
					temp->code->assign.left = temp->next->code->assign.left;
				else
					 temp->code->binop.result = temp->next->code->assign.left;

				InterCodes codes = temp->next;
				if(temp->next->next != NULL){
					temp->next->next->prev = temp;
				}
				temp->next = codes->next;
				free(codes);
			}
		}
		temp = temp->next;
	}
}

void printfile(node* p){
	head_init();
	intercode_aly(p);
	//optimize();
}

int getSize(Type p){
	int size = 0;
	if(p->kind == Int||p->kind == Float)
		size = size + 4;
	else if(p->kind == ARRAY){
		size = getSize(p->array.elem);
		size =  size * p->array.size;
	}
	else{
		FieldList q = p->structure;
		while(q!=NULL){
			size = size + getSize(q->type);
			q = q->brother;
		}
	}
	return size;
}

