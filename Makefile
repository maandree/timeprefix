.POSIX:

CONFIGFILE = config.mk
include $(CONFIGFILE)

all: timeprefix

timeprefix: timeprefix.o
	$(CC) -o $@ timeprefix.o $(LDFLAGS)

.c.o:
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CFLAGS)

check: timeprefix
	test "$$(printf '%s\n' a b c d e | ./timeprefix | sed 's/[0-9]/0/g' | md5sum | tr -Cd '[:xdigit:]\n')" \
		= "3f1efed82f846e18973bd016fe5aeba4"

install: timeprefix
	mkdir -p -- "$(DESTDIR)$(PREFIX)/bin"
	mkdir -p -- "$(DESTDIR)$(MANPREFIX)/man1"
	cp -- timeprefix "$(DESTDIR)$(PREFIX)/bin/"
	cp -- timeprefix.1 "$(DESTDIR)$(MANPREFIX)/man1/"

uninstall:
	-rm -f -- "$(DESTDIR)$(PREFIX)/bin/timeprefix"
	-rm -- "$(DESTDIR)$(MANPREFIX)/man1/timeprefix.1"

clean:
	-rm -f -- timeprefix *.o

.SUFFIXES:
.SUFFIXES: .o .c

.PHONY: all check install uninstall clean
