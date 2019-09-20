// ARCH1718.stefano.notari.0000832003
#include "stack.h"

void incSP(FILE *fout){
	fprintf(fout, "@R0\n");
	fprintf(fout, "AM=M+1\n");
}

void getSP(FILE *fout){
	fprintf(fout, "@R0\n");
	fprintf(fout, "AM=M\n");
}

void decSP(FILE *fout){
	fprintf(fout, "@R0\n");
	fprintf(fout, "AM=M-1\n");
}

void push(FILE *fout,int value){
	if(value != 0){
		fprintf(fout, "@%d\n", value);
		fprintf(fout, "D=A\n");
		getSP(fout);
		fprintf(fout, "M=D\n");
	} else{
		getSP(fout);
		fprintf(fout, "M=0\n");
	}
	incSP(fout);
}

void pushDregister(FILE *fout){
	getSP(fout);
	fprintf(fout, "M=D\n");
	incSP(fout);
}

void popDregister(FILE *fout){
	decSP(fout);
	fprintf(fout, "D=M\n");
}

void pop(FILE *fout,int dest){
	decSP(fout);
	fprintf(fout, "D=M\n");
	fprintf(fout, "@%d\n", dest);
	fprintf(fout, "M=D\n");
}