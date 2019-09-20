// ARCH1718.stefano.notari.0000832003
#include "loopandfunction.h"

void label(FILE *fout,string line){
	string firstPart = malloc(max_length*sizeof(char));
	string secondPart = malloc(max_length*sizeof(char));
	nextSpace(line,firstPart,secondPart);
	fprintf(fout, "(%s)\n", firstPart);
}

void gotoL(FILE *fout,string line){
	string firstPart = malloc(max_length*sizeof(char));
	string secondPart = malloc(max_length*sizeof(char));
	nextSpace(line,firstPart,secondPart);
	fprintf(fout, "@%s\n", firstPart);
	fprintf(fout, "0;JMP\n");
}

void if_goto(FILE *fout,string line,int numberLine){
	string firstPart = malloc(max_length*sizeof(char));
	string secondPart = malloc(max_length*sizeof(char));
	nextSpace(line,firstPart,secondPart);
	popDregister(fout);
	fprintf(fout, "@%s\n", firstPart);
	fprintf(fout, "D;JNE\n");
}

void pushCallFunction(FILE *fout,string reg){
	fprintf(fout, "@%s\n", reg);
	fprintf(fout, "D=M\n");
	fprintf(fout, "@SP\n");
	fprintf(fout, "A=M\n");
	fprintf(fout, "M=D\n");
	fprintf(fout, "@SP\n");
	fprintf(fout, "M=M+1\n");
}

void callFunction(FILE *fout,string line,int numberLine){
	string functionName = malloc(max_length*sizeof(char));
	string numArgs = malloc(max_length*sizeof(char));
	nextSpace(line,functionName,numArgs);
	int l = strlen(numArgs);
	removeSpaces(numArgs,l);
	//PUSH return address
	fprintf(fout, "@returnFunction_%d\n", numberLine);
	fprintf(fout, "D=A\n");
	fprintf(fout, "@SP\n");
	fprintf(fout, "A=M\n");
	fprintf(fout, "M=D\n");
	fprintf(fout, "@SP\n");
	fprintf(fout, "M=M+1\n");
	//pushDregister(fout);
	//PUSH LCL
	pushCallFunction(fout,"LCL");
	//PUSH ARG
	pushCallFunction(fout,"ARG");
	//PUSH THIS
	pushCallFunction(fout,"THIS");
	//PUSH THAT
	pushCallFunction(fout,"THAT");
	//ARG = SP - n - 5
	int n = getInt(numArgs);
	fprintf(fout, "@SP\n");
	fprintf(fout, "D=M\n");
	fprintf(fout, "@5\n");
	fprintf(fout, "D=D-A\n");
	fprintf(fout, "@%d\n", n);
	fprintf(fout, "D=D-A\n");
	fprintf(fout, "@ARG\n");
	fprintf(fout, "M=D\n");
	//LCL = SP
	fprintf(fout, "@SP\n");
	fprintf(fout, "D=M\n");
	fprintf(fout, "@LCL\n");
	fprintf(fout, "M=D\n");
	//goto f
	fprintf(fout, "@%s\n", functionName);
	fprintf(fout, "0;JMP\n");
	//(return address)
	fprintf(fout, "(returnFunction_%d)\n", numberLine);
}

void function(FILE *fout,ptr_table head,string line,int numberLine){
	if(myStrStr(line,"Sys.init"))
		return;
	string functionName = malloc(256*sizeof(char));
	string numArgs = malloc(256*sizeof(char));
	nextSpace(line,functionName,numArgs);
	int l = strlen(numArgs);
	removeSpaces(numArgs,l);
	int numArguments = getInt(numArgs);
	fprintf(fout, "(%s)\n", functionName);
	int i;
	for(i = 0;i<numArguments;++i){
		push(fout,0);
	}
}

void preFrame(FILE *fout,string reg,int numberLine){
	//fprintf(fout, "@LCL\n");
	fprintf(fout, "@frame_%d\n",numberLine);
	fprintf(fout, "AM=M-1\n");
	fprintf(fout, "D=M\n");
	fprintf(fout, "@%s\n", reg);
	fprintf(fout, "M=D\n");
}

void functionReturn(FILE *fout,ptr_table head,int numberLine){
	fprintf(fout, "@LCL\n");
	fprintf(fout, "D=M\n");
	//FRAME = LCL
	fprintf(fout, "@frame_%d\n",numberLine);
	fprintf(fout, "M=D\n");
	//RET = *(FRAME-5)
	fprintf(fout, "@5\n");
	fprintf(fout, "D=D-A\n");
	fprintf(fout, "A=D\n");
	fprintf(fout, "D=M\n");
	fprintf(fout, "@ret_%d\n",numberLine);
	fprintf(fout, "M=D\n");
	//*ARG = pop
	fprintf(fout, "@SP\n");
	fprintf(fout, "AM=M-1\n");
	fprintf(fout, "D=M\n");
	fprintf(fout, "@ARG\n");
	fprintf(fout, "A=M\n");
	fprintf(fout, "M=D\n");
	//SP = ARG+1
	fprintf(fout, "@ARG\n");
	fprintf(fout, "D=M+1\n");
	fprintf(fout, "@SP\n");
	fprintf(fout, "M=D\n");
	//THAT = *(FRAME-1)
	preFrame(fout,"THAT",numberLine);
	// THIS = *(FRAME-2)
	preFrame(fout,"THIS",numberLine);
	//ARG = *(FRAME-3)
	preFrame(fout,"ARG",numberLine);
	//LCL = *(FRAME-4)
	preFrame(fout,"LCL",numberLine);
	// ret
	fprintf(fout, "@ret_%d\n", numberLine);
	fprintf(fout, "A=M\n");
	fprintf(fout, "0;JMP\n");
}