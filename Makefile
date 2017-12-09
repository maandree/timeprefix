.POSIX:

CONFIGFILE = config.mk
include $(CONFIGFILE)

all: timeprefix

timeprefix: timeprefix.o
	$(CC) -o $@ timeprefix.o $(LDFLAGS)

.c.o:
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CFLAGS)

install: timeprefix
	mkdir -p -- "$(DESTDIR)$(PREFIX)/bin"
	mkdir -p -- "$(DESTDIR)$(PREFIX)/share/licenses/timeprefix"
	mkdir -p -- "$(DESTDIR)$(MANPREFIX)/man1"
	cp -- timeprefix "$(DESTDIR)$(PREFIX)/bin/"
	cp -- LICENSE "$(DESTDIR)$(PREFIX)/share/licenses/timeprefix/"
	cp -- timeprefix.1 "$(DESTDIR)$(MANPREFIX)/man1/"

uninstall:
	-rm -f -- "$(DESTDIR)$(PREFIX)/bin/timeprefix"
	-rm -rf -- "$(DESTDIR)$(PREFIX)/share/licenses/timeprefix"
	-rm -- "$(DESTDIR)$(MANPREFIX)/man1/timeprefix.1"
	-rmdir -- "$(DESTDIR)$(PREFIX)/bin"
	-rmdir -- "$(DESTDIR)$(MANPREFIX)/man1"

clean:
	-rm -f -- timeprefix *.o

.SUFFIXES:
.SUFFIXES: .o .c

.PHONY: all install uninstall clean
