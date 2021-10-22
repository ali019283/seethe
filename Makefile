CFLAGS += -O2 -pipe
all:
	$(CC) seethe.c $(CFLAGS) -o seethe
	$(CC) smanager.c $(CFLAGS) -o sman
install: all
	cp seethe /sbin
	cp sman /usr/bin
