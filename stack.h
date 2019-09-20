// ARCH1718.stefano.notari.0000832003
#include <stdio.h>

void incSP(FILE *fout);
void getSP(FILE *fout);
void decSP(FILE *fout);
void push(FILE *fout,int value);
void pushDregister(FILE *fout);
void popDregister(FILE *fout);
void pop(FILE *fout,int dest);