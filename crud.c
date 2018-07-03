#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>
#include <string.h>
#include "crud.h"

MYSQL *conn;
MYSQL_RES *result;
MYSQL_ROW row;

int retval;
const char* host = "jesdb.smaldino.it";
const char* database = "db_meteo1";
const char* db_user = "meteo1";
const char* db_pass = "meteop1";

int CRUD_insert_temp_hum(char *sitecode, char *data, float temp, float hum){
	char stringa[500];
	int retcode;
	conn = mysql_init (NULL);
	if (!mysql_real_connect(conn,host,db_user,db_pass,database,8606,NULL,0)) {
		fprintf(stderr,"Errore di connessione: %s\n",mysql_error(conn));
		retcode = -1;
	}
	else{
		sprintf(stringa,"INSERT INTO TempHum (SiteCode,ReadTime,Temperature,Humidity) VALUES ('%s','%s',%4.1f,%4.1f);",sitecode,data,temp,hum);
		printf("%s\n",stringa);
		retval = mysql_query(conn,stringa);
		if(retval==0){
			printf("Inserimento riuscito%s\n");
			retcode = 0;
		}else{
			fprintf(stderr,"Inserimento non riuscito\n%s\n",mysql_error(conn));
			retcode = -2;
		}
	}
	mysql_close(conn);
	return retcode;
} // CRUD_insert_temp_hum
