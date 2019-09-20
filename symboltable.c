// ARCH1718.stefano.notari.0000832003
#include "symboltable.h"

ptr_table addSymbol(ptr_table head,string symbol,int value){
	if(head == NULL){
		head = malloc(sizeof(symbolAddressTable_t));
		head->symbol = (char*)malloc(max_length*sizeof(char));
		head->symbol = symbol;
		head->value = value;
		head->next = NULL;
	}else{
		ptr_table itr = head;
		while(itr->next != NULL)
			itr = itr->next;
		itr->next = malloc(sizeof(symbolAddressTable_t));
		itr = itr->next;
		itr->symbol = (char*)malloc(max_length*sizeof(char));
		itr->symbol = symbol;
		itr->value = value;
		itr->next = NULL;
	}
	return head;
}

void printSymbolTable(ptr_table head){
	ptr_table itr = malloc(sizeof(ptr_table));
	itr = head;

	if(itr != NULL)
		do{
			string symbol = itr->symbol;
			int value = itr->value;
			printf("%s : %d\n", symbol,value);
			itr = itr->next;
		}while(itr != NULL);

}

bool existSymbol(ptr_table head,string symbol){
	ptr_table itr = malloc(sizeof(ptr_table));
	itr = head;
	bool found = false;
	if(itr != NULL)
		do{
			string tableSymbol = itr->symbol;
			if(myStrCmp(tableSymbol, symbol) == 0)
				found = true;
			itr = itr->next;
		}while(itr != NULL && !found);
	return found;
}

int getSymbolValue(ptr_table head,string symbol){
	ptr_table itr = malloc(sizeof(ptr_table));
	itr = head;
	bool found = false;
	int v = -1;
	if(itr != NULL)
		do{
			if(myStrCmp(itr->symbol, symbol) == 0){
				found = true;
				v = itr->value;
			}
			itr = itr->next;
		}while(itr != NULL && !found);
	return v;
}

ptr_table insertDefaultSymbol(ptr_table head){
	head = addSymbol(head,"R0", 0);
	head = addSymbol(head,"R1", 1);
	head = addSymbol(head,"R2", 2);
	head = addSymbol(head,"R3", 3);
	head = addSymbol(head,"R4", 4);
	head = addSymbol(head,"R5", 5);
	head = addSymbol(head,"R6", 6);
	head = addSymbol(head,"R7", 7);
	head = addSymbol(head,"R8", 8);
	head = addSymbol(head,"R9", 9);
	head = addSymbol(head,"R10", 10);
	head = addSymbol(head,"R11", 11);
	head = addSymbol(head,"R12", 12);
	head = addSymbol(head,"R13", 13);
	head = addSymbol(head,"R14", 14);
	head = addSymbol(head,"R15", 15);
	head = addSymbol(head,"SCREEN",16384);
	head = addSymbol(head,"KBD",24576);
	head = addSymbol(head,"SP",0);
	head = addSymbol(head,"LCL", 1);
	head = addSymbol(head,"ARG", 2);
	head = addSymbol(head,"THIS", 3);
	head = addSymbol(head,"THAT", 4);
	return head;
}