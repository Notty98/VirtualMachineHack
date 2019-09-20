// ARCH1718.stefano.notari.0000832003
#include "constants.h"
#include "functionlib.h"
#include "stack.h"

void label(FILE *fout,string line);
void gotoL(FILE *fout,string line);
void if_goto(FILE *fout,string line,int numberLine);
void pushCallFunction(FILE *fout,string reg);
void callFunction(FILE *fout,string line,int numberLine);
void function(FILE *fout,ptr_table head,string line,int numberLine);
void preFrame(FILE *fout,string reg,int numberLine);
void functionReturn(FILE *fout,ptr_table head,int numberLine);