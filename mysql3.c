#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

#define MAX_STRING 128

int main() {

     MPI_Init(NULL,NULL);
     int world_rank;
     MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
     MYSQL *conn;
     MYSQL_RES *res;
     MYSQL_ROW row;
     char *server = "localhost";
     char *user = "root";
     char *password = "5h3bfex4x"; /* set me first */
     char *database = "agidb";
     char *dataname = "test1name";
     char *datasurname = "test1surname";
     conn = mysql_init(NULL);
     /* Connect to database */
	int firstRecord;
	int lastRecord;

     if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
//	printf("MySQL Database Connection\n1- Fill Table\n2- Access Data\nChoice: ");
//	int program_type = -1;
//	scanf("%d", &program_type);
		
	clock_t begin = clock();
 /*	switch(program_type)
	{
		case 1:
			for(int i = 1000; i < 9999; i++)
			{	
			
				char query[MAX_STRING] = {0};	

				char *name = (char*)malloc(sizeof(char) * 8);
				char name_ext[] = "jack";
				memcpy(name, name_ext, sizeof(char) * 4);
				sprintf(name+sizeof(char)*4, "%d", i);

		
				char* surname = (char*)malloc(sizeof(char) * 11);
				char surname_ext[] = "sparrow";
				memcpy(surname, surname_ext, sizeof(char) * 7);
				sprintf(surname+sizeof(char)*7, "%d",i);
		


				snprintf(query, MAX_STRING, "INSERT INTO agi (name, surname) VALUES ('%s', '%s')", name, surname);
				mysql_query(conn, query);
				
				free(name);
				free(surname);
			}	
		break;
		///---------------------------------------------------------------------------------------------------------------------- //
		case 2:
			
*/
			switch(world_rank){
			case 0:
				firstRecord = 1;
				lastRecord = 1500;
				break;
			case 1:
				firstRecord = 1500;
				lastRecord = 3000;
				break;
			case 2:
				firstRecord = 3000;
				lastRecord = 4500;
				break;
			case 3:
				firstRecord = 4500;
				lastRecord = 6000;
				break;
			case 4:
				firstRecord = 6000;
				lastRecord = 7500;
				break;
			case 5:
				firstRecord = 7500;
				lastRecord = 9000;
				break;
			default:
				printf("wrong rank!\n");
				break;

			}

			for(int i = firstRecord; i < lastRecord; i++)
			{
				MYSQL_RES *temp_res = NULL;
				char query[MAX_STRING] = {0};
			//	snprintf(query, MAX_STRING, "SELECT * from agi where id = %d", i);
				snprintf(query, MAX_STRING, "INSERT INTO agi(name, surname) VALUES('testfinal', 'testfinal2')");
				if(mysql_query(conn, query))
				{
					printf(mysql_error(conn));
				} else {
					temp_res = mysql_use_result(conn);
				}

				if(temp_res){
					while((row=mysql_fetch_row(temp_res)))
						printf("%s %s %s\n", row[0], row[1], row[2]);											
				}
				mysql_free_result(temp_res);
			//	res = mysql_use_result(conn);
			//	while((row = mysql_fetch_row(res)) != NULL)
			//		printf("%s \n", row[0]);
			
			}					
			//break;

	/*	default:
			printf("Wrong Type!");
			return 0;
			break;
	
	}*/

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Query runned %f seconds.\n", time_spent);

/*    
    if (mysql_query(conn, "select * from agi")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
*/
    res = mysql_use_result(conn);

    /* output table name */
//    printf("MySQL Tables in mysql database:\n");
//    while ((row = mysql_fetch_row(res)) != NULL)
//        printf("%s \n", row[0]);

    /* close connection */
    mysql_free_result(res);
    mysql_close(conn);


	MPI_Finalize();
}
