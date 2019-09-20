// ARCH1718.stefano.notari.0000832003
#include <stdio.h>
#include "constants.h"
#include "symboltable.h"
#include "stack.h"
#include "functionlib.h"

int getPointerAddress(string line,ptr_table head);
void getPointerValue(FILE *fout,int num);
void popPointer(FILE *fout,string line,ptr_table head);
void pushPointer(FILE *fout,string line,ptr_table head);
void popThisOrThat(FILE *fout,int num,int thisOrThatBit);
void pushThisOrThat(FILE *fout,int num,int thisOrThatBit);