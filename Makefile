CC=gcc
CFLAGS=-Wall -O0 -g
LIBS=-lcheck -lm -lpthread -lrt

SRCDIR=src
TESTDIR=tests

all: librpn.a

librpn.a: $(SRCDIR)/rpn.o $(SRCDIR)/operator_stack.o
	ar rcs $@ $^

$(SRCDIR)/rpn.o: $(SRCDIR)/rpn.c $(SRCDIR)/rpn.h $(SRCDIR)/operator_stack.h
	gcc $(CFLAGS) -c $(SRCDIR)/rpn.c -o $@

$(SRCDIR)/operator_stack.o: $(SRCDIR)/operator_stack.c $(SRCDIR)/operator_stack.h
	gcc $(CFLAGS) -c $(SRCDIR)/operator_stack.c -o $@

$(TESTDIR)/check_rpn.o: $(TESTDIR)/check_rpn.c $(SRCDIR)/rpn.h
	gcc $(CFLAGS) -c $(TESTDIR)/check_rpn.c -o $@

test: rpn-test
	./rpn-test

rpn-test: librpn.a $(TESTDIR)/check_rpn.o
	gcc -o rpn-test $(TESTDIR)/check_rpn.o $(SRCDIR)/rpn.o $(SRCDIR)/operator_stack.o $(LIBS)

clean:
	$(RM) $(SRCDIR)/*.o $(TESTDIR)/*.o rpn rpn-test librpn.a
