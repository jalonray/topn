uname := $(shell sh -c 'uname -s 2>/dev/null || echo not')

CXX = g++
CC = gcc

CFLAGS = -std=c99 -pedantic -Wall -W -Wdeprecated-declarations  $(PROF)
CXXFLAGS = -Wno-deprecated -Wall -W $(PROF)
LDFLAGS = -lm -lpthread -lssl -lcrypto

DEBUG?=-g -ggdb

CCCOLOR="\033[34m"
LINKCOLOR="\033[34;1m"
SRCCOLOR="\033[33m"
BINCOLOR="\033[37;1m"
MAKECOLOR="\033[32;1m"
ENDCOLOR="\033[0m"

QUIET_CXX = @printf '    %b %b\n' $(CCCOLOR)CXX$(ENDCOLOR) $(SRCCOLOR)$@$(ENDCOLOR);
QUIET_CC = @printf '    %b %b\n' $(CCCOLOR)CC$(ENDCOLOR) $(SRCCOLOR)$@$(ENDCOLOR);
QUIET_LINK = @printf '    %b %b\n' $(LINKCOLOR)LINK$(ENDCOLOR) $(BINCOLOR)$@$(ENDCOLOR);

PRGNAME = test
OBJS = util.o heap.o test.o heap_topn.o simple_topn.o


all: $(PRGNAME)

util.o: util.c
heap.o: heap.c
test.o: test.c
heap_topn.o: heap_topn.c
simple_topn.o: simple_topn.c

$(PRGNAME):$(OBJS) $(DEPS) 
	$(QUIET_LINK)$(CXX) -o $(PRGNAME)  $(OBJS) $(LDFLAGS)

%.o: %.cc
	$(QUIET_CXX)$(CXX) -c $(CXXFLAGS) $(DEBUG) $<

%.o: %.c
	$(QUIET_CC)$(CC) -c $(CFLAGS) $(DEBUG) $<

clean:
	rm -f $(PRGNAME) *.o
	rm test
