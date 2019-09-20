// ARCH1718.stefano.notari.0000832003
#include "staticstack.h"
#include <stdlib.h>
#include "string.h"

void staticPop(FILE *fout,int pos,string fileName){
	popDregister(fout);
	fprintf(fout, "@%s%d\n", fileName,pos);
	fprintf(fout, "M=D\n");
}

void getStaticValue(FILE *fout,int pos,string fileName){
	fprintf(fout, "@%s%d\n", fileName,pos);
	fprintf(fout, "D=M\n");
}

void staticPush(FILE *fout,int pos,string fileName){
	getStaticValue(fout,pos,fileName);
	pushDregister(fout);
}