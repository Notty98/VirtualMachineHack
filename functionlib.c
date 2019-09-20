// ARCH1718.stefano.notari.0000832003
#include "functionlib.h"

void removeSpaces(char* line,int length){
  char* i = line;
  char* j = line;
  int itr = 0;
  while(*j != 0 && itr < length){
    *i = *j++;
    if(*i != ' ')
      i++;
  	itr++;
  }
  *i = 0;
}

void myMemcpy(void *dest, void *src, size_t n){
   char *csrc = (char *)src;
   char *cdest = (char *)dest;

   int i;
   for (i=0; i<n; i++)
       cdest[i] = csrc[i];
}

bool isDigit(const char c){
	bool digit = false;
	int i = 0;
	while(!digit && i < 10){
		char n = numberArray[i]+'0';
		if(n == c)
			digit = true;
		i++;
	}
	return digit;
}

bool isAlpha(const char c){
	int asciiCode = (int) c;
	bool alpha = false;
	if((asciiCode>= 65 && asciiCode <=90) || (asciiCode >=97 && asciiCode <= 122))
		alpha = true;
	return alpha;

}

bool isSpecialSymbol(const char c){
	bool special = false;
	int i = 0;
	while(i < specialSymbolLength && !special){
		if(specialSymbol[i] == c)
			special = true;
		i++;
	}
	return special;
}

int getInt(string line){
	int startIndex = 0;
	bool found = false;
	while((isDigit(line[startIndex]) || isAlpha(line[startIndex]) || isSpecialSymbol(line[startIndex])) && !found){
		if(isDigit(line[startIndex]))
			found = true;
		else
			startIndex++;
	}
	char *start = &line[startIndex];
	int finishIndex = startIndex;

	while(isdigit(line[finishIndex]))
		finishIndex++;

	char *end = &line[finishIndex];

	string value = malloc(sizeof(char)*(end-start+1));
	myMemcpy(value, start, end - start);
	int num = atoi(value);

	return num;
}

int myStrCmp(const char *string1,const char *string2 ){
    while(*string1){
      if(*string1 != *string2)
        break;
      string1++;
      string2++;
    }
    return *(const unsigned char*)string1 - *(const unsigned char*)string2;
}

void nextSpace(string line,string firstPart,string lastPart){
	int startIndex = 0;
	while(line[startIndex] == ' ')
		startIndex++;
	int endIndex = startIndex;
	while(line[endIndex] != ' ' && line[endIndex] != '/' && line[endIndex+1] != '/' && (isDigit(line[endIndex]) || isAlpha(line[endIndex]) || isSpecialSymbol(line[endIndex])))
		endIndex++;
	string next;
	if(startIndex != endIndex){
		char* start = &line[startIndex];
		char* end = &line[endIndex];
		next = malloc(sizeof(char)*(end-start+1));
		string value = malloc(sizeof(char)*(end-start+1));
		myMemcpy(next,start,end-start);
		next[end-start] = '\0';
	} else{
		next = malloc(sizeof(char)*(1));
		next[0] = '\0';
	}
	strcpy(firstPart,next);
	int l = strlen(line);
	char* firstChar = &line[endIndex];
	char* lastChar = &line[l];
	string value = malloc(sizeof(char)*(lastChar-firstChar+1));
	string temp = malloc(sizeof(char)*(lastChar-firstChar+1));
	myMemcpy(temp,firstChar,lastChar-firstChar);
	temp[lastChar-firstChar] = '\0';
	strcpy(lastPart,temp);
}

bool myStrStr(const char *str,const char *sub){
	bool found = false;
	int length_str = strlen(str);
	int length_sub = strlen(sub);

	int j = 0;
	int i = 0;
	while(!found && i < length_str){
		if(str[i] == sub[j])
			j++;
		else
			j = 0;
		if(j == length_sub)
			found = true;
		i++;
	}

	return found;

}

void myStrcpyat(string to,string append){
	int len = strlen(append);
	int lenTo = strlen(to);
	char *start = &append[0];
	char *end = &append[len];
	myMemcpy(&to[lenTo],start,end-start);
	to[lenTo+end-start] = '\0';
}