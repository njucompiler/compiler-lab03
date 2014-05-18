
#include "intercode.h"
#include "node.h"


int var_no;

void var_no_init(){
	var_no = 1;
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
	return temp;
}

Operand translate_Exp(node* exp,char* place){
	//-------------------------------------------------Exp ASSIGNOP Exp
	if(exp->exp_type == 7){
		char t = new_temp();		
		t_no = var_no;
		var_no++;
		InterCode code1 = translate_Exp(exp->child->brother->brother,t);
		InterCode code2 = new_interCode(0);
		code2.assign.left = new_operand_name(exp->child->node_value);
		code2.assign.right = new_operand(0,t_no);

		InterCode code3 = new_interCode(0);
		code3.assign.left = new_operand(3,t_no);
		code3.assign.right = new_operand_name(exp->child->node_value);
		code1.next = code2;
		code2->next = code3;
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
		
	}

	//-------------------------------------------------Exp MINUS Exp
	else if(exp->exp_type == 12){
		
	}

	//--------------------------------------------------Exp STAR Exp
	else if(exp->exp_type == 13){
		
	}

	//--------------------------------------------------Exp DIV Exp
	else if(exp->exp_type == 14){	
		
	}

	//--------------------------------------------------LP Exp RP
	else if(exp->exp_type == 15){
		
	}

	//--------------------------------------------------MINUS Exp
	else if(exp->exp_type == 16){
		
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
		InterCode code = new_interCode(0);
		code.assign.right = new_operand(1,exp->node_int);
		code.assign.left = new_operand(3,var_no);
		var_no++;
		return code;
	}

	//--------------------------------------------------FLOAT
	else if(exp->exp_type == 24){
		
	}
} 

