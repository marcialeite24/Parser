
OBJS=scanner.o parser.o TP1.o TP1main.o
INTERM=scanner.c parser.c parser.h
PROGRAM=./TP1main
CFLAGS=-g

all: $(PROGRAM)

scanner.c: scanner.flex parser.h
	flex -o scanner.c scanner.flex

parser.c parser.h: parser.bison
	bison --defines=parser.h -o parser.c parser.bison

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS)
clean:
	rm -f $(PROGRAM) $(OBJS) $(INTERM)

test: $(PROGRAM)
	$(PROGRAM) example1.txt
	$(PROGRAM) example2.txt
	$(PROGRAM) example3.txt
	$(PROGRAM) example4.txt
