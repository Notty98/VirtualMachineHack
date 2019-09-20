// ARCH1718.stefano.notari.0000832003
#include "symboltable.h"
#include "stack.h"
#include <stdio.h>

int getLocalOrArgumentAddress(ptr_table head,bool local);
void getLocalOrArgumentValue(FILE *fout,ptr_table head,bool local);
void popLocalOrArgument(FILE *fout,int num,ptr_table head,bool local);
void pushLocalOrArgument(FILE *fout,int num,ptr_table head,bool local);
void popTemp(FILE *fout,int num,ptr_table head);
void pushTemp(FILE *fout,int num,ptr_table head);
void setLocalArgumentAddress(FILE *fout,ptr_table head,bool local);