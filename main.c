// ARCH1718.stefano.notari.0000832003
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"
#include "constants.h"
#include "stack.h"
#include "hackoperations.h"
#include "staticstack.h"
#include "pointerstack.h"
#include "functionlib.h"
#include "argtemplocalregister.h"
#include "loopandfunction.h"

typedef char *string;
string fileInputName;
string ext = "asm";
string fileName;

int getEndIndex(string line,int start){
	int end = start;
	bool finishString = false;
	while(!finishString){
		if(!(isDigit(line[end]) || isAlpha(line[end]) || line[end] == '_'))
			finishString = true;
		else
			end++;
	}
	return end;
}

void pushInstruction(FILE *fout,string line,ptr_table head){
	string firstPart = malloc(max_length*sizeof(char));
	string secondPart = malloc(max_length*sizeof(char));
	nextSpace(line,firstPart,secondPart);
	int len = strlen(secondPart);
	removeSpaces(secondPart,len);
	int n = getInt(secondPart);
	if(myStrStr(firstPart,"constant")) push(fout,n);
	else if(myStrStr(firstPart,"static")) staticPush(fout,n,fileName);
	else if(myStrStr(firstPart,"pointer")) pushPointer(fout,secondPart,head);
	else if(myStrStr(firstPart,"this")) pushThisOrThat(fout,n,3);
	else if(myStrStr(firstPart,"that")) pushThisOrThat(fout,n,4);
	else if(myStrStr(firstPart,"local")) pushLocalOrArgument(fout,n,head,true);
	else if(myStrStr(firstPart,"argument")) pushLocalOrArgument(fout,n,head,false);
	else if(myStrStr(firstPart,"temp")) pushTemp(fout,n,head);
}

void popInstruction(FILE *fout,string line,ptr_table head){
	string firstPart = malloc(max_length*sizeof(char));
	string secondPart = malloc(max_length*sizeof(char));
	nextSpace(line,firstPart,secondPart);
	int len = strlen(secondPart);
	removeSpaces(secondPart,len);
	int n = getInt(secondPart);
	if(myStrStr(firstPart,"static")) staticPop(fout,n,fileName);
	else if(myStrStr(firstPart,"pointer")) popPointer(fout,secondPart,head);
	else if(myStrStr(firstPart,"this")) popThisOrThat(fout,n,3);
	else if(myStrStr(firstPart,"that")) popThisOrThat(fout,n,4);
	else if(myStrStr(firstPart,"local")) popLocalOrArgument(fout,n,head,true);
	else if(myStrStr(firstPart,"argument")) popLocalOrArgument(fout,n,head,false);
	else if(myStrStr(firstPart,"temp")) popTemp(fout,n,head);
}

void arithmeticOperations(FILE *fout,string line,int numberLine){
	if(myStrStr(line,"add")) add(fout);
	else if(myStrStr(line,"sub")) sub(fout);
	else if(myStrStr(line,"neg")) neg(fout);
}

void logicOperations(FILE *fout,string line){
	if(myStrStr(line,"and")) and(fout);
	else if(myStrStr(line,"or")) or(fout);
	else if(myStrStr(line,"not")) not(fout);
}

void jumpCondition(FILE *fout,string line,int numberLine){
	if(myStrStr(line,"eq")) eq(fout,numberLine);
	else if(myStrStr(line,"lt")) lt(fout,numberLine);
	else if(myStrStr(line,"gt")) gt(fout,numberLine);
}

int getPointPosition(string name){
	int i = 0;
	bool found = false;
	while(!found && name[i] != '\0'){
		if(name[i] == '.' && name[i+1] == 'v' && name[i+2] == 'm')
			found = true;
		i++;
	}
	if(found)
		return i;
	else
		return -1;
}

int getLastSlashPosition(string name){
	int i = 0;
	int countSlash = 0;
	if(isAlpha(name[i]))
		return i;
	bool found = false;
	int numSlash = 0;
	int l = strlen(name);
	int j;
	for(j = 0; j < l;j++)
		if(name[j] == '\\' || name[j] == '/')
			numSlash++;
	while(countSlash < numSlash){
		if(name[i] == '\\' || name[i] == '/')
			countSlash++;
		i++;
	}

	return i++;

}

void init(FILE *fout,int numberLine){
	//SP = 256
	fprintf(fout, "@256\n");
	fprintf(fout, "D=A\n");
	fprintf(fout, "@SP\n");
	fprintf(fout, "M=D\n");
	//LCL = 300
	/*fprintf(fout, "@300\n");
	fprintf(fout, "D=A\n");
	fprintf(fout, "@LCL\n");
	fprintf(fout, "M=D\n");*/
	//ARG = 400
	/*fprintf(fout, "@400\n");
	fprintf(fout, "D=A\n");
	fprintf(fout, "@ARG\n");
	fprintf(fout, "M=D\n");*/
	//THIS = 3000
	/*fprintf(fout, "@3000\n");
	fprintf(fout, "D=A\n");
	fprintf(fout, "@THIS\n");
	fprintf(fout, "M=D\n");*/
	//THAT = 3010
	/*fprintf(fout, "@3010\n");
	fprintf(fout, "D=A\n");
	fprintf(fout, "@THAT\n");
	fprintf(fout, "M=D\n");*/
	//callFunction(fout,"callSys.init0",numberLine);
	//fprintf(fout, "0;JMP\n");
}

int main(int argc,char *argv[]){
	if(argc == 1){
		printf("Error, no Arguments!");
		return 1;
	}

	if(argc > 2){
		printf("Error, too much Arguments!");
		return 1;
	}

	fileInputName = argv[1];

	int numberLine = 0;

	FILE *fin;
	fin = fopen(fileInputName,"r");

	string output = (char *)malloc (max_length * sizeof (char));
	fileName = (char *)malloc (max_length * sizeof (char));
	int p = getPointPosition(fileInputName);
	int s = getLastSlashPosition(fileInputName);
	if(p != -1){
		myMemcpy(fileName,&fileInputName[s],10);
		myMemcpy(output,&fileInputName[0],p);
	}
	output[p] = '\0';
	fileName[10] = '\0';
	myStrcpyat(output,ext);

	FILE *fout;
	fout = fopen(output,"w");

	ptr_table head = NULL;
	head = insertDefaultSymbol(head);

	char str [max_length];
	size_t len;
	int read;
	string firstPart = malloc(max_length*sizeof(char));
	string lastPart = malloc(max_length*sizeof(char));

	init(fout,numberLine);
	while(fgets(str,max_length,fin) != NULL){
		fprintf(fout, "\t//%s", str);

		firstPart = malloc(max_length*sizeof(char));
		nextSpace(str,firstPart,lastPart);
		if(firstPart[0] != '/' && firstPart[1] != '/' && (isDigit(firstPart[0]) || isAlpha(firstPart[0]))){
			if(myStrStr(firstPart,"push")) pushInstruction(fout,lastPart,head);
			else if(myStrStr(firstPart,"pop")) popInstruction(fout,lastPart,head);
			else if(myStrStr(firstPart,"label")) label(fout,lastPart);
			else if(myStrStr(firstPart,"if")) if_goto(fout,lastPart,numberLine);
			else if(myStrStr(firstPart,"goto")) gotoL(fout,lastPart);
			else if(myStrStr(firstPart,"function")) function(fout,head,lastPart,numberLine);
			else if(myStrStr(firstPart,"return")) functionReturn(fout,head,numberLine);
			else if(myStrStr(firstPart,"call")) callFunction(fout,lastPart,numberLine);
			arithmeticOperations(fout,firstPart,numberLine);
			logicOperations(fout,firstPart);
			jumpCondition(fout,firstPart,numberLine);
			numberLine++;
		}
	}

	return 0;

}