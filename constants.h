// ARCH1718.stefano.notari.0000832003
#ifndef CONSTANTS_H
#define CONSTANTS_H
typedef char *string;
typedef struct symbolAddressTable{
	string symbol;
	int value;
	struct symbolAddressTable *next;
} symbolAddressTable_t;

typedef symbolAddressTable_t *ptr_table;
#endif
extern const int max_length;
extern const int iSP;
extern const int staticSegment;
extern const int localSegment;
extern const int startTemp;
extern const int numberArray[10];
extern const int specialSymbolLength;
extern const char specialSymbol[4];