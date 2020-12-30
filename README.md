# System
Ubuntu 20.04  
MySQL 8.022  
  
# Requirements  
MPI -> sudo apt install mpich  
GCC -> gcc -o mysql-test MySQL-Test.c -L/usr/local/mysql/lib -lmysqlclient -lz  
Install MySQL C Library -> sudo apt-get install libmysqlclient-dev  
  
# Misc  
MySQL Access -> sudo mysql -u root  


# How to run
"make select" : Run select query
"make select-mpi" : Run select query using by MPI 

"make insert" : Run instert query
"make insert-mpi" : Run insert query using by MPI
