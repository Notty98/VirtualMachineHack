// ARCH1718.stefano.notari.0000832003
#include "argtemplocalregister.h"

int getLocalOrArgumentAddress(ptr_table head,bool local){
	int registerAddress = 0;
	if(local)
		registerAddress = getSymbolValue(head,"LCL");
	else
		registerAddress = getSymbolValue(head,"ARG");
	return registerAddress;
}

void setLocalArgumentAddress(FILE *fout,ptr_table head,bool local){
	int reg = getLocalOrArgumentAddress(head,local);
	fprintf(fout, "@%d\n", reg);
	fprintf(fout, "M=D\n");
}

void getLocalOrArgumentValue(FILE *fout,ptr_table head,bool local){
	int num = getLocalOrArgumentAddress(head,local);
	fprintf(fout, "@%d\n", num);
	fprintf(fout, "D=M\n");
}

void popLocalOrArgument(FILE *fout,int num,ptr_table head,bool local){
	popDregister(fout);
	int localOrArgument = getLocalOrArgumentAddress(head,local);
	fprintf(fout, "@%d\n", localOrArgument);
	fprintf(fout, "A=M\n");
	int i;
	for(i = 0;i<num;i++)
		fprintf(fout, "A=A+1\n");
	fprintf(fout, "M=D\n");
}

void pushLocalOrArgument(FILE *fout,int num,ptr_table head,bool local){
	int localOrArgument = getLocalOrArgumentAddress(head,local);
	fprintf(fout, "@%d\n", localOrArgument);
	fprintf(fout, "A=M\n");
	int i;
	for(i = 0;i<num;i++)
		fprintf(fout, "A=A+1\n");
	fprintf(fout, "D=M\n");
	pushDregister(fout);
}

void popTemp(FILE *fout,int num,ptr_table head){
	popDregister(fout);
	int tempRegister = startTemp + num;
	fprintf(fout, "@%d\n",tempRegister);
	fprintf(fout, "M=D\n");
}

void popTempRegister(FILE *fout,int num){
	int tempRegister = startTemp + num;
	fprintf(fout, "@%d\n",tempRegister);
	fprintf(fout, "D=M\n");
}

void pushTemp(FILE *fout,int num,ptr_table head){
	int tempRegister = startTemp + num;
	fprintf(fout, "@%d\n",tempRegister);
	fprintf(fout, "D=M\n");
	pushDregister(fout);
}