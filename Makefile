CC = gcc
MPICC = mpicc
MPIRUN = mpirun
LIBS = -L/usr/local/mysql/lib -lmysqlclient -lz
CORE = 6

select:
	$(CC) -o select.o mysql-select.c $(LIBS)
	sudo ./select.o

select-mpi:
	$(MPICC) -o select-mpi.o	mysql-select-mpi.c $(LIBS)
	sudo $(MPIRUN) -n $(CORE) ./select-mpi.o

insert:
	$(CC) -o insert.o mysql-insert.c $(LIBS)
	sudo ./insert.o

insert-mpi:
	$(MPICC) -o insert-mpi.o	mysql-insert-mpi.c $(LIBS)
	sudo $(MPIRUN) -n $(CORE) ./insert-mpi.o

clean:
	rm -f *.o