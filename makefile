OBJS = main.o hashtable.o preprocessing.o date.o list.o avl.o comands.o commandfunctions.o
EXEC = diseaseMonitor
GCCC = gcc -c
GCCO = gcc -o
LIBS = -lm

$(EXEC): $(OBJS)
	$(GCCO) $(EXEC) $(OBJS) $(LIBS)

main.o: main.c
	$(GCCC) main.c

hashtable.o: hashtable.c
	$(GCCC) hashtable.c

preprocessing.o: preprocessing.c
	$(GCCC) preprocessing.c

comands.o: comands.c
	$(GCCC) comands.c	

commandfunctions.o: commandfunctions.c
	$(GCCC) commandfunctions.c	

date.o: date.c
	$(GCCC) date.c	

list.o: list.c
	$(GCCC) list.c	

avl.o: avl.c
	$(GCCC) avl.c


clean:
	rm -rf $(OBJS) $(EXEC)
