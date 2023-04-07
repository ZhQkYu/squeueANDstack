bucketstack: bucketstack.o bucketstack_client.o
	gcc -Wall -std=c99 -g -o bucketstack bucketstack.o bucketstack_client.o

bucketstack.o: bucketstack.h bucketstack.c
	gcc -Wall -std=c99 -c bucketstack.c

bucketstack_client.o: bucketstack_client.c
	gcc -Wall -std=c99 -c bucketstack_client.c

clean:
	rm -f *.o bucketstack