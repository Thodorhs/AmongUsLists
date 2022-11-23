CC=gcc
CFLAGS=-Wall -pedantic 

AmongUs.out: main.o among_us.o
	$(CC) $(CFLAGS) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -rf among_us.o main.o AmongUs.out