all: rtclock.o parSum.c seqSum.c
	gcc -Wall -o parSum parSum.c rtclock.o -lpthread
	gcc -Wall -o seqSum seqSum.c rtclock.o

rtclock.o: rtclock.h rtclock.c
	gcc -Wall -c rtclock.c

clean:
	rm -rf *.o parSum seqSum
