CC = gcc
CFLAGS = -Wall

all: mybsh

mybsh: mybsh.c
	$(CC) $(CFLAGS) -o $@ $<

commands: 
	$(CC) $(CFLAGS) -o mybin/ls commands/ls.c
	$(CC) $(CFLAGS) -o mybin/pwd commands/pwd.c
	$(CC) $(CFLAGS) -o mybin/clear commands/clear.c
	$(CC) $(CFLAGS) -o mybin/myps commands/myps.c
	$(CC) $(CFLAGS) -o mybin/mykill commands/mykill.c

clean:
	rm -f mybsh mybin/ls mybin/pwd mybin/clear mybin/myps mybin/mykill

.PHONY: all commands clean
