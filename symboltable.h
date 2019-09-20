// ARCH1718.stefano.notari.0000832003
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "functionlib.h"

ptr_table addSymbol(ptr_table head,string symbol,int value);

void printSymbolTable(ptr_table head);

bool existSymbol(ptr_table head,string symbol);

int getSymbolValue(ptr_table head,string symbol);

ptr_table insertDefaultSymbol(ptr_table head);