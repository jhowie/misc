BINDIR=/usr/local/bin
LFLAGS=
#CFLAGS=-g
CFLAGS=

BINARIES= ip4innet

.c.o:
	cc -c $(CFLAGS) $<

all: $(BINARIES)

clean:
	rm -f $(BINARIES)
	rm *.o
	rm *.a
	rm -rf *.dSYM

install: all
	install -d -o root -g wheel $(BINDIR)
	install -c -o root -g wheel -m 0555 ip4innet $(BINDIR)

	
ip4innet: ip4innet.o
	cc $(CFLAGS) -o ip4innet ip4innet.o $(LFLAGS)

