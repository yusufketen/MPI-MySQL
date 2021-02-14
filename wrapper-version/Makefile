CC = gcc
MPICC = mpicc
LIBS = -L/usr/local/mysql/lib -lmysqlclient -lz

ale:
	$(CC) -o utility.o utility.c -c
	$(CC) -o ale.o ale.c -c
	$(CC) -o ali-wrapper.o ali-wrapper.c -c
	$(CC) -o main ale.o utility.o
	$(CC) -o ali-wrapper ali-wrapper.o utility.o
	$(MPICC) -o ali.o ali.c $(LIBS)
	sudo ./main

clean:
	rm -f *.o
	rm -f ali-wrapper
	rm -f ./main