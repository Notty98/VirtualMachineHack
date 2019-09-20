# ARCH1718.stefano.notari.0000832003
VMtranslator: main.o symboltable.o constants.o stack.o hackoperations.o staticstack.o pointerstack.o functionlib.o argtemplocalregister.o loopandfunction.o
	gcc -o VMtranslator main.o symboltable.o constants.o stack.o hackoperations.o staticstack.o pointerstack.o functionlib.o argtemplocalregister.o loopandfunction.o

main.o: main.o symboltable.o constants.o stack.o hackoperations.o argtemplocalregister.o
	gcc -c main.c

functionlib.o: functionlib.c functionlib.h constants.o
	gcc -c functionlib.c

symboltable.o: symboltable.c symboltable.h constants.o functionlib.o
	gcc -c symboltable.c

constants.o: constants.c constants.h
	gcc -c constants.c

hackoperations.o: hackoperations.c hackoperations.h stack.o
	gcc -c hackoperations.c

stack.o: stack.c stack.h
	gcc -c stack.c

staticstack.o: staticstack.c staticstack.h stack.o constants.o
	gcc -c staticstack.c

pointerstack.o: pointerstack.c pointerstack.h symboltable.o stack.o constants.o
	gcc -c pointerstack.c

argtemplocalregister.o: argtemplocalregister.c argtemplocalregister.h stack.o symboltable.o
	gcc -c argtemplocalregister.c

loopandfunction.o: loopandfunction.c loopandfunction.h constants.o functionlib.o stack.o
	gcc -c loopandfunction.c

clean: 
	rm *.o VMtranslator