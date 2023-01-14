all: rtclock.o parSum.h parSum.c seqSum.c
	gcc -Wall -g -o parSum parSum.c rtclock.o -lpthread
	gcc -Wall -g -o seqSum seqSum.c rtclock.o

rtclock.o: rtclock.h rtclock.c
	gcc -Wall -g -c rtclock.c

clean:
	rm -rf *.o parSum seqSum
