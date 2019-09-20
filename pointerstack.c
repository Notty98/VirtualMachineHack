// ARCH1718.stefano.notari.0000832003
#include "pointerstack.h"

int getPointerAddress(string line,ptr_table head){
	int registerAddress;
	int num = getInt(line);
	if(num == 0)
		registerAddress = getSymbolValue(head,"THIS");
	else
		registerAddress = getSymbolValue(head,"THAT");
	return registerAddress;
}

void getPointerValue(FILE *fout,int num){
	fprintf(fout, "@%d\n", num);
	fprintf(fout, "D=M\n");
}

void popPointer(FILE *fout,string line,ptr_table head){
	int n = getPointerAddress(line,head);
	pop(fout,n);
}

void pushPointer(FILE *fout,string line,ptr_table head){
	int n = getPointerAddress(line,head);
	getPointerValue(fout,n);
	pushDregister(fout);
}

void popThisOrThat(FILE *fout,int num,int thisOrThatBit){
	popDregister(fout);
	fprintf(fout, "@%d\n", thisOrThatBit);
	fprintf(fout, "A=M\n");
	int i;
	for(i = 0;i<num;i++)
		fprintf(fout, "A=A+1\n");
	fprintf(fout, "M=D\n");
}

void pushThisOrThat(FILE *fout,int num,int thisOrThatBit){
	fprintf(fout, "@%d\n", thisOrThatBit);
	fprintf(fout, "A=M\n");
	int i;
	for(i = 0;i<num;i++)
		fprintf(fout, "A=A+1\n");
	fprintf(fout, "D=M\n");
	pushDregister(fout);
}