#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

#define MAX_STRING 128

int main()
{

	MPI_Init(NULL, NULL);
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
							user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	clock_t begin = clock();
	switch (world_rank)
	{
	case 0:
		firstRecord = 1;
		lastRecord = 10000;
		break;
	case 1:
		firstRecord = 10000;
		lastRecord = 20000;
		break;
	case 2:
		firstRecord = 20000;
		lastRecord = 30000;
		break;
	case 3:
		firstRecord = 30000;
		lastRecord = 40000;
		break;
	case 4:
		firstRecord = 40000;
		lastRecord = 50000;
		break;
	case 5:
		firstRecord = 50000;
		lastRecord = 60000;
		break;
	default:
		printf("wrong rank!\n");
		break;
	}

	for (int i = firstRecord; i < lastRecord; i++)
	{
		MYSQL_RES *temp_res = NULL;
		char query[MAX_STRING] = {0};
		snprintf(query, MAX_STRING, "SELECT * from agi where id = %d", i);
		//snprintf(query, MAX_STRING, "INSERT INTO agi(name, surname) VALUES('testfinal', 'testfinal2')");
		if (mysql_query(conn, query))
		{
			printf("%s",mysql_error(conn));
		}
		else
		{
			temp_res = mysql_use_result(conn);
		}

		if (temp_res)
		{
			//while ((row = mysql_fetch_row(temp_res)))
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

	MPI_Finalize();
}
