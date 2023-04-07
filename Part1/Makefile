squeue: squeue.o squeue_client.o
	gcc -Wall -std=c99 -o squeue squeue.o squeue_client.o

squeue.o: squeue.h squeue.c
	gcc -Wall -std=c99 -c squeue.c

squeue_client.o: squeue_client.c
	gcc -Wall -std=c99 -c squeue_client.c

clean:
	rm -f *.o squeue