// ARCH1718.stefano.notari.0000832003
#include "hackoperations.h"

void add(FILE *fout){
	decSP(fout);
	getSP(fout);
	fprintf(fout, "D=M\n");
	decSP(fout);
	fprintf(fout, "M=D+M\n");
	incSP(fout);
}

void sub(FILE *fout){
	decSP(fout);
	getSP(fout);
	fprintf(fout, "D=M\n");
	decSP(fout);
	fprintf(fout, "M=M-D\n");
	incSP(fout);
}

void eq(FILE *fout,int numberLine){
	sub(fout);
	decSP(fout);
	getSP(fout);
	fprintf(fout, "D=M\n");
	fprintf(fout, "M=-1\n");
	fprintf(fout, "@EQ%d\n", numberLine);
	fprintf(fout, "D;JEQ\n");
	getSP(fout);
	fprintf(fout, "M=0\n");
	fprintf(fout, "(EQ%d)\n", numberLine);
	incSP(fout);
}

void lt(FILE *fout,int numberLine){
	sub(fout);
	decSP(fout);
	getSP(fout);
	fprintf(fout, "D=M\n");
	fprintf(fout, "M=-1\n");
	fprintf(fout, "@LT%d\n", numberLine);
	fprintf(fout, "D;JLT\n");
	getSP(fout);
	fprintf(fout, "M=0\n");
	fprintf(fout, "(LT%d)\n", numberLine);
	incSP(fout);
}

void gt(FILE *fout,int numberLine){
	sub(fout);
	decSP(fout);
	getSP(fout);
	fprintf(fout, "D=M\n");
	fprintf(fout, "M=-1\n");
	fprintf(fout, "@GT%d\n", numberLine);
	fprintf(fout, "D;JGT\n");
	getSP(fout);
	fprintf(fout, "M=0\n");
	fprintf(fout, "(GT%d)\n", numberLine);
	incSP(fout);
}

void neg(FILE *fout){
	decSP(fout);
	getSP(fout);
	fprintf(fout, "M=-M\n");
	incSP(fout);
}

void and(FILE *fout){
	decSP(fout);
	getSP(fout);
	fprintf(fout, "D=M\n");
	decSP(fout);
	getSP(fout);
	fprintf(fout, "M=M&D\n");
	incSP(fout);
}

void or(FILE *fout){
	decSP(fout);
	getSP(fout);
	fprintf(fout, "D=M\n");
	decSP(fout);
	getSP(fout);
	fprintf(fout, "M=M|D\n");
	incSP(fout);
}

void not(FILE *fout){
	decSP(fout);
	getSP(fout);
	fprintf(fout, "M=!M\n");
	incSP(fout);
}