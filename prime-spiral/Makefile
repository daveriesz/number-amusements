
PROGRAM = prime-spiral

CSOURCES = prime-spiral.c
COBJECTS = $(CSOURCES:.c=.o)

LDFLAGS = -lpng

all: $(PROGRAM)

$(PROGRAM): $(COBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

run: $(PROGRAM)
	./$<

clean: objclean execlean pngclean

objclean:
	$(RM) -f $(COBJECTS)

execlean:
	$(RM) -f $(PROGRAM)

pngclean:
	$(RM) -f prime-spiral.png
