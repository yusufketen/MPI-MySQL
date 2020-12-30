#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING 128

int main() {
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

		
	clock_t begin = clock();
 
			for(int i = 1; i < 60000; i++)
			{
				MYSQL_RES *temp_res = NULL;
				char query[MAX_STRING] = {0};
				snprintf(query, MAX_STRING, "SELECT * from agi where id = %d", i);
				//snprintf(query, MAX_STRING, "INSERT INTO agi(name, surname) VALUES('testfinal', 'testfinal2')");
				if(mysql_query(conn, query))
				{
					printf("%s",mysql_error(conn));
				} else {
					temp_res = mysql_use_result(conn);
				}

				if(temp_res){
					//while((row=mysql_fetch_row(temp_res)))
						//printf("%s %s %s\n", row[0], row[1], row[2]);											
				}
				mysql_free_result(temp_res);
			
			
			}					

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Query runned %f seconds.\n", time_spent);

    res = mysql_use_result(conn);

    /* close connection */
    mysql_free_result(res);
    mysql_close(conn);

}
